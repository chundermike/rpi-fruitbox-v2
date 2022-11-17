#include "fruitbox.hpp"

using namespace std;

const array<dynamic_parameter_t, 12> DynamicParameter {
  {
    DynamicParameterNone,
    
    {"${RANDOM}", StatusEvent_TimerChange, true, false,
      [](void *var) {
        dynamic_t *v { static_cast<dynamic_t *>(var) };
        v->val = v->min + (fast_random::rand() % (v->max - v->min));
      }
    },

    {"${TIMER_TICK}", StatusEvent_TimerChange, true, false,
      [](void *var) {
        dynamic_t *v { static_cast<dynamic_t *>(var) };
        if (v->forward)
        {
          if (++v->val >= v->max) v->forward = false;
        }
        else
        {
          if (--v->val <= v->min) v->forward = true;
        }
      }
    },

    {"${VOLUME}", StatusEvent_VolumeChange, true, false,
      [](void *var) {
        dynamic_t *v { static_cast<dynamic_t *>(var) };
        float vol { static_cast<float>(Config->ini_general->song_volume) / static_cast<float>(100.0) };
        v->val = v->min + static_cast<int32_t>((v->max - v->min) * vol);
      }
    },

    {"${FIRST_VISIBLE_TITLE_STRIP}", StatusEvent_TitleStripMoveChange, true, false,
      [](void *var) {
        dynamic_t *v { static_cast<dynamic_t *>(var) };
        float strip { };
        if (Database->number_of_title_strips == 1)
        {
          strip = 0.0;
        }
        else
        {
          strip = static_cast<float>(TitleStripDisplayClass::start_title_strip) / static_cast<float>(Database->number_of_title_strips - 1);
        }
        v->val = v->min + static_cast<int32_t>((v->max - v->min) * strip);
      }
    },
    
    {"${LAST_VISIBLE_TITLE_STRIP}", StatusEvent_TitleStripMoveChange, true, false,
      [](void *var) {
        dynamic_t *v { static_cast<dynamic_t *>(var) };
        float strip { };
        if (Database->number_of_title_strips == 1)
        {
          strip = 0.0;
        }
        else
        {
          strip = static_cast<float>(TitleStripDisplayClass::start_title_strip + Config->skin_general->num_title_strips - 1) / static_cast<float>(Database->number_of_title_strips - 1);
        }
        v->val = v->min + static_cast<int32_t>((v->max - v->min) * strip);
      }
    },
    
    {"${NOW_PLAYING_ELAPSED_TIME}", StatusEvent_OneSecondChange, true, false,
      [](void *var) {
        dynamic_t *v { static_cast<dynamic_t *>(var) };
        v->val = v->min + static_cast<int32_t>(static_cast<float>(v->max - v->min) * status.now_playing_time_remaining_scale);
      }
    },
    
    {"${SONG_LOAD_POSITION}", StatusEvent_TimerChange, true, false,
      [](void *var) {
        dynamic_t *v { static_cast<dynamic_t *>(var) };
        v->val = v->min + static_cast<int32_t>(static_cast<float>(v->max - v->min) * status.song_load_position);
      }
    },
    
    {"${PLAYQUEUE_OCCUPANCY}", StatusEvent_TimerChange, true, false,
      [](void *var) {
        dynamic_t *v { static_cast<dynamic_t *>(var) };
        v->val = v->min + static_cast<int32_t>(static_cast<float>(v->max - v->min) * PlayQueue->occupancy);
      }
    },
    
    {"${SPECTRUM_BAND}", StatusEvent_AudioBandsChange, true, true,
      [](void *var) {
        dynamic_t *v { static_cast<dynamic_t *>(var) };
        // double gain { static_cast<double>(v->max - v->min) / spectrum_analyser_max_av_len};
        double gain { static_cast<double>(v->max - v->min)};
        v->val = v->min + static_cast<uint32_t>((spectrum_analyser_band[0][v->mode_param] + spectrum_analyser_band[1][v->mode_param]) * gain) / 2;
      }
    },
    
    {"${LEFT_SPECTRUM_BAND}", StatusEvent_AudioBandsChange, true, true,
      [](void *var) {
        dynamic_t *v { static_cast<dynamic_t *>(var) };
        // double gain { static_cast<double>(v->max - v->min) / spectrum_analyser_max_av_len};
        double gain { static_cast<double>(v->max - v->min) };
        v->val = v->min + static_cast<uint32_t>(spectrum_analyser_band[0][v->mode_param] * gain);
      }
    },
    
    {"${RIGHT_SPECTRUM_BAND}", StatusEvent_AudioBandsChange, true,  true,
      [](void *var) {
        dynamic_t *v { static_cast<dynamic_t *>(var) };
        // double gain { static_cast<double>(v->max - v->min) / spectrum_analyser_max_av_len};
        double gain { static_cast<double>(v->max - v->min) };
        v->val = v->min + static_cast<uint32_t>(spectrum_analyser_band[1][v->mode_param] * gain);
      }
    }
  }
};

  void DisplayBaseClass::ResetBaseParams(void)
  {
    ResetDynamic(size, 0, 0);
    ResetDynamic(position, 0, 0);
    ResetDynamic(clip, 0, 0, 0, 0);
    ResetDynamic(angle, 0);
    ResetDynamic(tint, 255, 255, 255, 255);
    tint_defined = false;
    horzflip = false;
    vertflip = false;
    no_draw = false;
    has_dynamics = false;
    clipped = false;
    visible = true;
  }

  void DisplayBaseClass::ResetDynamic(dynamic_t &var, int32_t val)
  {
    var = { &DynamicParameterNone, val, val, val, false, 0 };
  }

  void DisplayBaseClass::ResetDynamic(dynamics2_t &var, int32_t val1, int32_t val2)
  {
    ResetDynamic(var.x, val1);
    ResetDynamic(var.y, val2);
  }

  void DisplayBaseClass::ResetDynamic(dynamics4_t &var, int32_t val1, int32_t val2, int32_t val3, int32_t val4)
  {
    ResetDynamic(var.x, val1);
    ResetDynamic(var.y, val2);
    ResetDynamic(var.w, val3);
    ResetDynamic(var.h, val4);
  }

  void DisplayBaseClass::InitDynamic(dynamic_t &var)
  // setup correct status event mask bits and (common) has_dynamics flag
  {
    event_mask |= var.param->event_mask;
    if (var.param->is_dynamic) has_dynamics = true; // minimum of one parameter needs to be dynamic to make whole display object dynamic
    if (var.param->is_spectrum_analyser)
    { 
      Audio->spectrum_analyser = true; // ditto above
    } 
  }

  void DisplayBaseClass::InitDynamics(void)
  {
    if (supports_dynamics)
    {
      if (static_cast<uint32_t>(dynamic_flag_en) >= Config->status_flag.size()) dynamic_flag_en = dynamic_flag_en_e::None;
      InitDynamic(size.x);
      InitDynamic(size.y);
      InitDynamic(position.x);
      InitDynamic(position.y);
      InitDynamic(clip.x);
      InitDynamic(clip.y);
      InitDynamic(clip.w);
      InitDynamic(clip.h);
      InitDynamic(angle);
      InitDynamic(tint.x);
      InitDynamic(tint.y);
      InitDynamic(tint.w);
      InitDynamic(tint.h);
    }
  }

  void DisplayBaseClass::UpdateDynamic(dynamic_t &var, const uint32_t event)
  {
    if (event & var.param->event_mask)
    {
      var.param->Update(static_cast<void*>(&var));
    }
    
    if (var.max >= var.min) // normal (ascending) range
    {
      if (var.val > var.max) var.val = var.max;
      else if (var.val < var.min) var.val = var.min;
    }
    else // descending range
    {
      if (var.val > var.min) var.val = var.min;
      else if (var.val < var.max) var.val = var.max;
    }

  }

  void DisplayBaseClass::UpdateDynamics(const uint32_t event)
  {
    if (has_dynamics)
    {
      if (Config->status_flag[static_cast<uint32_t>(dynamic_flag_en)])
      {
        if (size.x.param->is_dynamic)     UpdateDynamic(size.x, event);
        if (size.y.param->is_dynamic)     UpdateDynamic(size.y, event);
        if (position.x.param->is_dynamic) UpdateDynamic(position.x, event);
        if (position.y.param->is_dynamic) UpdateDynamic(position.y, event);
        if (clip.x.param->is_dynamic)     UpdateDynamic(clip.x, event);
        if (clip.y.param->is_dynamic)     UpdateDynamic(clip.y, event);
        if (clip.w.param->is_dynamic)     UpdateDynamic(clip.w, event);
        if (clip.h.param->is_dynamic)     UpdateDynamic(clip.h, event);
        if (angle.param->is_dynamic)      UpdateDynamic(angle, event);
        if (tint.x.param->is_dynamic)     UpdateDynamic(tint.x, event);
        if (tint.y.param->is_dynamic)     UpdateDynamic(tint.y, event);
        if (tint.w.param->is_dynamic)     UpdateDynamic(tint.w, event);
        if (tint.h.param->is_dynamic)     UpdateDynamic(tint.h, event);
        tint_colour = al_map_rgba(tint.x.val, tint.y.val, tint.w.val, tint.h.val);
      }
    }
  };

