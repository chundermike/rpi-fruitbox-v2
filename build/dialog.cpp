#include "fruitbox.hpp"
#include "dialog_font.hpp"

using namespace std;

#define BUTTON_PRESSED          0x20000000

constexpr char fruitboxPiPre4ExeStr[]          { "./rpi/fruitbox" };
#ifdef _RPI4_32
constexpr char fruitboxPi4ExeStr[]             { "./rpi4_32/fruitbox" };
#else
constexpr char fruitboxPi4ExeStr[]             { "./rpi4/fruitbox" };
#endif
constexpr char ReleaseNotesStr[]               { "Release Notes" };
constexpr char releaseNotesFilename[]          { "./release_notes.txt" };
constexpr char SystemMoveStr[]                 { "mv " };
constexpr char DeleteFileStr[]                 { "rm " };
constexpr char WritePermissionExeStr[]         { "chmod +x " };
constexpr char releaseNotesFileUrl[]           { "https://raw.githubusercontent.com/chundermike/rpi-fruitbox-v2/master/release_notes.txt" };
constexpr char fruitboxPiPre4ExecutableUrl[]   { "https://raw.githubusercontent.com/chundermike/rpi-fruitbox-v2/master/rpi/fruitbox" };
#ifdef _RPI4_32
constexpr char fruitboxPi4ExecutableUrl[]      { "https://raw.githubusercontent.com/chundermike/rpi-fruitbox-v2/master/rpi4_32/fruitbox" };
#else
constexpr char fruitboxPi4ExecutableUrl[]      { "https://raw.githubusercontent.com/chundermike/rpi-fruitbox-v2/master/rpi4/fruitbox" };
#endif
constexpr char Keyword_Version[]               { "Version" };
constexpr char ThisVersionStr[]                { "This version ... " };
constexpr char LatestVersionStr[]              { "Latest version ... " };
constexpr char CheckingStr[]                   { "checking ... " };
constexpr char VersionStr[]                    { "Version " };
constexpr char NotFoundStr[]                   { "not found" };
constexpr char UnknownStr[]                    { "unknown" };
constexpr char DownloadSuccessStr[]            { " downloaded successfully!  Awesome" };
constexpr char RestartStr[]                    { "Please restart fruitbox for update to take effect" };
constexpr char DownloadFailedStr[]             { " download failed!" };
constexpr char DownloadingStr[]                { "Downloading latest version " };
constexpr char CouldntBackupStr[]              { "Couldn't make local backup of fruitbox executable" };
constexpr char CheckInternetStr[]              { "...check your internet connection" };
constexpr char ConfirmDownloadStr[]            { "Download latest version?" };
constexpr char AlreadyLatestVersionStr[]       { "...you already have the latest version. Nice one" };

constexpr int32_t LogoSpinOffsetX       { -16 * 512 / 800 }; /*  svg centre offset * png width / svg width  */
constexpr int32_t LogoSpinOffsetY       { -70 * 512 / 800 }; /*  svg centre offset * png height / svg height */

const char *fruitboxExecutableUrl { fruitboxPiPre4ExecutableUrl };
const char *fruitboxExeStr        { fruitboxPiPre4ExeStr };
        
// special characters defined in fruitbox.ttf ...
string up_sym    { 24 };
string down_sym  { 25 };
string left_sym  { 26 };
string right_sym { 27 };
string back_sym  { 28 };

ALLEGRO_BITMAP *DialogBaseClass::bitmap {};
ALLEGRO_BITMAP *DialogBaseClass::backdrop_bm {};
ALLEGRO_FILE *DialogBaseClass::font_f {};
bool DialogBaseClass::touch_menu_active { false };

DialogButtonClass *DialogBaseClass::ButtonsMenuNavigate {};
DialogButtonClass *DialogBaseClass::ButtonsYesNoWhatsNew {};
DialogButtonClass *DialogBaseClass::ButtonsLeftRightSelect {};
DialogButtonClass *DialogBaseClass::ButtonsLeftRightOk {};
DialogButtonClass *DialogBaseClass::ButtonsOk {};
DialogButtonClass *DialogBaseClass::ButtonsYesNo {};
DialogButtonClass *DialogBaseClass::ButtonsKeyboard {};

ints2_t DialogBaseClass::bitmap_size {};
uint32_t DialogBaseClass::border_thickness {};
uint32_t DialogBaseClass::corner_radius {};
uint32_t DialogBaseClass::line_thickness {};
uint32_t DialogBaseClass::header_centre_y {};
ALLEGRO_COLOR DialogBaseClass::background_colour {};
ALLEGRO_COLOR DialogBaseClass::backdrop_blend_colour {};
ALLEGRO_COLOR DialogBaseClass::ghosted_text_colour {};
ALLEGRO_COLOR DialogBaseClass::header_text_colour {};
ALLEGRO_COLOR DialogBaseClass::highlight_colour {};
ALLEGRO_COLOR DialogBaseClass::body_text_colour {};
ALLEGRO_COLOR DialogBaseClass::line_colour {};
ALLEGRO_COLOR DialogBaseClass::button_text_colour {};
ALLEGRO_COLOR DialogBaseClass::footer_text_colour {};
int32_t DialogBaseClass::font_ascent {};
int32_t DialogBaseClass::font_descent {};
text_t DialogBaseClass::header_text {};
text_t DialogBaseClass::footer_text {};
text_t DialogBaseClass::body_text {};
text_t DialogBaseClass::button_text {};
uint32_t DialogBaseClass::button_width {};
uint32_t DialogBaseClass::button_height {};
uint32_t DialogBaseClass::button_spacing {};
uint32_t DialogBaseClass::button_pressed { BUTTON_NONE };
bool DialogBaseClass::ignore_button_release { false };
/*
draw button criterion...

1. If have touchscreen or mouse, need to draw navigation buttons
2. need to draw "OK"
*/

void DialogBaseClass::ActivateTouchControls(void)
{
  if (Input->touch_active || Input->mouse_active)
  {
    DialogBaseClass::touch_menu_active = true;
  }
  DialogBaseClass::ignore_button_release = true; // one shot for entering menu from (button pressed active) jukebox controls into (button released active) menu controls
}

void DialogBaseClass::RestoreButtonMappings(void)
{
  // cout << "RestoreButtonMappings" << endl;
  for (uint32_t b = 0; b < Config->buttons->button.size(); ++b)
  {
    Config->buttons->button[b].menu_touch_area = { 0, 0, 0, 0, nullptr }; // prevent detection if a new set of buttons is activated
    if (Config->buttons->button[b].menu_enable)
    {
      Config->buttons->button[b].menu_enable = false;
      Config->buttons->button[b] = Config->buttons->backup_button[b];
      // b.type = b.type_backup;
    }
  }
}

void DialogBaseClass::DeActivateTouchControls(void) 
{
  DialogBaseClass::touch_menu_active = false;
  // any button in the menu is restored to it's correct input type...
  // cout << "DeActivateTouchControls" << endl;
  DialogBaseClass::RestoreButtonMappings();
}

DialogBaseClass::DialogBaseClass(const string &t)
{
  DialogBaseClass();
  SetTitle(t);
}

