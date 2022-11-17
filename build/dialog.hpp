#pragma once

#include "fruitbox.hpp"

using namespace std;

enum class vertical_offset_e
{
  Top,
  Centre,
  Bottom
};

enum class value_type_e
{
  None,
  Bool,
  String,
  Uint32,
  Float,
  AttractChoice,
  Button
};

enum class indicator_direction_e
{
  Left,
  Right,
  Up,
  Down
};

struct dialog_list_item_label_t
{
  string name {};
  void (*init_func)(void) {};
  bool (*run_func)(uint32_t param) {};
  uint32_t run_func_param {};
  void (*exit_func)(void) {};
};

struct dialog_list_item_param_t
{
  value_type_e value_type { value_type_e::None };
  void* value { nullptr };
  int32_t min_value { 0 };
  int32_t max_value { 0 };
};

struct dialog_list_item_t
{
  dialog_list_item_label_t label;
  dialog_list_item_param_t param;
  bool disabled { false };
};

struct dialog_button_t
{
  string label;
  uint32_t width;
  uint32_t code;
  uints2_t position {0, 0};
};

class DialogButtonClass
{
  friend class DialogBaseClass;

public:
  DialogButtonClass(bool lr_sel) { left_right_select = lr_sel; }
  void AddButton(const string &label, const uints2_t position, const float width_scale, const uint32_t code);
  void AddButton(const string &label, const uints2_t position, const uint32_t code);
  void AddButton(const string &label, const float width_scale, const uint32_t code);
  void AddButton(const string &label, const uint32_t code);
  void Draw(const dialog_button_t &b, const uints2_t position);
  bool Run(void);

  uint32_t choice { BUTTON_NONE };
  vector<dialog_button_t> button {};
private:
  bool left_right_select { false }; // use left/right to cycle through buttons rather than touch / direct keyboard input
  bool first_run { true };
  uint32_t selected { 0 };
};

class DialogBaseClass
{
public:
  DialogBaseClass(const string &title);
  DialogBaseClass(void);
  ~DialogBaseClass();
  void SetTitle(const string &title) { header = title; }
  void SetFooter(const string &title) { footer = title; }
  void Show(const bool flip_display);
  void AttachButtons(DialogButtonClass *buttons);
  void DetachButtons(void);
  bool EnableVirtualKeyboard(void);
  bool DisableVirtualKeyboard(void);

  static DialogButtonClass *ButtonsMenuNavigate;
  static DialogButtonClass *ButtonsYesNoWhatsNew;
  static DialogButtonClass *ButtonsLeftRightSelect;
  static DialogButtonClass *ButtonsLeftRightOk;
  static DialogButtonClass *ButtonsOk;
  static DialogButtonClass *ButtonsYesNo;
  static DialogButtonClass *ButtonsKeyboard;
  static ALLEGRO_BITMAP *bitmap;
  static ALLEGRO_BITMAP *backdrop_bm;
  static ALLEGRO_FILE *font_f;
  static bool touch_menu_active;
  static void ActivateTouchControls(void);
  static void DeActivateTouchControls(void);
  static void RestoreButtonMappings(void);

  static ints2_t bitmap_size;
  static uint32_t border_thickness;
  static uint32_t corner_radius;
  static uint32_t line_thickness;
  static uint32_t header_centre_y;
  static ALLEGRO_COLOR background_colour;
  static ALLEGRO_COLOR backdrop_blend_colour;
  static ALLEGRO_COLOR ghosted_text_colour;
  static ALLEGRO_COLOR header_text_colour;
  static ALLEGRO_COLOR highlight_colour;
  static ALLEGRO_COLOR body_text_colour;
  static ALLEGRO_COLOR line_colour;
  static ALLEGRO_COLOR button_text_colour;
  static ALLEGRO_COLOR footer_text_colour;
  static int32_t font_ascent;
  static int32_t font_descent;
  static text_t header_text;
  static text_t footer_text;
  static text_t body_text;
  static text_t button_text;
  static uint32_t button_width;
  static uint32_t button_height;
  static uint32_t button_spacing;
  static uint32_t button_pressed;
  static bool ignore_button_release;

  uint32_t fade_level;
  bool redraw { true }; // true = enables drawing in Draw() // MOVE TO PROTECTED AFTER RE-CODE OF TEST AND CONFIG BUTTONS
  bool redraw_pending { false }; // used to flag a redraw request on next display update
  bool show_on_draw { false }; // true = immediately flips display backbuffer to show dialog as soon as it's drawn
  DialogButtonClass *Buttons { nullptr };
  
protected:
  bool Run(void);
  area_t Draw(const uint32_t body_items);
  // void DrawIndicator(const uint32_t x, const uint32_t y, const indicator_direction_e dir);
  void DrawBackground(void);

  vertical_offset_e vertical_offset { vertical_offset_e::Centre };

