///////////////////////////////////////////////////////////////////////////////
// Project fruitbox.  A Retro MP3 Jukebox for the Raspberry Pi.
// Mike Kingsley 2016.
//
// Reads fruitbox and skin configuration files.
///////////////////////////////////////////////////////////////////////////////

#include "fruitbox.hpp"
#include "camera_shutter_click.hpp"

using namespace std;

string ConfigBaseClass::filepath {};

// tl, br used internally (and potentially modified)
ints2_t ConfigBaseClass::touch_tl {};
ints2_t ConfigBaseClass::touch_br {};

// tl, br read / written to ini file
ints2_t TouchScreenConfigClass::touch_tl {};
ints2_t TouchScreenConfigClass::touch_br {};

ConfigClass::ConfigClass(void)
{
  ini_general        = new IniGeneralConfigClass();
  ini_attract        = new IniAttractModeConfigClass();
  ini_skin_list      = new IniSkinListConfigClass();
  buttons            = new ButtonsConfigClass();
  touch_screen       = new TouchScreenConfigClass();
  mouse              = new MouseDisplayClass();
  joystick           = new JoystickDisplayClass();

  skin_general       = new GeneralConfigClass();
  skin_touch_buttons = new TouchButtonsDisplayClass();
  skin_touch_song    = new TouchSongDisplayClass();

  tmp_fonts          = new FontConfigClass ();
  tmp_title_strip    = new TitleStripDisplayClass ();
  tmp_status         = new StatusDisplayClass ();
  tmp_bitmap         = new BitmapDisplayClass ();
  // tmp_joystick       = new JoystickDisplayClass ();
  tmp_analyser       = new SpectrumAnalyserDisplayClass ();
}

bool ConfigClass::LoadIni(void)
{
  ifstream iniFile;
  string line;

  iniFile.open(ini_filename, ios::in);
  if (!iniFile.is_open())
  {
    log_file << WARNING << "Couldn't open initialisation file '" << ini_filename << "' for input" << endl;
    log_file << WARNING << "So will create a new default one" << endl;

    // create a fresh one...
    if (SaveIni() == false)
    {
      return false;
    }
    // and open it for subsequent reading...
    iniFile.open(ini_filename, ios::in);
  }

  log_file << "Loading initialisation file '" << ini_filename << "'..." << endl;

  ConfigBaseClass *obj { ini_general };

  ini_skin_list->skin_file.clear(); // start with no skin chooser Files...

  while (getline(iniFile, line))
  {
    if (line.empty()) continue;
    line.erase(0, line.find_first_not_of(" \t"));// remove leading whitespace
    if (line.empty()) continue;
    if (line.at(0) == cfgFile_comment) continue; // comment line
    if (line.at(0) == cfgFile_section_start)
    { // a new section...
      log_file << endl << "  " << line << endl;
      if (line.find(cfgSection_ini_general) != string::npos)
      {
        obj = ini_general;
      }
      else if (line.find(cfgSection_ini_mouse) != string::npos)
      {
        obj = mouse;
      }
      else if (line.find(cfgSection_ini_joystick) != string::npos)
      {
        obj = joystick;
      }
      else if (line.find(cfgSection_ini_attract) != string::npos)
      {
        obj = ini_attract;
      }
      else if (line.find(cfgSection_ini_skin_list) != string::npos)
      {
        obj = ini_skin_list;
      }
      else if (line.find(cfgSection_ini_buttons) != string::npos)
      {
        obj = buttons;
      }
      else if (line.find(cfgSection_ini_touch_screen) != string::npos)
      {
        obj = touch_screen;
      }
    } else { // no section character, so assume a config parameter...
      if (obj != nullptr) obj->cfgRead(line);
    }
  }

  log_file << endl;

  // check if we need GPIO input...
  for (auto &b : buttons->button)
  {
    if (b.type == input_type_e::GPIO)
    {
      int32_t pin { b.param[EVENT_PARAM_VAL1] };

      if (pin < NUM_GPIO)
      {
        Gpio->ConfigurePinAsInput(pin);
      }
      else
      {
        error("Invalid GPIO number (%d)", pin);
      }
    }
  }

  buttons->BackupUserMappings();

  log_file << endl << "...initialisation file closed." << endl << endl;

  iniFile.close();

  // only mark touch screen as calibrated if both top-left (tl) and bottom-right (br) values have been read from ini file...
  touch_screen->calibrated = touch_screen->tl_calibrated && touch_screen->br_calibrated; 

  return true;
}