DialogBaseClass::DialogBaseClass(void)
{
  if (DialogBaseClass::bitmap == nullptr) // only create once
  {
    // any dialog object created shares a common bitmap (the size of the display) which is overlayed onto the existing (jukebox) bitmap
    DialogBaseClass::bitmap_size.x = Display->display_size.width;
    DialogBaseClass::bitmap_size.y = Display->display_size.height;

    font_t f {};
    DialogBaseClass::bitmap = al_create_bitmap(DialogBaseClass::bitmap_size.x, DialogBaseClass::bitmap_size.y);
    // bitmaps_created++; log_file << "al_create_bitmap(" << DialogBaseClass::bitmap_size.x << "," << DialogBaseClass::bitmap_size.y << ") - " << bitmaps_created << " DialogBaseClass::DialogBaseClass" << endl;
    if (DialogBaseClass::bitmap == nullptr) error("Failed to create %d x %d dialog bitmap", DialogBaseClass::bitmap_size.x, DialogBaseClass::bitmap_size.y);

    DialogBaseClass::font_f = al_open_memfile(dialog_font_data, DIALOG_FONT_LEN, "rb");
    f.size = DialogBaseClass::bitmap_size.y / 16;
    if (DialogBaseClass::font_f == nullptr) error( "Failed to load dialog font file");
    if ((f.handle = al_load_ttf_font_f(DialogBaseClass::font_f, nullptr, -f.size, 0)) == nullptr) error("Failed to create dialog font");
    Config->fonts.push_back(f); // first font in the config font pool is this system font

    DialogBaseClass::font_ascent      = al_get_font_ascent(Config->fonts.at(SystemFontNumber).handle);
    DialogBaseClass::font_descent     = al_get_font_descent(Config->fonts.at(SystemFontNumber).handle);
    DialogBaseClass::border_thickness = DialogBaseClass::font_ascent / 2;
    DialogBaseClass::corner_radius    = DialogBaseClass::border_thickness / 4;
    DialogBaseClass::line_thickness   = Config->fonts.at(SystemFontNumber).size / 12;
    DialogBaseClass::button_height    = static_cast<uint32_t>(Config->fonts.at(SystemFontNumber).size);
    DialogBaseClass::button_width     = DialogBaseClass::bitmap_size.x / 8;
    DialogBaseClass::button_spacing   = DialogBaseClass::button_width / 4;

    uint32_t active_width { DialogBaseClass::bitmap_size.x - 2 * DialogBaseClass::border_thickness };

    uint32_t r { Config->ini_general->menu_colour.r };
    uint32_t g { Config->ini_general->menu_colour.g };
    uint32_t b { Config->ini_general->menu_colour.b };
    
    uint32_t br { Config->ini_general->menu_bk_colour.r };
    uint32_t bg { Config->ini_general->menu_bk_colour.g };
    uint32_t bb { Config->ini_general->menu_bk_colour.b };
    uint32_t ba { Config->ini_general->menu_bk_colour.a };
    
    DialogBaseClass::background_colour     = al_map_rgba(br, bg, bb, ba);  // dialog box background
    DialogBaseClass::header_text_colour    = al_map_rgba(r, g, b, 255);
    // DialogBaseClass::ghosted_text_colour   = al_map_rgba((128*br)/255, (128*bg)/255, (128*bb)/255, 255);// 64,  64,  64, 255);
    DialogBaseClass::ghosted_text_colour   = al_map_rgba(br, bg, bb, ba);// 64,  64,  64, 255);
    DialogBaseClass::body_text_colour      = al_map_rgba((180*r)/255, (180*g)/255, (180*b)/255, 255);//180, 180, 180, 255);
    DialogBaseClass::line_colour           = al_map_rgba((180*r)/255, (180*g)/255, (180*b)/255, 255);//180, 180, 180, 255);
    DialogBaseClass::button_text_colour    = al_map_rgba((180*r)/255, (180*g)/255, (180*b)/255, 255);//180, 180, 180, 255);
    DialogBaseClass::footer_text_colour    = al_map_rgba((220*r)/255, (220*g)/255, (220*b)/255, 255);//220, 220, 220, 255);
    DialogBaseClass::highlight_colour      = al_map_rgba((255*r)/255, (255*g)/255, (255*b)/255, 255);//255, 255, 255, 255);

    DialogBaseClass::backdrop_blend_colour = al_map_rgba(128, 128, 128, 128);

    SetText(DialogBaseClass::footer_text, SystemFontNumber, DialogBaseClass::footer_text_colour, ALLEGRO_ALIGN_RIGHT,  false, TextModeCondensed, false, -DialogBaseClass::border_thickness, 0, active_width);
    SetText(DialogBaseClass::header_text, SystemFontNumber, DialogBaseClass::header_text_colour, ALLEGRO_ALIGN_LEFT,   false, TextModeCondensed, false, DialogBaseClass::border_thickness,  0, active_width);
    SetText(DialogBaseClass::body_text,   SystemFontNumber, DialogBaseClass::body_text_colour,   ALLEGRO_ALIGN_LEFT,   false, TextModeCondensed, false, 0, 0, active_width);
    SetText(DialogBaseClass::button_text, SystemFontNumber, DialogBaseClass::button_text_colour, ALLEGRO_ALIGN_CENTRE, false, TextModeCondensed, false, 0, 0, 0);

    DialogBaseClass::ButtonsMenuNavigate = new DialogButtonClass(false);
    DialogBaseClass::ButtonsMenuNavigate->AddButton("Select", 1.0, BUTTON_SELECT);
    DialogBaseClass::ButtonsMenuNavigate->AddButton(right_sym, 0.5, BUTTON_RIGHT);
    DialogBaseClass::ButtonsMenuNavigate->AddButton(left_sym, 0.5, BUTTON_LEFT);
    DialogBaseClass::ButtonsMenuNavigate->AddButton(back_sym, 0.5, BUTTON_QUIT);

    DialogBaseClass::ButtonsYesNoWhatsNew = new DialogButtonClass(true);
    DialogBaseClass::ButtonsYesNoWhatsNew->AddButton("Yes", BUTTON_Y);
    DialogBaseClass::ButtonsYesNoWhatsNew->AddButton("No", BUTTON_N);
    DialogBaseClass::ButtonsYesNoWhatsNew->AddButton("What's New", 1.5, BUTTON_W);

    DialogBaseClass::ButtonsLeftRightSelect = new DialogButtonClass(false);
    DialogBaseClass::ButtonsLeftRightSelect->AddButton("Select", 1.0, BUTTON_SELECT);
    DialogBaseClass::ButtonsLeftRightSelect->AddButton(right_sym, 0.5, BUTTON_RIGHT);
    DialogBaseClass::ButtonsLeftRightSelect->AddButton(left_sym, 0.5, BUTTON_LEFT);

    DialogBaseClass::ButtonsLeftRightOk = new DialogButtonClass(false);
    DialogBaseClass::ButtonsLeftRightOk->AddButton("Ok", 1.0, BUTTON_SELECT);
    DialogBaseClass::ButtonsLeftRightOk->AddButton(right_sym, 0.5, BUTTON_RIGHT);
    DialogBaseClass::ButtonsLeftRightOk->AddButton(left_sym, 0.5, BUTTON_LEFT);

    DialogBaseClass::ButtonsOk = new DialogButtonClass(true);
    DialogBaseClass::ButtonsOk->AddButton("Ok", BUTTON_SELECT);

    DialogBaseClass::ButtonsYesNo = new DialogButtonClass(true);
    DialogBaseClass::ButtonsYesNo->AddButton("Yes", BUTTON_Y);
    DialogBaseClass::ButtonsYesNo->AddButton("No", BUTTON_N);

    uints2_t keyboard_bottom_right_first_row {
      DialogBaseClass::bitmap_size.x - 3 * DialogBaseClass::border_thickness, 
      DialogBaseClass::bitmap_size.y - 4 * (DialogBaseClass::button_height + DialogBaseClass::border_thickness) // two button rows from bottom
    };
    
    uints2_t keyboard_bottom_right_second_row {
      keyboard_bottom_right_first_row.x, 
      keyboard_bottom_right_first_row.y + (DialogBaseClass::button_height + DialogBaseClass::border_thickness), 
    };
    
    uints2_t keyboard_bottom_right_third_row {
      keyboard_bottom_right_second_row.x - DialogBaseClass::button_height, 
      keyboard_bottom_right_second_row.y + (DialogBaseClass::button_height + DialogBaseClass::border_thickness), 
    };
    
    uints2_t keyboard_bottom_right_fourth_row {
      keyboard_bottom_right_third_row.x + 2 * DialogBaseClass::button_height, 
      keyboard_bottom_right_third_row.y + (DialogBaseClass::button_height + DialogBaseClass::border_thickness), 
    };
    
    DialogBaseClass::ButtonsKeyboard = new DialogButtonClass(false);
    // DialogBaseClass::ButtonsKeyboard->AddButton("ENTER", keyboard_bottom_right_fourth_row, 1.25, BUTTON_SELECT);
    // DialogBaseClass::ButtonsKeyboard->AddButton(right_sym, 0.5, BUTTON_RIGHT);
    // DialogBaseClass::ButtonsKeyboard->AddButton(left_sym, 0.5, BUTTON_LEFT);
    // DialogBaseClass::ButtonsKeyboard->AddButton("Z", 0.5, BUTTON_Z);
    // DialogBaseClass::ButtonsKeyboard->AddButton("Y", 0.5, BUTTON_Y);
    // DialogBaseClass::ButtonsKeyboard->AddButton("X", 0.5, BUTTON_X);
    // DialogBaseClass::ButtonsKeyboard->AddButton("W", 0.5, BUTTON_W);
    // DialogBaseClass::ButtonsKeyboard->AddButton("V", 0.5, BUTTON_V);
    // DialogBaseClass::ButtonsKeyboard->AddButton("U", 0.5, BUTTON_U);
    // DialogBaseClass::ButtonsKeyboard->AddButton("T", keyboard_bottom_right_third_row, 0.5, BUTTON_T);
    // DialogBaseClass::ButtonsKeyboard->AddButton("S", 0.5, BUTTON_S);
    // DialogBaseClass::ButtonsKeyboard->AddButton("R", 0.5, BUTTON_R);
    // DialogBaseClass::ButtonsKeyboard->AddButton("Q", 0.5, BUTTON_Q);
    // DialogBaseClass::ButtonsKeyboard->AddButton("P", 0.5, BUTTON_P);
    // DialogBaseClass::ButtonsKeyboard->AddButton("O", 0.5, BUTTON_O);
    // DialogBaseClass::ButtonsKeyboard->AddButton("N", 0.5, BUTTON_N);
    // DialogBaseClass::ButtonsKeyboard->AddButton("M", 0.5, BUTTON_M);
    // DialogBaseClass::ButtonsKeyboard->AddButton("L", 0.5, BUTTON_L);
    // DialogBaseClass::ButtonsKeyboard->AddButton("K", 0.5, BUTTON_K);
    // DialogBaseClass::ButtonsKeyboard->AddButton("J", keyboard_bottom_right_second_row, 0.5, BUTTON_J);
    // DialogBaseClass::ButtonsKeyboard->AddButton("I", 0.5, BUTTON_I);
    // DialogBaseClass::ButtonsKeyboard->AddButton("H", 0.5, BUTTON_H);
    // DialogBaseClass::ButtonsKeyboard->AddButton("G", 0.5, BUTTON_G);
    // DialogBaseClass::ButtonsKeyboard->AddButton("F", 0.5, BUTTON_F);
    // DialogBaseClass::ButtonsKeyboard->AddButton("E", 0.5, BUTTON_E);
    // DialogBaseClass::ButtonsKeyboard->AddButton("D", 0.5, BUTTON_D);
    // DialogBaseClass::ButtonsKeyboard->AddButton("C", 0.5, BUTTON_C);
    // DialogBaseClass::ButtonsKeyboard->AddButton("B", 0.5, BUTTON_B);
    // DialogBaseClass::ButtonsKeyboard->AddButton("A", 0.5, BUTTON_A);
    // DialogBaseClass::ButtonsKeyboard->AddButton("9", keyboard_bottom_right_first_row, 0.5, BUTTON_9);
    // DialogBaseClass::ButtonsKeyboard->AddButton("8", 0.5, BUTTON_8);
    // DialogBaseClass::ButtonsKeyboard->AddButton("7", 0.5, BUTTON_7);
    // DialogBaseClass::ButtonsKeyboard->AddButton("6", 0.5, BUTTON_6);
    // DialogBaseClass::ButtonsKeyboard->AddButton("5", 0.5, BUTTON_5);
    // DialogBaseClass::ButtonsKeyboard->AddButton("4", 0.5, BUTTON_4);
    // DialogBaseClass::ButtonsKeyboard->AddButton("3", 0.5, BUTTON_3);
    // DialogBaseClass::ButtonsKeyboard->AddButton("2", 0.5, BUTTON_2);
    // DialogBaseClass::ButtonsKeyboard->AddButton("1", 0.5, BUTTON_1);
    // DialogBaseClass::ButtonsKeyboard->AddButton("0", 0.5, BUTTON_0);
    DialogBaseClass::ButtonsKeyboard->AddButton("ENTER", keyboard_bottom_right_fourth_row, 1.0, BUTTON_SELECT);
    DialogBaseClass::ButtonsKeyboard->AddButton(right_sym, 0.5, BUTTON_RIGHT);
    DialogBaseClass::ButtonsKeyboard->AddButton(left_sym, 0.5, BUTTON_LEFT);
    DialogBaseClass::ButtonsKeyboard->AddButton("M", 0.5, BUTTON_M);
    DialogBaseClass::ButtonsKeyboard->AddButton("N", 0.5, BUTTON_N);
    DialogBaseClass::ButtonsKeyboard->AddButton("B", 0.5, BUTTON_B);
    DialogBaseClass::ButtonsKeyboard->AddButton("V", 0.5, BUTTON_V);
    DialogBaseClass::ButtonsKeyboard->AddButton("C", 0.5, BUTTON_C);
    DialogBaseClass::ButtonsKeyboard->AddButton("X", 0.5, BUTTON_X);
    DialogBaseClass::ButtonsKeyboard->AddButton("Z", 0.5, BUTTON_Z);
    DialogBaseClass::ButtonsKeyboard->AddButton("L", keyboard_bottom_right_third_row, 0.5, BUTTON_L);
    DialogBaseClass::ButtonsKeyboard->AddButton("K", 0.5, BUTTON_K);
    DialogBaseClass::ButtonsKeyboard->AddButton("J", 0.5, BUTTON_J);
    DialogBaseClass::ButtonsKeyboard->AddButton("H", 0.5, BUTTON_H);
    DialogBaseClass::ButtonsKeyboard->AddButton("G", 0.5, BUTTON_G);
    DialogBaseClass::ButtonsKeyboard->AddButton("F", 0.5, BUTTON_F);
    DialogBaseClass::ButtonsKeyboard->AddButton("D", 0.5, BUTTON_D);
    DialogBaseClass::ButtonsKeyboard->AddButton("S", 0.5, BUTTON_S);
    DialogBaseClass::ButtonsKeyboard->AddButton("A", 0.5, BUTTON_A);
    DialogBaseClass::ButtonsKeyboard->AddButton("P", keyboard_bottom_right_second_row, 0.5, BUTTON_P);
    DialogBaseClass::ButtonsKeyboard->AddButton("O", 0.5, BUTTON_O);
    DialogBaseClass::ButtonsKeyboard->AddButton("I", 0.5, BUTTON_I);
    DialogBaseClass::ButtonsKeyboard->AddButton("U", 0.5, BUTTON_U);
    DialogBaseClass::ButtonsKeyboard->AddButton("Y", 0.5, BUTTON_Y);
    DialogBaseClass::ButtonsKeyboard->AddButton("T", 0.5, BUTTON_T);
    DialogBaseClass::ButtonsKeyboard->AddButton("R", 0.5, BUTTON_R);
    DialogBaseClass::ButtonsKeyboard->AddButton("E", 0.5, BUTTON_E);
    DialogBaseClass::ButtonsKeyboard->AddButton("W", 0.5, BUTTON_W);
    DialogBaseClass::ButtonsKeyboard->AddButton("Q", 0.5, BUTTON_Q);
    DialogBaseClass::ButtonsKeyboard->AddButton("9", keyboard_bottom_right_first_row, 0.5, BUTTON_9);
    DialogBaseClass::ButtonsKeyboard->AddButton("8", 0.5, BUTTON_8);
    DialogBaseClass::ButtonsKeyboard->AddButton("7", 0.5, BUTTON_7);
    DialogBaseClass::ButtonsKeyboard->AddButton("6", 0.5, BUTTON_6);
    DialogBaseClass::ButtonsKeyboard->AddButton("5", 0.5, BUTTON_5);
    DialogBaseClass::ButtonsKeyboard->AddButton("4", 0.5, BUTTON_4);
    DialogBaseClass::ButtonsKeyboard->AddButton("3", 0.5, BUTTON_3);
    DialogBaseClass::ButtonsKeyboard->AddButton("2", 0.5, BUTTON_2);
    DialogBaseClass::ButtonsKeyboard->AddButton("1", 0.5, BUTTON_1);
    DialogBaseClass::ButtonsKeyboard->AddButton("0", 0.5, BUTTON_0);
  }
}

