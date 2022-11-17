#pragma once

#include "fruitbox.hpp"

using namespace std;

class ConfigClass  : public ConfigBaseClass
{
public:
  ConfigClass(void);
  bool LoadSkin(const string cfg_filename);
  bool LoadIni(void);
  bool SaveIni(void);
  void ConfigureDisplayTouch(void);
  void ConfigureSkinTouch(void);
  // void LoadButtons(const string filename);
  // void ChooseMenu(const string choose_cfg_filename, string &filename);
  // void LoadChooserScreenshot(ChooserConfigClass *chooser);
  void PostProcess(void);
  dynamics2_t SetSizeToTitleStrip(DisplayBaseClass *obj);
  void SetTitleStripPositions(DisplayBaseClass *obj);

  IniGeneralConfigClass     *ini_general {};
  IniAttractModeConfigClass *ini_attract {};
  IniSkinListConfigClass    *ini_skin_list {};
  ButtonsConfigClass        *buttons {};
  TouchScreenConfigClass    *touch_screen {};
  MouseDisplayClass         *mouse {};
  JoystickDisplayClass      *joystick {};

  GeneralConfigClass        *skin_general {};
  TouchButtonsDisplayClass  *skin_touch_buttons {};
  TouchSongDisplayClass     *skin_touch_song {};
  vector<DisplayBaseClass*>  skin_display_object {};

  void DescribeParamsIni(ofstream &strm, const char *indent)
  {
    strm << indent << cfgSection_ini_general << endl;
    ini_general->DescribeParams(strm, indent);
    strm << endl << indent << cfgSection_ini_attract << endl;
    ini_attract->DescribeParams(strm, indent);
    strm << endl << indent << cfgSection_ini_skin_list << endl;
    ini_skin_list->DescribeParams(strm, indent);
    strm << endl << indent << cfgSection_ini_buttons << endl;
    buttons->DescribeParams(strm, indent);
    strm << endl << indent << cfgSection_ini_touch_screen << endl;
    touch_screen->DescribeParams(strm, indent);
    strm << endl << indent << cfgSection_ini_mouse << endl;
    mouse->DescribeParams(strm, indent);
    strm << endl << indent << cfgSection_ini_joystick << endl;
    joystick->DescribeParams(strm, indent);
    strm << endl;
  }

  void DescribeParams(ofstream &strm, const char *indent)
  {
    strm << indent << cfgSection_skin_general << endl;
    skin_general->DescribeParams(strm, indent);

    strm << endl << indent << cfgSection_fonts << endl;
    tmp_fonts->DescribeParams(strm, indent);

    strm << endl << indent << cfgSection_title_strip << multiCfgParameter << endl;
    tmp_title_strip->DescribeParams(strm, indent);

    strm << endl << indent << cfgSection_status << multiCfgParameter << endl;
    tmp_status->DescribeParams(strm, indent);

    strm << endl << indent << cfgSection_bitmap << multiCfgParameter << endl;
    tmp_bitmap->DescribeParams(strm, indent);

    strm << endl << indent << cfgSection_spectrum_analyser << multiCfgParameter << endl;
    tmp_analyser->DescribeParams(strm, indent);

    // strm << endl << indent << cfgSection_ini_joystick << multiCfgParameter << endl;
    // tmp_joystick->DescribeParams(strm, indent);

    strm << endl << indent << cfgSection_touch_song << endl;
    skin_touch_song->DescribeParams(strm, indent);

    strm << endl << indent << cfgSection_touch_buttons << endl;
    skin_touch_buttons->DescribeParams(strm, indent);

    strm << endl;
  }

  void cfgRead(string line) {};

  // bool screenshot { false };
  bool no_scale { false };
  float rotate { 0.0 };
  uint32_t attract_mode_select {};
  array<bool, 5> status_flag {true, false, false, false, false}; // first one true as this is used as the default dynamic parameter enable

  string filename {};
  // string button_map { defaultButtonFilename };
  string ini_filename { defaultIniFilename };
  vector<uint32_t> select_digit_base {};
  vector<font_t> fonts {};
  // ints2_t touch_tl { };
  // ints2_t touch_br { };

private:
  FontConfigClass *tmp_fonts {};
  TitleStripDisplayClass *tmp_title_strip {};
  StatusDisplayClass *tmp_status {};
  BitmapDisplayClass *tmp_bitmap {};
  SpectrumAnalyserDisplayClass *tmp_analyser {};
  // JoystickDisplayClass *tmp_joystick {};

  bool addObject(ConfigBaseClass * obj)
  {
    DisplayBaseClass *o = dynamic_cast<DisplayBaseClass*>(obj);
    if (o != nullptr)
    { // object is a display object...
      skin_display_object.push_back(o->clone());
      o->renew();
      return true;
    }

    FontConfigClass *f = dynamic_cast<FontConfigClass*>(obj);
    if (f != nullptr)
    { // object is a font...
      for (auto &font : f->fonts)
      {
        if ((font.handle = al_load_ttf_font(font.filename.c_str(), -font.size, 0)) == nullptr) error("Failed to create %d-pt font '%s'", font.size, font.filename.c_str());
        fonts.push_back(font);
      }
      return true;
    }
    return false;
  };
};