  float logo_angle {};
  string header {};
  string footer {};
  double width_scale { 0.6 };

private:
  DialogButtonClass *Buttons_backup { nullptr };
  void SetText(text_t &text, const int32_t font_number,const ALLEGRO_COLOR colour,
               const int32_t alignment, const bool capitalise, const int32_t mode, const bool quoted,
               const int32_t offset_x, const int32_t offset_y, const uint32_t max_width);
               
};

class DialogMessageClass : public DialogBaseClass 
{
public:
  DialogMessageClass(const string &title)
  {
    SetTitle(title);
    AttachButtons(DialogBaseClass::ButtonsOk);
  }
  bool Run(void); // check for key press
  void Draw(void);
  void Draw(const string &body);
  void Draw(const vector<string> &body);
};

class DialogYesNoQuestionClass : public DialogMessageClass
{
public:
  DialogYesNoQuestionClass(const string &title) : DialogMessageClass { title }
  {
    AttachButtons(DialogBaseClass::ButtonsYesNo);
  }
};

class DialogProgressBarClass : public DialogBaseClass 
{
public:
  DialogProgressBarClass()
  {
    vertical_offset = vertical_offset_e::Bottom;
  }
  void Draw(const string &title, const uint32_t percent_complete);
};


class DialogFileViewClass : public DialogBaseClass 
{
public:
  DialogFileViewClass(const string &title)
  {
    SetTitle(title);
    AttachButtons(DialogBaseClass::ButtonsOk);
    width_scale = 0.95;
  }
  bool LoadFile(const string &filename);
  void Draw(void);
  bool Run(void);
private:
  ifstream file {};
  deque<uint32_t> page_offset {};
  vector<string> line {};
  int32_t first_visible_line {};
  uint32_t num_visible_lines {};
};


class DialogListClass : public DialogBaseClass 
{
public:
  DialogListClass(const string &title)
  {
    SetTitle(title);
    AttachButtons(DialogBaseClass::ButtonsMenuNavigate);
  }
  void Draw(const deque<string> list);
};


class DialogSelectableListClass : public DialogBaseClass 
{
public:
  DialogSelectableListClass(const string &title)
  {
    SetTitle(title);
    AttachButtons(DialogBaseClass::ButtonsMenuNavigate);
  }
  void AddListItem(const dialog_list_item_label_t &label);
  void AddListItem(const dialog_list_item_label_t &label, const dialog_list_item_param_t &param);
  void EnableListItem(uint32_t item, bool enable);
  bool Run(void);
  void Draw(void);
  bool EditString(void);
  bool ConfigButton(uint32_t b);
  template <typename T> bool Edit(void);
  string Uint32Str(uint32_t value);
  string FloatStr(float value);
  string AttractChoiceStr(attract_choice_e value);
  string EnableDisableStr(bool value);
  vector<dialog_list_item_t> list {};
  uint32_t selected_item {};
  bool changed { false };
private:
  bool editing_selected_item {};
  void (*exit_func)(void) {};
  bool (*run_func)(uint32_t param) {};
  void (*init_func)(void) {};
  uint32_t run_func_param {};
  uint32_t first_visible_item {};
  uint32_t num_visible_items {};
  uint32_t max_visible_items { 10 };
};


class DialogSkinChooserClass : public DialogBaseClass 
{
public:
  DialogSkinChooserClass(void)
  {
    AttachButtons(DialogBaseClass::ButtonsLeftRightSelect);
  }
  string Run(void);
private:
  void Draw(const vector<string> &body);
  void LoadSkin(const string &filename);
  private:
  string skin_name {};
  string skin_version {};
  vector<string> skin_desc {};
};


class DialogCalibrateTouchClass : public DialogBaseClass 
{
public:
  DialogCalibrateTouchClass(const string &title)
  {
    SetTitle(title);
    show_on_draw = true;
  }
  bool Run(void);
private:
  void Draw(const string &body);
  void Draw(const string &body, const int32_t target_x, const int32_t target_y);
};

#define MAX_SPIN 200

class DialogSplashScreenClass : public DialogBaseClass 
{
public:
  bool Run(void);
private:
  void Draw(void);
  uint32_t spin { MAX_SPIN };
};

enum class software_update_state_e
{
  start,
  request_version,
  check_version,
  confirm_update,
  view_release_notes,
  request_fruitbox,
  download_fruitbox,
  press_any_key,
  finish
};

class DialogSoftwareUpdateClass : public DialogBaseClass 
{
public:
  DialogSoftwareUpdateClass(const string &title);
  bool Run(void);
  void Draw(const vector<string> &body);
private:
  uint32_t selected { 0 };
  bool FindLatestVersion(const char* filename);
  bool GetRemoteFile(const char *url, const char *filename);
  software_update_state_e state { software_update_state_e::start };
  DialogFileViewClass *ViewReleaseNotes;

  vector<string> message {};
  string latest_version {};
};