DialogBaseClass::~DialogBaseClass()
{
}

void DialogBaseClass::SetText
(
  text_t &text,
  const int32_t font_number,
  const ALLEGRO_COLOR colour,
  const int32_t alignment,
  const bool capitalise,
  const int32_t mode,
  const bool quoted,
  const int32_t offset_x,
  const int32_t offset_y,
  const uint32_t max_width
)
{
  text.font_number = font_number;
  text.colour = colour;
  text.alignment = alignment;
  text.capitalise = capitalise;
  text.mode = mode;
  text.quoted = quoted;
  text.offset.x = offset_x;
  text.offset.y = offset_y;
  text.max_width = max_width;
}

void DialogBaseClass::DrawBackground(void)
{
  float disp_w { static_cast<float>(Display->display_size.width) };
  float disp_h { static_cast<float>(Display->display_size.height) };

  al_set_target_bitmap(DialogBaseClass::bitmap);
  al_clear_to_color(al_map_rgba(0,0,0,0));
  
  uint32_t bk_alpha { 255 };
  
  if (DisplayClass::jukebox_drawn)
  {
    bk_alpha = 220; // allow jukebox background to show through slightly
  }
  
  ALLEGRO_VERTEX v[] =
  {
    { 0     , 0     , 0, 0, 0, al_map_rgba(200, 200, 200, bk_alpha)}, //top left
    { disp_w, 0     , 0, 0, 0, al_map_rgba(128, 128, 128, bk_alpha)}, //top right
    { 0     , disp_h, 0, 0, 0, al_map_rgba(64, 64, 64, bk_alpha)}, //bottom left
    { disp_w, disp_h, 0, 0, 0, al_map_rgba(0, 0, 0, bk_alpha)}  //bottom right
  };
  al_draw_prim(v, NULL, NULL, 0, 4, ALLEGRO_PRIM_TRIANGLE_STRIP);

  // draw background bitmap if one specified (i.e. skin chooser)...
  if (DialogBaseClass::backdrop_bm != nullptr)
  {
    al_draw_tinted_scaled_bitmap(DialogBaseClass::backdrop_bm, DialogBaseClass::backdrop_blend_colour, 0, 0, al_get_bitmap_width(DialogBaseClass::backdrop_bm), al_get_bitmap_height(DialogBaseClass::backdrop_bm), 0, 0, DialogBaseClass::bitmap_size.x, DialogBaseClass::bitmap_size.y, 0);
  }

  float logo_w { static_cast<float>(al_get_bitmap_width(Display->fruitbox_logo_bm)) };
  float logo_h { static_cast<float>(al_get_bitmap_height(Display->fruitbox_logo_bm)) };

  al_draw_scaled_rotated_bitmap(Display->fruitbox_logo_bm, LogoSpinOffsetX + logo_w/2,
                                LogoSpinOffsetY + logo_h/2,
                                disp_w/2, disp_h/2,
                                disp_w/(4*logo_w), disp_w/(4*logo_h),
                                logo_angle, 0);
}

// area_t DialogBaseClass::Draw
// draw message/list box with header and footer only, and no backdrop bitmap
// returns size and position of body area
// (
  // const uint32_t body_items
// )
// {
  // return DialogBaseClass::Draw(body_items, nullptr);
// }

area_t DialogBaseClass::Draw
// draw message/list box with header and footer only
// also draw on-screen (touch) keyboard if required...
// returns size and position of body area
(
  const uint32_t body_items
)
{
  DrawBackground();

  area_t box {};

  box.w = static_cast<uint32_t>(width_scale * static_cast<double>(DialogBaseClass::bitmap_size.x));
  box.x = (DialogBaseClass::bitmap_size.x - box.w) / 2; // centered horizontally

  uint32_t num_lines {3 + body_items}; // header (+gap), body_items

  if (footer.size()) num_lines++; // add space for footer
  if (Buttons != nullptr) num_lines++; // add space for buttons

  box.h = num_lines * Config->fonts.at(SystemFontNumber).size;

  switch (vertical_offset)
  {
    case vertical_offset_e::Centre :
      box.y = (DialogBaseClass::bitmap_size.y - box.h) / 2;
      break;

    case vertical_offset_e::Bottom :
      box.y = DialogBaseClass::bitmap_size.y - box.h - Config->fonts.at(SystemFontNumber).size; // one font height above bottom of screen
      break;

    case vertical_offset_e::Top :
      box.y = 2*DialogBaseClass::border_thickness;
      break;
  }

  DialogBaseClass::header_centre_y = box.y + ((DialogBaseClass::border_thickness + Config->fonts.at(SystemFontNumber).size) / 2);
  
  al_draw_filled_rounded_rectangle(box.x, box.y, box.x + box.w, box.y + box.h, DialogBaseClass::corner_radius, DialogBaseClass::corner_radius, DialogBaseClass::background_colour);

  al_draw_rounded_rectangle(box.x, box.y, box.x + box.w, box.y + box.h, DialogBaseClass::corner_radius, DialogBaseClass::corner_radius, DialogBaseClass::line_colour, DialogBaseClass::line_thickness);

  uint32_t max_text_width { box.w - 2 * DialogBaseClass::border_thickness };
  DialogBaseClass::header_text.max_width = DialogBaseClass::footer_text.max_width = max_text_width;

  Display->Text(DialogBaseClass::bitmap, DialogBaseClass::header_text, DialogBaseClass::bitmap_size.x, box.x, box.y + DialogBaseClass::border_thickness - DialogBaseClass::font_descent, header);
  uints2_t line_start { box.x + DialogBaseClass::border_thickness, box.y + DialogBaseClass::border_thickness + Config->fonts.at(SystemFontNumber).size };
  Display->Text(DialogBaseClass::bitmap, DialogBaseClass::footer_text, DialogBaseClass::bitmap_size.x, -box.x, box.y + box.h - DialogBaseClass::border_thickness - Config->fonts.at(SystemFontNumber).size + DialogBaseClass::font_descent, footer);

  // area_t body defines an area of the body text...indented horizontally by 2*DialogBaseClass::border_thickness each side to give nice
  // gap when higlighted for SelectableList...
  area_t body {box.x + 2*DialogBaseClass::border_thickness, box.y + DialogBaseClass::border_thickness + Config->fonts.at(SystemFontNumber).size + DialogBaseClass::font_ascent, box.w - 4 * DialogBaseClass::border_thickness, body_items * Config->fonts.at(SystemFontNumber).size};

  al_draw_line(line_start.x, line_start.y, line_start.x + body.w + 2*DialogBaseClass::border_thickness, line_start.y, DialogBaseClass::line_colour, DialogBaseClass::line_thickness);

  if (Buttons != nullptr)
  {
    bool draw { false };
    uints2_t position { box.x + box.w - DialogBaseClass::border_thickness, box.y + box.h - DialogBaseClass::button_height - DialogBaseClass::border_thickness}; // bottom right corner of dialog box
    for (auto &b : Buttons->button)
    {
      if (b.position.x) // user-defined button position over-rides automatic position
      {
        position = b.position;
      }

      position.x -= b.width; // left-hand side of button (as first position.x is right hand side of dialog box)
      Buttons->Draw(b, position);
      position.x -= DialogBaseClass::button_spacing; // space between next button
    }
  }

  return body;
}