bool ConfigClass::SaveIni(void)
{
  ofstream iniFile;
  string line;

  iniFile.open(ini_filename, ios::out);
  if (!iniFile.is_open())
  {
    log_file << WARNING << "Couldn't open initialisation file '" << ini_filename << "' for output" << endl;;
    return false;
  }

  log_file << "Saving initialisation file '" << ini_filename << "'..." << endl;

  iniFile << "# " << FRUITBOX_VERSION << " global config file" << endl << endl;
  iniFile << cfgSection_ini_general << endl;
  ini_general->cfgWrite(iniFile);
  iniFile << endl << cfgSection_ini_attract << endl;
  ini_attract->cfgWrite(iniFile);
  iniFile << endl << cfgSection_ini_skin_list << endl;
  ini_skin_list->cfgWrite(iniFile);
  iniFile << endl << cfgSection_ini_buttons << endl;
  buttons->cfgWrite(iniFile);
  iniFile << endl << cfgSection_ini_touch_screen << endl;
  touch_screen->cfgWrite(iniFile);

  iniFile << endl << cfgSection_ini_mouse << endl;
  mouse->cfgWrite(iniFile);

  iniFile << endl << cfgSection_ini_joystick << endl;
  joystick->cfgWrite(iniFile);

  iniFile.close();
  log_file << "Initialisation file saved." << endl << endl;

  return true;
}

void ConfigClass::ConfigureDisplayTouch(void)
// compute the touch offsets and scale factors for converting touch screen co-ordinates to display co-ordinates
// (used for menus; needs to be done before skin is loaded as required by skin chooser)
{
  // Setup touch input offset and scaling...

  if (ConfigBaseClass::touch_tl.x > ConfigBaseClass::touch_br.x)  // swap min and max around
  {
    ints2_t temp {ConfigBaseClass::touch_br};
    ConfigBaseClass::touch_br = ConfigBaseClass::touch_tl;
    ConfigBaseClass::touch_tl = temp;
    Input->reversed_touch = true;
  }

  // If max touch co-ordinates not defined, we set them to the size of the display...
  if (ConfigBaseClass::touch_br.x == 0) ConfigBaseClass::touch_br.x = Display->display_size.width;
  if (ConfigBaseClass::touch_br.y == 0) ConfigBaseClass::touch_br.y = Display->display_size.height;

  uint32_t touch_range_x = static_cast<uint32_t>(ConfigBaseClass::touch_br.x - ConfigBaseClass::touch_tl.x);
  uint32_t touch_range_y = static_cast<uint32_t>(ConfigBaseClass::touch_br.y - ConfigBaseClass::touch_tl.y);

  Input->touch_offset_x = ConfigBaseClass::touch_tl.x ;
  Input->touch_offset_y = ConfigBaseClass::touch_tl.y ;

  if (touch_range_x)
  {
    Display->scale_touch_to_display_x = static_cast<float>(Display->display_size.width) / static_cast<float>(touch_range_x);
  }
  if (touch_range_y)
  {
    Display->scale_touch_to_display_y = static_cast<float>(Display->display_size.height) / static_cast<float>(touch_range_y);
  }
}

void ConfigClass::ConfigureSkinTouch(void)
// compute the touch offsets and scale factors for converting touch screen co-ordinates to skin co-ordinates
{
  Display->scale_display_to_skin_x = static_cast<float>(skin_general->skin_size.x)  / static_cast<float>(Display->display_size.width);
  Display->scale_display_to_skin_y = static_cast<float>(skin_general->skin_size.y) / static_cast<float>(Display->display_size.height);

  uint32_t touch_range_x = static_cast<uint32_t>(ConfigBaseClass::touch_br.x - ConfigBaseClass::touch_tl.x);
  uint32_t touch_range_y = static_cast<uint32_t>(ConfigBaseClass::touch_br.y - ConfigBaseClass::touch_tl.y);

  if (touch_range_x)
  {
    Display->scale_touch_to_skin_x = static_cast<float>(skin_general->skin_size.x) / static_cast<float>(touch_range_x);
  }
  if (touch_range_y)
  {
    Display->scale_touch_to_skin_y = static_cast<float>(skin_general->skin_size.y) / static_cast<float>(touch_range_y);
  }

  if (no_scale)
  {
    // jukebox is positioned in centre of the touch area...

    // x and y are offsets in display resolution for skin to be centred...
    float x { static_cast<float>((Display->display_size.width - skin_general->skin_size.x) / 2) };
    float y { static_cast<float>((Display->display_size.height - skin_general->skin_size.y) / 2) };

    // ...but the touch offsets are in touch resolution...
    Input->touch_offset_x += static_cast<uint32_t>((x * static_cast<float>(touch_range_x)) / static_cast<float>(Display->display_size.width));
    Input->touch_offset_y += static_cast<uint32_t>((y * static_cast<float>(touch_range_y)) / static_cast<float>(Display->display_size.height));

    // skin is not visually scaled, but touch scale is as it's in touch co-ordinates not display resolution...
    Display->scale_touch_to_skin_x = static_cast<float>(Display->display_size.width)  / static_cast<float>(touch_range_x);
    Display->scale_touch_to_skin_y = static_cast<float>(Display->display_size.height) / static_cast<float>(touch_range_y);
  }

  // if we have a touch screen or mouse and any touch areas are defined, then force those buttons to be of touch input type...

  if (Input->touch_active || Input->mouse_active)
  {
    buttons->RegisterTouchAreas();
  }
}


