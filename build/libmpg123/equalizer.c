/*
	equalizer.c: equalizer settings

	copyright ?-2006 by the mpg123 project - free software under the terms of the LGPL 2.1
	see COPYING and AUTHORS files in distribution or http://mpg123.org
	initially written by Michael Hipp
*/

/* NOTE : WORKS FOR MPG123-1.29.3 */

/*
#include <stdio.h>
#include <math.h>

int main(int argc, char *argv[])
{
  int x;
  float g, scale;
  float gain, master_gain;
  int lut_size;

  if (argc != 4)
  {
    printf("Usage : spectrum_correct <scale> <lut_size> <gain>\n");
    exit(-1);
  }

  scale = atof(argv[1]);
  lut_size = atoi(argv[2]);
  master_gain = atof(argv[3]);
  printf("scale = %1.2f\n", scale);
  for (x = 0; x <= lut_size; x += 1)
  {
    g = log(1 + (scale * lut_size)) / log(1 + (scale * x));
    if (x == 0) gain = 0;
    else gain = 1 / ((x * g) / lut_size);
    // printf("%d %f (%f)\n", x, gain, x * gain);
    float lut_in = (float)x/(float)lut_size;
    printf("%d %f -> %f\n", (int)(lut_in * lut_size), lut_in, lut_in * gain * master_gain);
  }
  return 0;
}*/

// #define DEBUG_PRINTF

#include "mpg123lib_intern.h"
#include "math.h"

#define LUT_SIZE_BITS          (11)
#define LUT_SIZE               (1 << LUT_SIZE_BITS)
#define LUT_SCALE              (0.3)
#define LUT_GAIN               (1.0)

#define NUM_SUB_BANDS          (32)

#define SYNC_DELAY_BITS        (4) /* multiplied by 1<<AVERAGING_LENGTH_BITS */
#define SYNC_DELAY             (256) /* must be less than SYNC_DELAY_BITS * AVERAGING_LENGTH */

#define AVERAGING_LENGTH_BITS  (6)
#define AVERAGING_LENGTH       (1 << AVERAGING_LENGTH_BITS)

#define DELAY_LINE_LENGTH      (1 << (AVERAGING_LENGTH_BITS + SYNC_DELAY_BITS))
#define DELAY_LINE_LENGTH_MASK (DELAY_LINE_LENGTH - 1)

float gain_lut[LUT_SIZE + 1];

uint32_t refresh_spectrum_analyser_band = 0;
double spectrum_analyser_band[2][NUM_SUB_BANDS]; // 0.0 to 1.0
double accum_band_value[2][NUM_SUB_BANDS];
float band_z[2][DELAY_LINE_LENGTH][NUM_SUB_BANDS]; // delay line

unsigned int delay_wptr[2] = {SYNC_DELAY, SYNC_DELAY}; // new sample store position
unsigned int delay_in[2]   = {DELAY_LINE_LENGTH, DELAY_LINE_LENGTH}; // accum window start position
unsigned int delay_out[2]  = {DELAY_LINE_LENGTH - AVERAGING_LENGTH, DELAY_LINE_LENGTH - AVERAGING_LENGTH}; // accum window end position

void init_equalizer(void)
{
  // set up log gain lut...
  int x;
  float g, gain;
  // printf("\ninit_equalizer..\n");
  for (x = 0; x <= LUT_SIZE; x += 1)
  {
    g = log(1 + (LUT_SCALE * LUT_SIZE)) / log(1 + (LUT_SCALE * x));
    if (x == 0) gain = 0;
    else gain = 1 / ((x * g) / LUT_SIZE);
    float lut_in = (float)x/(float)LUT_SIZE;
    gain_lut[x] = lut_in * gain * LUT_GAIN;
    // printf("%d %f -> %f\n", x, lut_in, gain_lut[x]);
  }
  // printf("****************");
}

void clear_equalizer(void)
{
  memset(band_z, 0, sizeof(band_z));

  for (int i = 0; i < NUM_SUB_BANDS; ++i) // clear averager accumulators
  {
    for(int ch = 0; ch < 2; ++ch)
    {
      accum_band_value[ch][i] = 0;
      spectrum_analyser_band[ch][i] = 0;
    }
  }
}

void do_equalizer(real *bandPtr, int channel, real equalizer[2][NUM_SUB_BANDS])
{
	int i;
  float f;

  unsigned int dwptr = delay_wptr[channel]++ & DELAY_LINE_LENGTH_MASK;
  unsigned int din   = delay_in[channel]++ & DELAY_LINE_LENGTH_MASK;
  unsigned int dout  = delay_out[channel]++ & DELAY_LINE_LENGTH_MASK;

  for(i=0;i<NUM_SUB_BANDS;i++)
  {
    // bandPtr[i] = REAL_MUL(bandPtr[i], equalizer[channel][i]);

    f = bandPtr[i];
    band_z[channel][dwptr][i] = (f < 0) ? -f : f; // add abs(latest band value) to delay pipeline

    // accumulate band value over AVERAGING_LENGTH delay taps...
    accum_band_value[channel][i] += (double)band_z[channel][din][i];
    accum_band_value[channel][i] -= (double)band_z[channel][dout][i];

#ifdef DEBUG_PRINTF
if (channel == 0 && i == 0) printf("%f ", accum_band_value[channel][i]);
#endif

  #if 1

  // uint32_t gain_lut_idx = (uint32_t)(accum_band_value[channel][i]) >> AVERAGING_LENGTH_BITS;
  uint32_t gain_lut_idx = (uint32_t)(accum_band_value[channel][i] * (LUT_SIZE >> AVERAGING_LENGTH_BITS));

  // #ifdef DEBUG_PRINTF
  // if (channel == 0 && i == 0) printf("%f %d ", band_val, gain_lut_idx);
  // #endif

  if (gain_lut_idx >= LUT_SIZE) gain_lut_idx = LUT_SIZE;

  #ifdef DEBUG_PRINTF
  if (channel == 0 && i == 0) printf("gain_lut[%d]=%f\n", gain_lut_idx, gain_lut[gain_lut_idx]);
  #endif

  // store for external code to see (after passing through log gain lut)...
  spectrum_analyser_band[channel][i] = gain_lut[gain_lut_idx];

  #else
   NOTE !!! THE BELOW CODE WILL ONLY BE EXECUTED FOR THE FIRST BAND ON THE FIRST CHANNEL,
   NOTE !!! SO WE NEED ONLY SET refresh_spectrum_analyser_band TO ZERO AFTER THEY ARE ALL DONE
    if (refresh_spectrum_analyser_band) // only need to update this when needed (i.e. each video frame in engine.cpp)
    {
      uint32_t gain_lut_idx = (uint32_t)(accum_band_value[channel][i]) >> AVERAGING_LENGTH_BITS;
      if (gain_lut_idx >= LUT_SIZE) gain_lut_idx = LUT_SIZE;

      // store for external code to see (after passing through log gin lut)...
      spectrum_analyser_band[channel][i] = gain_lut[gain_lut_idx];
      refresh_spectrum_analyser_band = 0;
    }
  #endif

#if 0
if (channel == 0 && i == 0)
{
  printf("%f, wp[%d]=%f, rp[%d]=%f %f %f lut[%d]=%f\n", bandPtr[i], wp, band_z[channel][wp][i], rp, band_z[channel][rp][i], accum_band_value[channel][i], band_val, gain_lut_idx, spectrum_analyser_band[channel][i]);
}
#endif

  }
}