// void DialogBaseClass::DrawIndicator(const uint32_t x, const uint32_t y, const indicator_direction_e dir)
// {
  // uint32_t x2, x3, y2, y3;
  // uint32_t width { (3 * DialogBaseClass::border_thickness) / 2 };

  // switch (dir)
  // {
    // case indicator_direction_e::Left :
      // x2 = x;
      // x3 = x - width;
      // y2 = y + 2*width;
      // y3 = y + width;
      // break;

    // case indicator_direction_e::Right :
      // x2 = x;
      // x3 = x + width;
      // y2 = y + 2*width;
      // y3 = y + width;
      // break;

    // case indicator_direction_e::Up :
      // x2 = x - width;
      // x3 = x - 2*width;
      // y2 = y - width;
      // y3 = y;
      // break;

    // case indicator_direction_e::Down :
      // x2 = x - width;
      // x3 = x - 2*width;
      // y2 = y + width;
      // y3 = y;
      // break;
  // }
  // al_draw_filled_triangle(x3, y3, x2, y2, x, y, DialogBaseClass::background_colour);
  // al_draw_line(x, y, x2, y2, DialogBaseClass::line_colour, DialogBaseClass::line_thickness);
  // al_draw_line(x2, y2, x3, y3, DialogBaseClass::line_colour, DialogBaseClass::line_thickness);
  // al_draw_line(x3, y3, x, y, DialogBaseClass::line_colour, DialogBaseClass::line_thickness);
// }

void DialogBaseClass::Show(const bool flip_display)
// copy dialog bitmap to display backbuffer and flip display if required
{
  al_set_target_bitmap(al_get_backbuffer(Display->display));
  al_draw_bitmap(DialogBaseClass::bitmap, 0, 0, 0);
  if (flip_display) al_flip_display();
}

bool DialogBaseClass::Run(void)
{
  if (Buttons == nullptr)
  {
    return false;
  }
  else
  {
    return Buttons->Run();
  }
}

void DialogBaseClass::AttachButtons(DialogButtonClass *buttons)
{
  DetachButtons(); // remove any existing attached buttons
  Buttons = buttons; // attach new buttons
}

void DialogBaseClass::DetachButtons(void)
{
  DialogBaseClass::RestoreButtonMappings(); // make sure any previously attached buttons are removed
  Buttons = nullptr;
}

bool DialogBaseClass::EnableVirtualKeyboard(void)
{
  if (Input->touch_active || Input->mouse_active)
  {
    vertical_offset = vertical_offset_e::Top;  // make room for keyboard
    Buttons_backup = Buttons;
    AttachButtons(ButtonsKeyboard);
    return true;
  }
  return false;
}