bool ConfigClass::LoadSkin(const string cfg_filename)
{
  ifstream skinFile;
  string line;
  uint32_t skinFile_line_number {};

  ConfigBaseClass::filepath = cfg_filename.substr(0, cfg_filename.find_last_of("/"));

  filename =  cfg_filename;

  skinFile.open(cfg_filename, ios::in);

  if (!skinFile.is_open())
  {
    error("Couldn't open skin file '%s' for input", cfg_filename.c_str());
  }

  log_file << "Reading skin configuration file '" << cfg_filename << "'..." << endl;

  ConfigBaseClass *obj { skin_general };

  while (getline(skinFile, line))
  {
    skinFile_line_number++;
    if (line.empty()) continue;
    line.erase(0, line.find_first_not_of(" \t"));// remove leading whitespace
    if (line.empty()) continue;
    if (line.at(0) == cfgFile_comment) continue; // comment line
    if (line.at(0) == cfgFile_section_start)
    { // a new section...
      addObject(obj); // add previous object to list (as appropriate)
      log_file << endl << "  " << line << endl;
      if (line.find(cfgSection_skin_general) != string::npos)
      {
        obj = skin_general;
      }
      else if (line.find(cfgSection_touch_buttons) != string::npos)
      {
        obj = skin_touch_buttons;
      }
      else if (line.find(cfgSection_touch_song) != string::npos)
      {
        obj = skin_touch_song;
      }
      else if (line.find(cfgSection_fonts) != string::npos)
      {
        obj = tmp_fonts;
      }
      else if (line.find(cfgSection_title_strip) != string::npos)
      {
        obj = tmp_title_strip;
        skin_general->num_title_strips++;
      }
      else if (line.find(cfgSection_status) != string::npos)
      {
        obj = tmp_status;
      }
      else if (line.find(cfgSection_bitmap) != string::npos)
      {
        obj = tmp_bitmap;
      }
      else if (line.find(cfgSection_spectrum_analyser) != string::npos)
      {
        obj = tmp_analyser;
      }
      else
      {
        log_file << WARNING << "Unrecognised section (line " << skinFile_line_number << ")" << endl;
        obj = nullptr;
      }
    } else { // no section character, so assume a config parameter...
      if (obj != nullptr) obj->cfgRead(line);
    }
  }
  addObject(obj); // add last object to list

  skinFile.close();
  log_file << "Closed skin file." << endl << endl;

  if (skin_general->num_title_strips == 0) error("Must define at least one [title strip]");

  return true;
}

dynamics2_t ConfigClass::SetSizeToTitleStrip(DisplayBaseClass *obj)
{
  dynamics2_t obj_size;
  
  if (obj->size.y.val == 0) // size not defined in config file so calculate it based on title_strip characteristics
  {
    obj_size = skin_general->title_strip_size;
    if (skin_general->album_mode == false)
    {
      if (skin_general->pair_songs != pair_songs_e::No)
      {
        obj_size.y.val /= (3 * skin_general->songs_per_title_strip) / 2;
      }
      else
      {
        obj_size.y.val /= (4 * skin_general->songs_per_title_strip) / 2;
      }
    }
  }
  else // the size from the config file takes precedence
  {
    obj_size = obj->size;
  }

  return obj_size;
}

void ConfigClass::SetTitleStripPositions(DisplayBaseClass *obj)
{
  for (auto &i : skin_display_object) // find all title_strips...
  {
    if (dynamic_cast<TitleStripDisplayClass*>(i) != nullptr)
    {
      vector<uints2_t> title_strip_pos {};
      uints2_t pos {};
      if (skin_general->album_mode == false)
      {
        uint32_t sinc = i->size.y.val / skin_general->songs_per_title_strip;
        uint32_t yinc = 4 * sinc / (4 - (skin_general->pair_songs != pair_songs_e::No ? 1 : 0));
        for (uint32_t s = 0; s < skin_general->songs_per_title_strip; ++s)
        {
          uint32_t y { s * sinc };
          pos.x = i->position.x.val + static_cast<JoystickDisplayClass*>(obj)->offset.x;
          pos.y = i->position.y.val + y + static_cast<JoystickDisplayClass*>(obj)->offset.y;

          if (skin_general->pair_songs != pair_songs_e::No)
          {
            title_strip_pos.push_back(pos);
            pos.y = i->position.y.val + y + yinc;
            s++;
          }
          title_strip_pos.push_back(pos);
        }
      }
      else
      {
        pos.x = i->position.x.val + static_cast<JoystickDisplayClass*>(obj)->offset.x;
        pos.y = i->position.y.val + static_cast<JoystickDisplayClass*>(obj)->offset.y;
        title_strip_pos.push_back(pos);
      }
      static_cast<JoystickDisplayClass*>(obj)->title_strip_position.push_back(title_strip_pos);
      static_cast<JoystickDisplayClass*>(obj)->SetPositionToTitleStrip(0, 0);
      static_cast<JoystickDisplayClass*>(obj)->title_strip_position.shrink_to_fit();
    }
  }
}