bool DialogBaseClass::DisableVirtualKeyboard(void)
{
  if (Input->touch_active || Input->mouse_active)
  {
    vertical_offset = vertical_offset_e::Centre;
    AttachButtons(Buttons_backup);
    return true;
  }
  return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Simple Message dialog boxes

void DialogMessageClass::Draw(void)
{
  if (redraw == false) return;

  area_t body_area { DialogBaseClass::Draw(0) };
  if (show_on_draw) DialogBaseClass::Show(true);
  redraw = false; // don't need to draw it again (unless it changes)
}

void DialogMessageClass::Draw
(
  const string &body
)
{
  if (redraw == false) return;

  area_t body_area { DialogBaseClass::Draw(1) };

  DialogBaseClass::body_text.max_width = body_area.w;
  Display->Text(DialogBaseClass::bitmap, DialogBaseClass::body_text, DialogBaseClass::bitmap_size.x, body_area.x, body_area.y, body);
  if (show_on_draw) DialogBaseClass::Show(true);
  redraw = false; // don't need to draw it again (unless it changes)
}

void DialogMessageClass::Draw
(
  const vector<string> &body
)
{
  if (redraw == false) return;
  
  area_t body_area { DialogBaseClass::Draw(body.size()) };
  uint32_t body_y { 0 };

  DialogBaseClass::body_text.max_width = body_area.w;
  for (auto &b : body)
  {
    Display->Text(DialogBaseClass::bitmap, DialogBaseClass::body_text, DialogBaseClass::bitmap_size.x, body_area.x, body_area.y + body_y, b);
    body_y += Config->fonts.at(SystemFontNumber).size;
  }
  if (show_on_draw) DialogBaseClass::Show(true);
  redraw = false; // don't need to draw it again (unless it changes)
}

bool DialogMessageClass::Run(void)
{
  if (DialogBaseClass::Run())
  {
    redraw = true;
    if (Buttons->choice & BUTTON_PRESSED)
    {
      return false;
    }
    return true; // choice made
  }
  return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Button(s)

void DialogButtonClass::AddButton(const string &label, const uints2_t position, const float width_scale, const uint32_t code)
{
  uint32_t width { static_cast<uint32_t>(static_cast<float>(DialogBaseClass::button_width) * width_scale) };

  button.push_back({label, width, code, position});
}

void DialogButtonClass::AddButton(const string &label, const uints2_t position, const uint32_t code)
{
  AddButton(label, position, 1.0, code);
}

void DialogButtonClass::AddButton(const string &label, const float width_scale, const uint32_t code)
{
  AddButton(label, {0, 0}, width_scale, code);
}

void DialogButtonClass::AddButton(const string &label, const uint32_t code)
{
  AddButton(label, {0, 0}, 1.0, code);
}

bool DialogButtonClass::Run(void)
{
  bool left_right_sel { false };
  
  //set left_right_sel true if not in touch/mouse mode and buttons are of type left_right_select
  if (Input->touch_active || Input->mouse_active) // a touchscreen or mouse
  {
  }
  else if (left_right_select)
  {
    left_right_sel = true;
  }

  uint32_t btn = Input->CheckForButtonPress(); // non-blocking

  if (left_right_sel == false)
  {
    if (btn == BUTTON_NONE) return false; // no choice made
  }
  DialogBaseClass::button_pressed = btn; // if BUTTON_RELEASED bit set, button will not highlight :)
  
  if (btn & BUTTON_RELEASED) // released, so clear released flag
  {
    if (DialogBaseClass::ignore_button_release)
    {
      DialogBaseClass::ignore_button_release = false;
      return false;
    }

    btn &= ~BUTTON_RELEASED;
  }
  else // not released, so set pressed flag...
  {
    btn |= BUTTON_PRESSED;
  }

  if (left_right_sel == false)
  {
    choice = btn;

    if (btn & BUTTON_PRESSED)
    {
      return true; // to allow display to highlight pressed button
    }

    if (Input->keyboard_installed || Input->touch_active || Input->mouse_active) // a keyboard, touchscreen or mouse
    {
      return true; // choice made
    }

    return false; // no choice made
  }

  // here onwards is for left_right_select mode;
  // we don't have a real keyboard (or we do, but the button list is in left/right selection mode),
  // so use left/right to cycle through buttons, and any other key to select

  bool ret { false };

  if (first_run)
  {
    ret = true; // need to force true return first time we enter the menu to highlight the currently selected button)
    selected = button.size() - 1; // start at left most button
    first_run = false;
  }
  
  // set here in case no key pressed, but we still want to highlight current selection...
  // choice = button.at(selected).code | BUTTON_PRESSED;
  // DialogBaseClass::button_pressed = choice & ~BUTTON_PRESSED;

  switch (btn)
  {
    case (BUTTON_PRESSED | BUTTON_LEFT)  : // buttons are draw right to left 
      if (selected == button.size() - 1)
      {
        selected = 0;
      }
      else
      {
        selected++;
      }
      ret = true; // choice made
      break;

    case (BUTTON_PRESSED | BUTTON_RIGHT) :
      if (selected == 0)
      {
        selected = button.size() - 1;
      }
      else 
      {
        selected--; 
      }
      ret = true; // choice made
      break;

    case BUTTON_LEFT :
    case BUTTON_RIGHT :
      break; // exclude LEFT/RIGHT button releases from switch default
   
    default : // any other button confirms selection
      if ((btn & BUTTON_PRESSED) == 0)
      {
        choice = button.at(selected).code;
        first_run = true; // for next time
        return true; // choice made
      }
      break;
  }

  if (ret)
  {
    choice = button.at(selected).code | BUTTON_PRESSED;
    DialogBaseClass::button_pressed = choice & ~BUTTON_PRESSED;
  }


  return ret;
  // return true; // to allow display to highlight pressed button
  // return false; // no choice made
}

void DialogButtonClass::Draw
(
  const dialog_button_t &b, 
  const uints2_t position
)
{
  uint32_t width    { b.width };
  uint32_t height   { DialogBaseClass::button_height };

  // note : we don't check for redraw in this function as it's called by other functions which check redraw
  bool pressed { DialogBaseClass::button_pressed == b.code ? true : false };

  ALLEGRO_COLOR text_colour { pressed ? DialogBaseClass::background_colour : DialogBaseClass::button_text_colour };
  ALLEGRO_COLOR bk_colour { pressed ? DialogBaseClass::highlight_colour : DialogBaseClass::background_colour };

  al_draw_filled_rounded_rectangle(position.x, position.y, position.x + width, position.y + height, DialogBaseClass::corner_radius, DialogBaseClass::corner_radius, bk_colour);
  al_draw_rounded_rectangle(position.x, position.y, position.x + width, position.y + height, DialogBaseClass::corner_radius, DialogBaseClass::corner_radius, DialogBaseClass::line_colour, DialogBaseClass::line_thickness);

  DialogBaseClass::button_text.max_width = width - 2 * DialogBaseClass::border_thickness;
  DialogBaseClass::button_text.colour = text_colour;
  Display->Text(DialogBaseClass::bitmap, DialogBaseClass::button_text, width, position.x, position.y, b.label);

  // setup corresponding input button touch area...
  // NOTE THIS IS ONLY DONE WHEN A MENU IS RE-DRAWN (AND HENCE WHEN BUTTONS ARE REDRAWN)
  button_t *input_btn { &Config->buttons->button.at(b.code) };

  input_btn->menu_enable = true;
  input_btn->menu_touch_area = { position.x, position.y, width, height, nullptr };
  
  if (Input->touch_active || Input->mouse_active)
  {
    input_btn->type = input_type_e::Touch;
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Progress Bar

void DialogProgressBarClass::Draw
(
  const string &title,
  const uint32_t percent_complete
)
{
  if (redraw == false) return;

  header = title;

  area_t body_area { DialogBaseClass::Draw(0) };

  DialogBaseClass::body_text.max_width = body_area.w;

  uint32_t bar_x { body_area.x - DialogBaseClass::border_thickness };
  uint32_t bar_w { body_area.w + 2*DialogBaseClass::border_thickness };

  al_draw_line(bar_x, body_area.y, bar_x + ((bar_w * percent_complete) / 100), body_area.y, DialogBaseClass::line_colour, 4*DialogBaseClass::line_thickness);

  if (show_on_draw) DialogBaseClass::Show(true);
  // redraw = false; // don't need to draw it again (unless it changes)
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Fixed (not selectable) List

void DialogListClass::Draw
(
  const deque<string> list
)
{
  if (redraw == false) return;
  area_t body_area { DialogBaseClass::Draw(list.size()) };
  uint32_t list_y { 0 };

  DialogBaseClass::body_text.max_width = body_area.w;

  for (auto &l : list)
  {
    Display->Text(DialogBaseClass::bitmap, DialogBaseClass::body_text, DialogBaseClass::bitmap_size.x, body_area.x, body_area.y + list_y, l);
    list_y += Config->fonts.at(SystemFontNumber).size;
  }

  if (show_on_draw) DialogBaseClass::Show(true);
  redraw = false; // don't need to draw it again (unless it changes)
}

///////////////////////////////////////////////////////////////////////////////////////////////
// File Viewer

bool DialogFileViewClass::LoadFile
(
  const string &filename
)
{
  line.clear();
  string fline;
  file.open(filename, ios::in);
  if (file.is_open())
  {
    while (getline(file, fline))
    {
      fline.erase(std::remove(fline.begin(), fline.end(), 13), fline.end()); // remove CR (for non-linux text file)
      fline.erase(std::remove(fline.begin(), fline.end(), 10), fline.end()); // remove LF (for non-linux text file)
      line.push_back(fline);
    }
    first_visible_line = 0;
    num_visible_lines = 10;
    file.close();
    SetFooter(to_string(first_visible_line+1) + "/" + to_string(line.size()));
    return true;
  }
  return false;
}

void DialogFileViewClass::Draw(void)
{
  if (redraw == false) return;
  area_t body_area { DialogBaseClass::Draw(num_visible_lines) };
  uint32_t body_y { 0 };

  body_text.max_width = body_area.w;
  for (auto l = first_visible_line; l < first_visible_line + num_visible_lines; ++l)
  {
    if (l == line.size()) break;
    Display->Text(DialogBaseClass::bitmap, DialogBaseClass::body_text, DialogBaseClass::bitmap_size.x, body_area.x, body_area.y + body_y, line.at(l));
    body_y += Config->fonts.at(SystemFontNumber).size;
  }
  if (show_on_draw) DialogBaseClass::Show(true);
  redraw = false; // don't need to draw it again (unless it changes)
}

bool DialogFileViewClass::Run(void)
{
  if (DialogBaseClass::Run()) // answer given...
  {
    redraw = true;
    Draw();

    if (Buttons->choice & BUTTON_PRESSED) return false; // only act on button release
    
    switch (Buttons->choice)
    {
      case BUTTON_RIGHT : // effectively up
        first_visible_line++;
        break;

      case BUTTON_LEFT : // effectively down
        first_visible_line--;
        break;

      default :
        return true; // finished viewing
        break;
    }

// cout << "first_visible_line " << first_visible_line << endl;
    if (first_visible_line < 0)
    {
      first_visible_line = 0;
    }
    else if (first_visible_line >= line.size())
    {
      first_visible_line = line.size() - 1;
    }

    SetFooter(to_string(first_visible_line+1) + "/" + to_string(line.size()));
  }
  return false; // not finished viewing
}

///////////////////////////////////////////////////////////////////////////////////////////////
// User Selectable List

bool DialogSelectableListClass::Run(void)
{
  // state machine to allow the user to move up and down through the list. If item selected, run item func()
  // non-blocking key wait allows jukebox to run in background

  if (run_func != nullptr) // run the selected run function
  {
    if (run_func(run_func_param) == true) // run_func finished
    {
      if (exit_func != nullptr)
      {
        exit_func();
      }
      // cout << "1. RestoreButtonMappings" << endl;
      DialogBaseClass::RestoreButtonMappings();
      editing_selected_item = false;
      init_func = nullptr;
      run_func = nullptr;
      exit_func = nullptr;
      redraw_pending = true; // redraw below (after going back to engine first)
      redraw = true;
    }
  }
  else if (redraw_pending) // draw after run_func finished (can't do it above as need to return to engine before redraw) 
  {
    redraw_pending = false;
    Draw();
  }
  else // run the selectable list
  {
    if (DialogBaseClass::Run()) // answer given...
    {
      redraw = true;
      
      switch (Buttons->choice)
      {
        case BUTTON_LEFT : // effectively down
          while (1)
          {
            if (selected_item > 0)
            {
              selected_item--;
              if (first_visible_item > 0)
              {
                first_visible_item--;
              }
            }
            else // wrap to bottom of list
            {
              selected_item = list.size() - 1; // wrap to end of list
              first_visible_item = list.size() - num_visible_items;
            }
            if (list.at(selected_item).label.name.size() && (list.at(selected_item).disabled == false)) break; // continue moving up/left until non-empty entry (i.e. jump over gaps or disabled items)
          }
          Draw();
          break;

        case BUTTON_RIGHT :
          while (1)
          {
            if (selected_item < list.size() - 1)
            {
              selected_item++;
              if (selected_item >= num_visible_items)
              {
                first_visible_item++;
              }
            }
            else
            {
              first_visible_item = selected_item = 0; // wrap to top of list
            }
            if (list.at(selected_item).label.name.size() && (list.at(selected_item).disabled == false)) break; // continue moving up/left until non-empty entry (i.e. jump over gaps or disabled items)
          }
          Draw();
          break;

        // check for the following three buttons to navigate off the menu, since it could be from the Main Menu or Search Menu...
        case BUTTON_SEARCH :
        case BUTTON_MENU :
        case BUTTON_QUIT :
          editing_selected_item = false;
          return true;
        break;

        default :
          if ((Buttons->choice & BUTTON_PRESSED) == 0) // only change run function if button released
          {
            editing_selected_item = true;
            init_func = list.at(selected_item).label.init_func; // register the init function
            run_func = list.at(selected_item).label.run_func; // register the run function
            run_func_param = list.at(selected_item).label.run_func_param;
            exit_func = list.at(selected_item).label.exit_func; // register the exit function
            if (init_func != nullptr)
            {
              init_func();
            }
          }
          Draw(); // draw on press or release (for button highlight/unhighlight)
          break;
      }
    }
  }

  return false;
}

void DialogSelectableListClass::AddListItem(const dialog_list_item_label_t &label, const dialog_list_item_param_t &param)
{
  list.push_back({label, param});
  if (num_visible_items < max_visible_items) ++num_visible_items;
}

void DialogSelectableListClass::AddListItem(const dialog_list_item_label_t &label) // list entry with no editable parameter value
{
  AddListItem(label, {value_type_e::None, nullptr, 0, 0});
}

void DialogSelectableListClass::EnableListItem(uint32_t item, bool enable)
{
  if (item < list.size())
  {
    list.at(item).disabled = !enable;
  }
}

void DialogSelectableListClass::Draw(void)
{
  if (redraw == false) return;

  ALLEGRO_COLOR body_text_colour { DialogBaseClass::body_text.colour };
  area_t body_area { DialogBaseClass::Draw(num_visible_items) };
  uint32_t list_y { Config->fonts.at(SystemFontNumber).size * (selected_item - first_visible_item) };
  DialogBaseClass::body_text.max_width = body_area.w;

  // highlight currently selected entry...
  {
    uint32_t rx1 { body_area.x - DialogBaseClass::border_thickness };
    uint32_t ry1 { body_area.y + list_y };
    uint32_t ry2 { body_area.y + Config->fonts.at(SystemFontNumber).size + list_y };
    uint32_t rx2 { body_area.x + body_area.w + DialogBaseClass::border_thickness };
    
    al_draw_filled_rounded_rectangle(rx1, ry1, rx2, ry2, DialogBaseClass::corner_radius, DialogBaseClass::corner_radius, DialogBaseClass::highlight_colour);

    uint32_t tx { body_area.x - (3 * DialogBaseClass::border_thickness) - (2 * DialogBaseClass::line_thickness)};
    uint32_t tyu { body_area.y };
    uint32_t tyd { body_area.y + body_area.h };

    // if (first_visible_item > 0) // draw up arrow
    // {
      // DrawIndicator(tx, tyu, indicator_direction_e::Up);
    // }

    // if ((list.size() - first_visible_item) != num_visible_items) // draw down arrow
    // {
      // DrawIndicator(tx, tyd, indicator_direction_e::Down);
    // }
  }

  if (list.size() > num_visible_items) // draw scroll bar...
  {
    uint32_t bar_height = (Config->fonts.at(SystemFontNumber).size * num_visible_items * num_visible_items) / list.size();
    uint32_t bar_x1 = body_area.x + body_area.w + (5 * DialogBaseClass::border_thickness / 4);
    uint32_t bar_x2 = bar_x1 + DialogBaseClass::border_thickness / 2;
    uint32_t bar_y = body_area.y + (((1 + body_area.h - bar_height) * selected_item) / list.size());
    al_draw_filled_rounded_rectangle(bar_x1, body_area.y, bar_x2, body_area.y + body_area.h, DialogBaseClass::corner_radius, DialogBaseClass::corner_radius, DialogBaseClass::ghosted_text_colour);
    al_draw_filled_rounded_rectangle(bar_x1, bar_y, bar_x2, bar_y + bar_height, DialogBaseClass::corner_radius, DialogBaseClass::corner_radius, DialogBaseClass::header_text_colour);
  }

  // decide which portion of list (if it's large) is to be shown...
  uint32_t last_visible_item { first_visible_item + num_visible_items};

  // draw list names...
  list_y = 0;

  for (auto l = first_visible_item; l < last_visible_item; ++l)
  {
    if (l == selected_item)
    {
      DialogBaseClass::body_text.colour = DialogBaseClass::background_colour;
    }
    else
    {
      if (editing_selected_item || list.at(l).disabled) // grey out all other items if editing or item is disabled
      {
        DialogBaseClass::body_text.colour = DialogBaseClass::ghosted_text_colour;
      }
      else
      {
        DialogBaseClass::body_text.colour = body_text_colour;
      }
    }
    Display->Text(DialogBaseClass::bitmap, DialogBaseClass::body_text, DialogBaseClass::bitmap_size.x, body_area.x, body_area.y + list_y, list.at(l).label.name);
    list_y += Config->fonts.at(SystemFontNumber).size;
  }

  // draw list values...
  list_y = 0;

  DialogBaseClass::body_text.alignment = ALLEGRO_ALIGN_RIGHT;
  for (auto l = first_visible_item; l < last_visible_item; ++l)
  {
    if (l == selected_item)
    {
      DialogBaseClass::body_text.colour = DialogBaseClass::background_colour;
    }
    else
    {
      if (editing_selected_item || list.at(l).disabled) // grey out all other items if editing or item is disabled
      {
        DialogBaseClass::body_text.colour = DialogBaseClass::ghosted_text_colour;
      }
      else
      {
        DialogBaseClass::body_text.colour = DialogBaseClass::header_text_colour;
      }
    }
    
    string value_str {};
    switch (list.at(l).param.value_type)
    {
      case value_type_e::None :
      break;

      case value_type_e::Bool :
        value_str = EnableDisableStr(*reinterpret_cast<bool*>(list.at(l).param.value));
      break;
      
      case value_type_e::Uint32 :
        value_str = Uint32Str(*reinterpret_cast<uint32_t*>(list.at(l).param.value));
      break;

      case value_type_e::Float :
        value_str = FloatStr(*reinterpret_cast<float*>(list.at(l).param.value));
      break;

      case value_type_e::String :
        value_str = *reinterpret_cast<string*>(list.at(l).param.value);
      break;
      
      case value_type_e::AttractChoice :
        value_str = AttractChoiceStr(*reinterpret_cast<attract_choice_e*>(list.at(l).param.value));
      break;

      case value_type_e::Button :
        value_str = Config->buttons->button[list.at(l).label.run_func_param].val_str;
      break;
    };

    Display->Text(DialogBaseClass::bitmap, DialogBaseClass::body_text, DialogBaseClass::bitmap_size.x, -body_area.x, body_area.y + list_y, value_str);
    list_y += Config->fonts.at(SystemFontNumber).size;
  }
  DialogBaseClass::body_text.colour = body_text_colour;
  DialogBaseClass::body_text.alignment = ALLEGRO_ALIGN_LEFT;
  
  if (show_on_draw) 
  {
    DialogBaseClass::Show(true);
  }
  redraw = false; // don't need to draw it again (unless it changes)
}

enum class config_button_state_e
{
  wait_for_key,
  wait_for_release
};

bool DialogSelectableListClass::ConfigButton(uint32_t b)
{
  static config_button_state_e state { config_button_state_e::wait_for_key };
  uint32_t btn_press;
  
  switch (state)
  {
    case config_button_state_e::wait_for_key :
      // cout << "***** wait_for_key" << endl;
      btn_press = Input->CheckForButtonPress();
      if (btn_press & BUTTON_RAW)
      {
        // cout << "btn_press & BUTTON_RAW" << endl;
        if (btn_press & BUTTON_RELEASED)
        {
          break; // ignore button releases
        }
        uint32_t btn { btn_press & BUTTON_MASK };
        Config->buttons->button.at(b).val_str = Input->RawKeyName(btn_press);
        Config->buttons->backup_button[b] = Config->buttons->button[b];
        state = config_button_state_e::wait_for_release;
        redraw = true;
      }
      break;

    case config_button_state_e::wait_for_release :
      btn_press = Input->CheckForButtonPress();
      // cout << "***** wait_for_release " << endl;
      if (btn_press & BUTTON_RAW)
      {
      // cout << "BUTTON_RAW " << hex << btn_press << endl;
        redraw = true;
        if (btn_press & BUTTON_RELEASED) // only act on button release
        {
          state = config_button_state_e::wait_for_key;
          changed = true;
          // cout << "changed 1" << endl;
          return true;
        }
      }
      break;
  }

  return false;
}

bool DialogSelectableListClass::EditString(void)
{
  string *str { static_cast<string*>(list.at(selected_item).param.value) };
  uint32_t str_max_len = list.at(selected_item).param.max_value;
  static bool waiting_for_confirm_release { false };

  if (DialogBaseClass::Run()) // answer given...
  {
    redraw = true;

    if (waiting_for_confirm_release)
    {
      if ((Buttons->choice & BUTTON_PRESSED) == 0) // button release confirms entry
      {
        waiting_for_confirm_release = false;
        editing_selected_item = false;
        return true; // finished editing
      }
      return false;
    }

    if (Buttons->choice & BUTTON_PRESSED)
    {
      uint32_t b { Buttons->choice & ~BUTTON_PRESSED };

      if ((b >= BUTTON_A) && (b <= BUTTON_Z))
      {
        if (str->size() < str_max_len)
        {
          *str += static_cast<char>(b - BUTTON_A + 'A');
        }
        changed = true;
        return false; // not finished editing
      }

      if ((b >= BUTTON_0) && (b <= BUTTON_9))
      {
        if (str->size() < str_max_len)
        {
          *str += static_cast<char>(b - BUTTON_0 + '0');
        }
        changed = true;
        return false; // not finished editing
      }
      
      if (b == BUTTON_RIGHT) // emulate space
      {
        if (str->size() < str_max_len)
        {
          *str += static_cast<char>(' ');
        }
        changed = true;
        return false; // not finished editing
      }
      
      if (b == BUTTON_LEFT) // emulate delete
      {
        if (!str->empty()) str->pop_back();
        changed = true;
        return false; // not finished editing
      }

      // ...any other (pressed) button confirms selection...
      waiting_for_confirm_release = true;
    }
  }
  return false;
}

template <typename T> bool DialogSelectableListClass::Edit(void)
{
  T *v    { reinterpret_cast<T*>(list.at(selected_item).param.value) };
  T v_min {};
  T v_max {};

  // if ((is_same<T, bool>::value == false) && (is_same<T, attract_choice_e>::value == false))
  if (is_same<T, bool>::value == false)
  {
    v_min = static_cast<T>(list.at(selected_item).param.min_value);
    v_max = static_cast<T>(list.at(selected_item).param.max_value);
  }

  if (DialogBaseClass::Run()) // answer given...
  {
    redraw = true;

    if (Buttons->choice & BUTTON_PRESSED) return false; // only act on button release

    uint32_t b { Buttons->choice };

    switch (b)
    {
      case BUTTON_LEFT :
        if (is_same<T, bool>::value == true)
        {
          *v = false;
          // *v = !(*v);
        }
        else
        {
          if (*v > v_min) *v -= 1;
        }
        changed = true;
        break;

      case BUTTON_RIGHT :
        if (is_same<T, bool>::value == true)
        {
          *v = true;
          // *v = !(*v);
        }
        else
        {
          if (*v < v_max) *v += 1;
        }
        changed = true;
        break;

      default :
        // any other (pressed) button finishes editing...
        editing_selected_item = false;
        return true; // finished editing
        break;
    }
  }
  return false; // not finished editing
}

template bool DialogSelectableListClass::Edit<uint32_t>(void);
template bool DialogSelectableListClass::Edit<float>(void);
template bool DialogSelectableListClass::Edit<bool>(void);
// template bool DialogSelectableListClass::Edit<attract_choice_e>(void);

string DialogSelectableListClass::Uint32Str(uint32_t value)
{
  return to_string(value);
}

string DialogSelectableListClass::FloatStr(float value)
{
  stringstream s {};
  
  s << setw(2) << value;
  
  return s.str();
}

string DialogSelectableListClass::AttractChoiceStr(attract_choice_e value)
{
  return AttractChoiceString(value);
}

string DialogSelectableListClass::EnableDisableStr(bool value)
{
  return EnableDisable(value);
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Skin Chooser

string DialogSkinChooserClass::Run(void)
{
  uint32_t current_skin { 0 };
  bool done { false };

  DialogBaseClass::ActivateTouchControls();
  DialogBaseClass::ignore_button_release = false;

  // File list has already been read from fruitbox.ini
  // and files string vector is Config->ini_skin_list->skin_file[]

  if (Config->ini_skin_list->skin_file.size() == 0)
  {
    vector<string> message {};
    message.push_back("No valid File entries in ini file '" + Config->ini_filename + "' [skins] section...");
    message.push_back("");
    message.push_back("Either specify valid File entries in '" + Config->ini_filename + "' [skins] section");
    message.push_back("or run fruitbox with the --skin <file> argument to specify a skin.");
    error(message);
  }

  uint32_t frame_ms { 1000 / static_cast<uint32_t>(display_refresh_rate) };
  uint32_t timeout_ms = Config->ini_general->skin_chooser_timeout.ticks * frame_ms;

  time_t start_time = time(nullptr); // in seconds
  
  if (Config->ini_skin_list->skin_file.size() > 1) // only allow user to select if more than one entry...
  {
    // allow user to select skin...
    while (done == false)
    {
      LoadSkin(Config->ini_skin_list->skin_file.at(current_skin));
      while (DialogBaseClass::Run() == false) { // wait here until button is pressed
        Draw(skin_desc);
        if (timeout_ms) // only timeout if a timeout value has been specified
        {
          if ((time(nullptr) - start_time) > (timeout_ms / 1000) )
          {
            done = true;
            break;
          }
        }
      };

      if (done == false) // not timed out
      {
        switch (Buttons->choice)
        {
          case BUTTON_LEFT :
            if (current_skin == 0)
            {
              current_skin = Config->ini_skin_list->skin_file.size() - 1;
            }
            else
            {
              current_skin--;
            }
            LoadSkin(Config->ini_skin_list->skin_file.at(current_skin));
            start_time = time(nullptr);
            break;

          case BUTTON_RIGHT :
            if (current_skin == Config->ini_skin_list->skin_file.size() - 1)
            {
              current_skin = 0;
            }
            else
            {
              current_skin++;
            }
            LoadSkin(Config->ini_skin_list->skin_file.at(current_skin));
            start_time = time(nullptr);
            break;

          default :
            if ((Buttons->choice & BUTTON_PRESSED) == 0) // only act on button release
            {
              done = true;
            }
            break;
        }
      }
    }

  }
  
  DialogBaseClass::DeActivateTouchControls();

  return Config->ini_skin_list->skin_file.at(current_skin);
}

void DialogSkinChooserClass::LoadSkin
(
  const string &filename
)
// load file, extract SkinName, SkinDescription(s), Screenshot, and draw the dialog
{
  ifstream skinFile;
  string line, str;
  string screenshot_str {defaultScreenshotFilename};

  skinFile.open(filename, ios::in);
  skin_name.clear();
  skin_version.clear();
  skin_desc.clear();
  if (skinFile.is_open())
  {
    GeneralConfigClass *general = new GeneralConfigClass();
    while (getline(skinFile, line))
    {
      if (line.empty()) continue;
      line.erase(0, line.find_first_not_of(" \t"));// remove leading whitespace
      if (line.empty()) continue;
      if (line.at(0) == cfgFile_comment) continue; // comment line

      if (general->GetParam(line, cfgKeyword_SkinName, skin_name, false)) continue;
      if (general->GetParam(line, cfgKeyword_SkinVersion, skin_version, false)) continue;
      if (general->GetParam(line, cfgKeyword_SkinDescription, str, false))
      {
        skin_desc.push_back(str);
        continue;
      }
      if (general->GetParam(line, cfgKeyword_Screenshot, screenshot_str, false)) continue;
    }

    // load screenshot bitmap
    {
      string screenshot_filename { filename.substr(0, filename.find_last_of("/")) + "/" + screenshot_str };
      if (DialogBaseClass::backdrop_bm)
      {
        al_destroy_bitmap(DialogBaseClass::backdrop_bm);
        DialogBaseClass::backdrop_bm = nullptr;
      }
      DialogBaseClass::backdrop_bm = al_load_bitmap(screenshot_filename.c_str());
    }

    skinFile.close();
    delete general;

    string skin_title { skin_name };
    if (skin_version.size())
    {
      skin_title += " (" + skin_version + ")";
    }
    SetTitle(skin_title);
    // SetFooter("<left> and <right> to change, any other button to select");
    SetFooter("");

    redraw = true;
    Draw(skin_desc);
  }
}

void DialogSkinChooserClass::Draw
(
  const vector<string> &body
)
{
  // if (redraw == false) return;

  area_t body_area { DialogBaseClass::Draw(body.size()) };
  uint32_t body_y { 0 };

  DialogBaseClass::body_text.max_width = body_area.w;

  for (auto &b : body)
  {
    Display->Text(DialogBaseClass::bitmap, DialogBaseClass::body_text, DialogBaseClass::bitmap_size.x, body_area.x, body_area.y + body_y, b);
    body_y += Config->fonts.at(SystemFontNumber).size;
  }

  if (Input->mouse_active) // draw mouse pointer...
  {
    // Config->mouse->update(StatusEvent_None);
    Config->mouse->draw();
  }
  DialogBaseClass::Show(true);
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Text Entry

#if 0
void DialogTextEntryClass::GetText
(
  string &text)
{
  // allow user to edit text string here
  
  DialogTextEntryClass::Draw(text);
}

void DialogTextEntryClass::Draw
(
  const string &text
)
{
  if (redraw == false) return;

  area_t body_area { DialogBaseClass::Draw(1) };

  uint32_t bar_x { body_area.x - DialogBaseClass::border_thickness };
  uint32_t bar_w { body_area.w + 2*DialogBaseClass::border_thickness };

  al_draw_line(bar_x, body_area.y, bar_x + bar_w , body_area.y, DialogBaseClass::header_text_colour, 4*DialogBaseClass::line_thickness);

  DialogBaseClass::body_text.max_width = body_area.w;
  Display->Text(DialogBaseClass::bitmap, DialogBaseClass::body_text, DialogBaseClass::bitmap_size.x, body_area.x, body_area.y, text);

  if (show_on_draw) DialogBaseClass::Show(true);
  redraw = false; // don't need to draw it again (unless it changes)
}
#endif

///////////////////////////////////////////////////////////////////////////////////////////////
// Calibrate Touch screen

#define TOUCH_POSITION  (8) /* calibrate targets are 1/8 of screen in from edges */

bool DialogCalibrateTouchClass::Run(void)
{
  ints2_t tl {};
  ints2_t target_pos { Display->display_size.width/TOUCH_POSITION, Display->display_size.height/TOUCH_POSITION };

  Input->calibrating_touch = true;
  // show_on_draw = true; // remove this as it's set in constructor

  uint32_t btn_press; // blocking (otherwise the calibration is too sluggish)

  Input->raw_mode = true;

  Draw(CalibrateTouchPressTargetStr, target_pos.x, target_pos.y);

  while (1)
  {
    btn_press = Input->WaitForButtonPress();
    if (btn_press & BUTTON_RAW_TOUCH)
    {
      if (btn_press & BUTTON_RELEASED)
      {
        continue; // ignore button releases
      }
      tl.x = btn_press & BUTTON_RAW_XTOUCH_MASK;
      tl.y = (btn_press >> BUTTON_RAW_YTOUCH_SHIFT) & BUTTON_RAW_YTOUCH_MASK;
      break;
    }
  }

  // bottom right
  
  target_pos = { ((TOUCH_POSITION - 1) * Display->display_size.width) / TOUCH_POSITION, ((TOUCH_POSITION - 1) * Display->display_size.height) / TOUCH_POSITION };
  Draw(CalibrateTouchPressTargetStr, target_pos.x, target_pos.y);
  while (1)
  {
    btn_press = Input->WaitForButtonPress();
    if (btn_press & BUTTON_RAW_TOUCH)
    {
      if (btn_press & BUTTON_RELEASED)
      {
        continue; // ignore button releases
      }
      ints2_t br
      {
        btn_press & BUTTON_RAW_XTOUCH_MASK,
        (btn_press >> BUTTON_RAW_YTOUCH_SHIFT) & BUTTON_RAW_YTOUCH_MASK
      };

      // now calculate touch screen edges by moving target touch positions by (1/TOUCH_POSITION)...
      ints2_t to_edge
      {
        (br.x - tl.x) / (TOUCH_POSITION - 2),
        (br.y - tl.y) / (TOUCH_POSITION - 2)
      };

      TouchScreenConfigClass::touch_tl.x = tl.x - to_edge.x;
      TouchScreenConfigClass::touch_tl.y = tl.y - to_edge.y;
      TouchScreenConfigClass::touch_br.x = br.x + to_edge.x;
      TouchScreenConfigClass::touch_br.y = br.y + to_edge.y;
      
      break;
    }
  }

  Input->raw_mode = false;

  Draw(CalibrateTouchCompleteStr);

  Config->touch_screen->calibrated = true;
  Input->calibrating_touch = false;

  this_thread::sleep_for(chrono::milliseconds(3000));

  return true; // finished
}
  
void DialogCalibrateTouchClass::Draw
(
  const string &body
)
{
  area_t body_area { DialogBaseClass::Draw(1) };

  DialogBaseClass::body_text.max_width = body_area.w;

  Display->Text(DialogBaseClass::bitmap, DialogBaseClass::body_text, DialogBaseClass::bitmap_size.x, body_area.x, body_area.y, body);

  if (show_on_draw) DialogBaseClass::Show(true);
}

void DialogCalibrateTouchClass::Draw
(
  const string &body,
  const int32_t target_x,
  const int32_t target_y
)
{
  area_t body_area { DialogBaseClass::Draw(1) };

  DialogBaseClass::body_text.max_width = body_area.w;

  Display->Text(DialogBaseClass::bitmap, DialogBaseClass::body_text, DialogBaseClass::bitmap_size.x, body_area.x, body_area.y, body);

  // draw crosshairs....
  al_draw_line(target_x,      target_y - 48, target_x,      target_y + 48, DialogBaseClass::highlight_colour, 8);
  al_draw_line(target_x - 48, target_y,      target_x + 48, target_y,      DialogBaseClass::highlight_colour, 8);
  al_draw_circle(target_x,target_y, 32, DialogBaseClass::highlight_colour, 8);

  if (show_on_draw) DialogBaseClass::Show(true);

}

///////////////////////////////////////////////////////////////////////////////////////////////
// Splash screen

bool DialogSplashScreenClass::Run(void)
{
  // Logo spin up..
  float ang_vel { static_cast<float>(spin) / 400 };
  float f { static_cast<float>(spin) / 100 };
  logo_angle += ang_vel;

  redraw = true;
  Draw();
  
  if (--spin > 0) // not finished yet
  {
    return false;
  }

  // spin-up finished...
  spin = MAX_SPIN; // for next time
  return true;

  // this_thread::sleep_for(chrono::milliseconds(1000));
  return true;
}

void DialogSplashScreenClass::Draw(void)
{

  if (redraw == false) return;

  // background contains the logo...
  DrawBackground();

  // draw version number...
  al_draw_text(Config->fonts.at(SystemFontNumber).handle, DialogBaseClass::body_text_colour, Display->display_size.width - 8, Display->display_size.height - Config->fonts.at(SystemFontNumber).size - 8, ALLEGRO_ALIGN_RIGHT, FRUITBOX_VERSION_NUMBER);

  if (show_on_draw) DialogBaseClass::Show(true);
  redraw = false; // don't need to draw it again (unless it changes)
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Software Update

DialogSoftwareUpdateClass::DialogSoftwareUpdateClass(const string &title)
{
  SetTitle(title);
  ViewReleaseNotes = new DialogFileViewClass(ReleaseNotesStr);
  ViewReleaseNotes->AttachButtons(ButtonsLeftRightOk);
}

bool DialogSoftwareUpdateClass::FindLatestVersion(const char* filename)
// find the first occurence of "version" (i.e. the latest) in the file, and read the subsequent version number string
{
  bool found_version { false };
  ifstream file;
  string line;

  file.open(filename, ios::in);
  if (!file.is_open()) return false;

  SoftwareUpdateConfigClass *read_version = new SoftwareUpdateConfigClass();

  while (getline(file, line) && !found_version)
  {
    if (line.empty()) continue;
    line.erase(0, line.find_first_not_of(" \t"));// remove leading whitespace
    if (line.empty()) continue;
    if (line.at(0) == cfgFile_comment) continue; // comment line
    if (read_version->GetParam(line, Keyword_Version, latest_version, true, true)) found_version = true;
  }

  delete read_version;
  file.close();

  return found_version;
}

bool DialogSoftwareUpdateClass::GetRemoteFile(const char *url, const char* filename)
{
  bool ok { false };
  FILE* file;
  if ((file = fopen( filename, "w")) != nullptr)
  {

    CURL* curl_handle = curl_easy_init();

// cout << "GetRemoteFile " << url << " : " << filename << endl;
    curl_easy_setopt(curl_handle, CURLOPT_FAILONERROR, true);
    curl_easy_setopt(curl_handle, CURLOPT_URL, url);
    curl_easy_setopt(curl_handle, CURLOPT_TIMEOUT, 60L);
    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, file) ;
    curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");

    if (curl_easy_perform(curl_handle) == CURLE_OK)
    {
      // cout << "OK!" << endl;
      ok = true;
    }

    curl_easy_cleanup(curl_handle);
    fclose(file);
  }

  return ok;
}

string system_cmd {};

bool DialogSoftwareUpdateClass::Run(void)
{
  switch (state)
  {
    case software_update_state_e::start :
      message.clear();
      redraw = true;
      message.push_back(string(ThisVersionStr) + string(FRUITBOX_VERSION_NUMBER));
      message.push_back(string(LatestVersionStr) + string(CheckingStr));
      DetachButtons();
      Draw(message); // no buttons
      state = software_update_state_e::request_version;
      break;

    case software_update_state_e::request_version :
      if (GetRemoteFile(releaseNotesFileUrl, releaseNotesFilename)) // try and download the release_notes.txt file from the rpi-fruitbox GitHub repo
      {
        state = software_update_state_e::check_version;
      }
      else // download failed
      {
        redraw = true;
        message.pop_back();
        message.push_back(string(LatestVersionStr) + string(NotFoundStr));
        message.push_back("");
        message.push_back(string(CheckInternetStr));
        AttachButtons(ButtonsOk);
        Draw(message);
        state = software_update_state_e::press_any_key;
      }
      break;

      break;

    case software_update_state_e::check_version :
      message.clear();
      redraw = true;
      message.push_back(string(ThisVersionStr) + string(FRUITBOX_VERSION_NUMBER));
      AttachButtons(ButtonsOk);
      if (FindLatestVersion(releaseNotesFilename)) // extract first version number from the release notes file just downloaded...
      {
        message.push_back(string(LatestVersionStr) + latest_version);
        message.push_back("");
        if (latest_version <= string(FRUITBOX_VERSION_NUMBER))
        {
          message.push_back(string(AlreadyLatestVersionStr));
          state = software_update_state_e::press_any_key;
        }
        else
        {
          message.push_back(string(ConfirmDownloadStr));
          AttachButtons(ButtonsYesNoWhatsNew);
          state = software_update_state_e::confirm_update;
          // cout << "confirm_update" << endl;
          break;
        }
        Draw(message);
      }
      else // not found version in release_notes.txt file
      {
        message.push_back(string(LatestVersionStr) + string(UnknownStr));
        message.push_back("");
        message.push_back(string(CheckInternetStr));
        state = software_update_state_e::press_any_key;
      }
      Draw(message);
      break;

    case software_update_state_e::confirm_update :
      if (DialogBaseClass::Run()) // answer given...
      {
        redraw = true;
        Draw(message);
          // cout << "debug2" << endl;
        if (Buttons->choice & BUTTON_PRESSED) return false; // only act on button release

        switch (Buttons->choice)
        {
          case BUTTON_W : // What's new - view release notes
          // cout << "debug3" << endl;
            ViewReleaseNotes->LoadFile(releaseNotesFilename);
            state = software_update_state_e::view_release_notes;
            break;

          case BUTTON_Y :// yes
          // cout << "debug4" << endl;
            state = software_update_state_e::request_fruitbox;
            break;

          default :
          // cout << "debug5" << endl;
            state = software_update_state_e::finish;
            break;
        }
      }
      break;
    
    case software_update_state_e::view_release_notes :
    
      ViewReleaseNotes->redraw = true;
      ViewReleaseNotes->Draw();

      if (ViewReleaseNotes->Run())
      {
        state = software_update_state_e::check_version;
      }
      break;

    case software_update_state_e::request_fruitbox :
      message.clear();
      redraw = true;
      {
        if (PiVersion >= 4)
        {
          fruitboxExecutableUrl = fruitboxPi4ExecutableUrl;
          fruitboxExeStr = fruitboxPi4ExeStr;
        }
        
        // move current fruitbox executable to fruitbox_<version_number> ...
        string fruitboxExeThisVerStr { string(fruitboxExeStr) + "_" + string(FRUITBOX_VERSION_NUMBER) };
        system_cmd = string(SystemMoveStr) + string(fruitboxExeStr) + " " + fruitboxExeThisVerStr;
        // cout << system_cmd << endl;
        system(system_cmd.c_str());
        
        ifstream ifile;
        ifile.open(fruitboxExeThisVerStr);
        if (ifile) // backup succeeded
        {
          ifile.close();
          message.push_back(string(DownloadingStr) + latest_version + " ...");
          state = software_update_state_e::download_fruitbox;
          DetachButtons();
        }
        else // couldn't backup old fruitbox executable
        {
          message.push_back(string(CouldntBackupStr));
          state = software_update_state_e::press_any_key;
          AttachButtons(ButtonsOk);
        }
      }
      Draw(message); //, false);
      break;

    case software_update_state_e::download_fruitbox :
      message.clear();
      redraw = true;
      {
        if (GetRemoteFile(fruitboxExecutableUrl, fruitboxExeStr)) // get fruitbox executable from github
        {
          message.push_back(string(VersionStr) + latest_version + string(DownloadSuccessStr));
          message.push_back("");
          message.push_back(string(RestartStr));
          // add exectute permission to fruitbox just downloaded...
          system_cmd = string(WritePermissionExeStr) + string(fruitboxExeStr);
        // cout << system_cmd << endl;
          system(system_cmd.c_str());
        }
        else // couldn't download fruitbox executable
        {
          message.push_back(string(VersionStr) + latest_version + string(DownloadFailedStr));
          message.push_back("");
          message.push_back(string(CheckInternetStr));

          // move the backup executable back to the original filename...
          // first delete any (partial) failed downloads...
          system_cmd = string(DeleteFileStr) + string(fruitboxExeStr);
        // cout << system_cmd << endl;
          system(system_cmd.c_str());
          // now move back fruitbox_<version_number> back to fruitbox...
          string fruitboxExeThisVerStr { string(fruitboxExeStr) + "_" + string(FRUITBOX_VERSION_NUMBER) };
          system_cmd = string(SystemMoveStr) + fruitboxExeThisVerStr + " " + string(fruitboxExeStr);
        // cout << system_cmd << endl;
          system(system_cmd.c_str());        
        }
      }

      state = software_update_state_e::press_any_key;
      AttachButtons(ButtonsOk);
      Draw(message);
      break;

    case software_update_state_e::press_any_key :
      if (DialogBaseClass::Run()) // answer given...
      {
        redraw = true;
        Draw(message);
        if (Buttons->choice & BUTTON_PRESSED)
        {
          return false;
        }
        else
        {
          state = software_update_state_e::finish;
        }
      }
      break;
      
    case software_update_state_e::finish :
      state = software_update_state_e::start;
      return true; // finished
      break;
  }

  return false; // not finished
}

void DialogSoftwareUpdateClass::Draw(const vector<string> &body) //, bool include_buttons)
{
  if (redraw == false) return;

  area_t body_area { DialogBaseClass::Draw(body.size()) };
  uint32_t body_y { 0 };

  DialogBaseClass::body_text.max_width = body_area.w;
  for (auto &b : body)
  {
    Display->Text(DialogBaseClass::bitmap, DialogBaseClass::body_text, DialogBaseClass::bitmap_size.x, body_area.x, body_area.y + body_y, b);
    body_y += Config->fonts.at(SystemFontNumber).size;
  }
  if (show_on_draw) DialogBaseClass::Show(true);
  redraw = false; // don't need to draw it again (unless it changes)
}