void ConfigClass::PostProcess(void)
{
  // sanity / dependency checks...
  if ((skin_general->skin_size.x == 0 ) || (skin_general->skin_size.y == 0)) error("SkinSize not specified");

  Display->jukebox = al_create_bitmap(skin_general->skin_size.x, skin_general->skin_size.y);
  // bitmaps_created++; log_file << "al_create_bitmap(" << skin_general->skin_size.x << "," << skin_general->skin_size.y << ") - " << bitmaps_created << " ConfigClass::PostProcess" << endl;
  if (Display->jukebox == nullptr) error("Failed to create %d x %d jukebox bitmap", skin_general->skin_size.x, skin_general->skin_size.y);

  if (ini_general->max_playqueue_length == 0) error("%s must be greater than zero", cfgKeyword_MaxPlayQueueLength);
  if (skin_general->num_title_strips == 0) error("Must define at least one %s", cfgSection_title_strip);
  if (skin_general->songs_per_title_strip == 0) error("%s must be greater than zero", cfgKeyword_SongsPerTitleStrip);

  // for (auto &p : ini_general->credits_per_coin)
  // {
    // if (p) ini_general->free_play = false; // credits_per_coin not zero so turn free play off
  // }
  if ((skin_general->songs_per_title_strip == 1) && skin_general->pair_songs != pair_songs_e::No) error("Can't enable %s if %s is less than 2", cfgKeyword_PairSongs, cfgKeyword_SongsPerTitleStrip);
  if (skin_general->title_strip_move_style.effect >= num_title_strip_move_effects) error("%s effect should be less than %d", cfgKeyword_TitleStripMoveStyle, num_title_strip_move_effects);
  if (ini_attract->enable) attract_mode_select = 1 ; // force starting attract_mode to GenreAnyStr if attract set to 1

  if (Config->skin_general->no_duplicates) Config->ini_general->loop_playqueue = false; // can't loop songs if no_dupicates is enabled

  // Add extra sound channels for camera shutter sound effect...
  StatusDisplayClass::num_sound_channels++;

  if (!al_reserve_samples(StatusDisplayClass::num_sound_channels)) error("Couldn't reserve audio samples");
  
  // for any audio samples (Sound in status object), attach it to the output_mixer (can't do this in GetParam as Audio instance doesn't exist at that point)
  for (auto &i : skin_display_object)
  {
    if (dynamic_cast<StatusDisplayClass*>(i) != nullptr)
    {
      sound_t *sound { &static_cast<StatusDisplayClass*>(i)->sound };
      
      if (sound->handle != nullptr)
      {
        al_attach_sample_instance_to_mixer(sound->instance, AudioClass::output_mixer);
      }
    }
  }

  // load the screenshot sound effect...
  ALLEGRO_FILE *camera_shutter_click_f { al_open_memfile(camera_shutter_click_data, CAMERA_SHUTTER_CLICK_LEN, "rb") };
  if (camera_shutter_click_f == nullptr) error( "Failed to load fruitbox camera shutter sound effect mem file");
  camera_shutter_click.handle = al_load_sample_f(camera_shutter_click_f, ".wav");
  al_fclose(camera_shutter_click_f);
  
  ///////////////////////////////////////////////////////////////////////////////////////////////

  if (skin_general->select_buttons.size() == 0) // cfg file hasn't defined any select keys so use default
  {
    skin_general->select_buttons.push_back(defaultFirstSelectButtons);
    skin_general->select_buttons.push_back(defaultSecondSelectButtons);
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////
  // processing of select buttons...

  status.select_code_str.assign(skin_general->select_buttons.size(), undefinedSelectDigit);  // initialise empty select code string

  // check that there are enough select key code combinations for the number of songs on screen...

  uint32_t visible_title_strips { 0 };

  for (auto &i : skin_display_object)
  {
    if (dynamic_cast<TitleStripDisplayClass*>(i) != nullptr) visible_title_strips++;
  }

  uint32_t select_codes  { 1 };

  for (auto &s : skin_general->select_buttons)
  {
    select_codes *= s.size();
  }

  uint32_t selectable_entries { visible_title_strips };

  if (skin_general->album_mode == false)
  {
    selectable_entries *= skin_general->songs_per_title_strip;
  }

  if (select_codes < selectable_entries) error("Not enough select key combinations (%d) for number of selectable entries (%d)", select_codes, selectable_entries);

  // compute bases for each select digit...
  for (auto b = 0; b < skin_general->select_buttons.size(); ++b)
  {
    uint32_t base {1};
    if (skin_general->select_buttons_sequence == select_buttons_sequence_e::RowCol)
    {
      for (auto x = b+1; x < skin_general->select_buttons.size(); ++x)
      {
         base *= skin_general->select_buttons.at(x).size();
      }
    }
    else
    {
      for (auto x = 0; x < b; ++x)
      {
         base *= skin_general->select_buttons.at(x).size();
      }
    }
    select_digit_base.push_back(base); // base of this digit is product of number of select codes all lower digits
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////

  status.first_visible_title_strip_str = to_string(1 + TitleStripDisplayClass::start_title_strip);
  status.last_visible_title_strip_str = to_string(TitleStripDisplayClass::start_title_strip + skin_general->num_title_strips);

  // unspecified text max_width will default to zero, so force them to be the width of the title_strip they're on...
  if (skin_general->artist_text.max_width == 0) skin_general->artist_text.max_width = skin_general->title_strip_size.x.val;
  if (skin_general->album_text.max_width == 0)  skin_general->album_text.max_width  = skin_general->title_strip_size.x.val;
  for (auto &e : skin_general->extra_text)
  {
    if (e.max_width == 0) e.max_width  = skin_general->title_strip_size.x.val;
  }
  if (skin_general->song_text.max_width == 0)   skin_general->song_text.max_width   = skin_general->title_strip_size.x.val;

  // check for out-of-range font numbers...if so, make them the system font number (0)...
  if (skin_general->artist_text.font_number >= fonts.size()) skin_general->artist_text.font_number = SystemFontNumber;
  if (skin_general->album_text.font_number >= fonts.size())  skin_general->album_text.font_number  = SystemFontNumber;
  for (auto &e : skin_general->extra_text)
  {
    if (e.font_number >= fonts.size()) e.font_number  = SystemFontNumber;
  }
  if (skin_general->song_text.font_number >= fonts.size())   skin_general->song_text.font_number   = SystemFontNumber;

  if (skin_general->paired_song_text.font_number == UndefinedFontNumber) // not defined, so make it the same as song_text
  {
    skin_general->paired_song_text = skin_general->song_text;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////

  // initialise the display objects now that we have all the config parameters...

  if (joystick->enabled)
  {
    dynamics2_t obj_size { SetSizeToTitleStrip(dynamic_cast<DisplayBaseClass*>(joystick)) };
    joystick->init(obj_size, StatusEvent_joystick);

    skin_general->select_mode = select_mode_e::JoyStick;
    
    // Input->joystick_installed = true;
  }

  for (auto &i : skin_display_object)
  {
    if (dynamic_cast<TitleStripDisplayClass*>(i) != nullptr)
    {
      i->init(skin_general->title_strip_size, StatusEvent_titleStrips);
    }

    if (dynamic_cast<TouchSongDisplayClass*>(i) != nullptr)
    {
      if (dynamic_cast<TouchSongDisplayClass*>(i)->enabled == true) // [touch song] enabled is true defined, so enable TouchSong mode
      {
        skin_general->select_mode = select_mode_e::TouchSong;

        dynamics2_t obj_size { SetSizeToTitleStrip(i) };
        i->init(obj_size, StatusEvent_ButtonChange);

      }
    }

    if (dynamic_cast<BitmapDisplayClass*>(i) != nullptr)
    {
      i->init({}, StatusEvent_bitmap);
    }

    if (dynamic_cast<SpectrumAnalyserDisplayClass*>(i) != nullptr)
    {
      i->init({}, StatusEvent_spectrum_analyser);
    }

    if (dynamic_cast<StatusDisplayClass*>(i) != nullptr)
    {
      i->init({}, StatusEvent_status);
    }

  }

  ///////////////////////////////////////////////////////////////////////////////////////////////

  // now for the joystick / touch_song object(s) we need to populate its title_strip entry position
  // lookup table with (x,y) co-ordinates for each song entry in the display...

  if (joystick->enabled)
  {
    SetTitleStripPositions(dynamic_cast<DisplayBaseClass*>(joystick));
  }

  for (auto &j : skin_display_object)
  {
    if (dynamic_cast<TouchSongDisplayClass*>(j) != nullptr)
    {
      SetTitleStripPositions(j);
      skin_touch_song = static_cast<TouchSongDisplayClass*>(j);
    }
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////

  // check if we have any joystick or touch_song objects defined...
  // then choose select mode based on those and whether we have a touchscreen...

  if ((skin_general->select_mode == select_mode_e::TouchSong) && (Input->touch_active == false) && (Input->mouse_active == false)) // if we can't install touchscreen or don't have a mouse in touch song mode, we fall back to joystick or button mode...
  {
    if (joystick->enabled)
    {
      skin_general->select_mode = select_mode_e::JoyStick;
    }
    else
    {
      skin_general->select_mode = select_mode_e::SelectCode;
    }
  }

  // after establishing select mode, if it's joystick we must turn off auto select...
  if (skin_general->select_mode == select_mode_e::JoyStick)
  {
    skin_general->auto_select = false; // a joystick defined means auto select must be turned off
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////
  // miscellaneous stuff...

  status.playqueue_space_str = PlayQueue->RemainingSpaceStr();

  ///////////////////////////////////////////////////////////////////////////////////////////////

  #if 0
  // check for duplicated button mappings...
  for (uint32_t b1 = 0; b1 < NUM_BUTTONS; ++b1)
  {
    if (buttons->button[b1].type == input_type_e::Touch) continue; // Touch don't count
    for (uint32_t b2 = 0; b2 < NUM_BUTTONS; ++b2)
    {
      if (b1 == b2) continue; // don't compare a button with itself
      if (buttons->button[b1].type == buttons->button[b2].type)
      {
        if (buttons->button[b1].param == buttons->button[b2].param)
        {
          error("Duplicated Button mapping : %s and %s", buttons->button.at(b1).name.c_str(), buttons->button[b2].name.c_str());
        }
      }
    }
  }
  #endif

}

void TouchScreenConfigClass::cfgRead(string line)
{
  if (GetParam(line, cfgKeyword_Enable, enabled)) return;
  // if there are touch min and/or max present in the ini file we assume the touch has been previously calibrated...
  if (GetParam(line, cfgKeyword_TouchTopLeft, TouchScreenConfigClass::touch_tl))
  {
    ConfigBaseClass::touch_tl = TouchScreenConfigClass::touch_tl; // ConfigBaseClass::touch_tl is used internally (and could be swapped)
    tl_calibrated = true;
    return;
  }
  if (GetParam(line, cfgKeyword_TouchBottomRight, TouchScreenConfigClass::touch_br))
  {
    ConfigBaseClass::touch_br = TouchScreenConfigClass::touch_br; // ConfigBaseClass::touch_br is used internally (and could be swapped)
    br_calibrated = true;
    return;
  }
}

void TouchScreenConfigClass::cfgWrite(ofstream &strm)
{
  PutParam(strm, cfgKeyword_Enable, enabled);
  if (calibrated)
  {
    PutParam(strm, cfgKeyword_TouchTopLeft, TouchScreenConfigClass::touch_tl);
    PutParam(strm, cfgKeyword_TouchBottomRight, TouchScreenConfigClass::touch_br);
  }
}
