// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.2.1
// LVGL VERSION: 8.3.4
// PROJECT: Display

#include "ui.h"
#include "ui_helpers.h"

///////////////////// VARIABLES ////////////////////
lv_obj_t * ui_Screen1;
lv_obj_t * ui_bBatteryVoltage;
lv_obj_t * ui_lBatteryVoltage;
lv_obj_t * ui_bBatteryTemperature;
lv_obj_t * ui_lBatteryTemperature;
lv_obj_t * ui_pShutdown;
lv_obj_t * ui_lShutdown;
lv_obj_t * ui_bCurrent;
lv_obj_t * ui_lCurrent;
void ui_event_pnextPage1(lv_event_t * e);
lv_obj_t * ui_pnextPage1;
lv_obj_t * ui_lnextPage1;
lv_obj_t * ui_Screen2;
lv_obj_t * ui_bMotorTemperature;
lv_obj_t * ui_lMotorTemperature;
lv_obj_t * ui_bAirTemperature;
lv_obj_t * ui_lAirTemperature;
lv_obj_t * ui_lTemp;
lv_obj_t * ui_lTemp1;
lv_obj_t * ui_pPowermode;
lv_obj_t * ui_lPowermode;
lv_obj_t * ui_bBrakePedal;
lv_obj_t * ui_bGasPedal;
lv_obj_t * ui_lSpeed;
void ui_event_pnextPage(lv_event_t * e);
lv_obj_t * ui_pnextPage;
lv_obj_t * ui_lnextPage;

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
    #error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP !=0
    #error "LV_COLOR_16_SWAP should be 0 to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////
void ui_event_pnextPage1(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(ui_Screen2, LV_SCR_LOAD_ANIM_FADE_ON, 0, 0);
    }
}
void ui_event_pnextPage(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(ui_Screen1, LV_SCR_LOAD_ANIM_FADE_ON, 0, 0);
    }
}

///////////////////// SCREENS ////////////////////
void ui_Screen1_screen_init(void)
{
    ui_Screen1 = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Screen1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_bBatteryVoltage = lv_bar_create(ui_Screen1);
    lv_bar_set_range(ui_bBatteryVoltage, 240, 403);
    lv_bar_set_value(ui_bBatteryVoltage, 300, LV_ANIM_OFF);
    lv_obj_set_width(ui_bBatteryVoltage, 80);
    lv_obj_set_height(ui_bBatteryVoltage, 30);
    lv_obj_set_x(ui_bBatteryVoltage, -45);
    lv_obj_set_y(ui_bBatteryVoltage, -45);
    lv_obj_set_align(ui_bBatteryVoltage, LV_ALIGN_CENTER);
    lv_obj_set_style_bg_color(ui_bBatteryVoltage, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_bBatteryVoltage, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui_bBatteryVoltage, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_bBatteryVoltage, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui_bBatteryVoltage, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_pad(ui_bBatteryVoltage, 1, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(ui_bBatteryVoltage, lv_color_hex(0x24C33D), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_bBatteryVoltage, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    ui_lBatteryVoltage = lv_label_create(ui_bBatteryVoltage);
    lv_obj_set_width(ui_lBatteryVoltage, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_lBatteryVoltage, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_lBatteryVoltage, LV_ALIGN_CENTER);
    lv_label_set_text(ui_lBatteryVoltage, "240V");
    lv_obj_set_style_text_color(ui_lBatteryVoltage, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_lBatteryVoltage, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_bBatteryTemperature = lv_bar_create(ui_Screen1);
    lv_bar_set_value(ui_bBatteryTemperature, 25, LV_ANIM_OFF);
    lv_obj_set_width(ui_bBatteryTemperature, 80);
    lv_obj_set_height(ui_bBatteryTemperature, 30);
    lv_obj_set_x(ui_bBatteryTemperature, 45);
    lv_obj_set_y(ui_bBatteryTemperature, -45);
    lv_obj_set_align(ui_bBatteryTemperature, LV_ALIGN_CENTER);
    lv_obj_set_style_bg_color(ui_bBatteryTemperature, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_bBatteryTemperature, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui_bBatteryTemperature, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_bBatteryTemperature, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui_bBatteryTemperature, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_pad(ui_bBatteryTemperature, 1, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(ui_bBatteryTemperature, lv_color_hex(0x24C33D), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_bBatteryTemperature, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    ui_lBatteryTemperature = lv_label_create(ui_bBatteryTemperature);
    lv_obj_set_width(ui_lBatteryTemperature, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_lBatteryTemperature, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_lBatteryTemperature, LV_ALIGN_CENTER);
    lv_label_set_text(ui_lBatteryTemperature, "20°C");
    lv_obj_set_style_text_color(ui_lBatteryTemperature, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_lBatteryTemperature, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_pShutdown = lv_obj_create(ui_Screen1);
    lv_obj_set_width(ui_pShutdown, 175);
    lv_obj_set_height(ui_pShutdown, 50);
    lv_obj_set_x(ui_pShutdown, 0);
    lv_obj_set_y(ui_pShutdown, -100);
    lv_obj_set_align(ui_pShutdown, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_pShutdown, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_pShutdown, lv_color_hex(0xC89632), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_pShutdown, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_pShutdown, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui_pShutdown, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_pShutdown, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui_pShutdown, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_pad(ui_pShutdown, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_lShutdown = lv_label_create(ui_pShutdown);
    lv_obj_set_width(ui_lShutdown, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_lShutdown, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_lShutdown, LV_ALIGN_CENTER);
    lv_label_set_text(ui_lShutdown, "HV Enabled");

    ui_bCurrent = lv_bar_create(ui_Screen1);
    lv_bar_set_range(ui_bCurrent, 0, 200);
    lv_bar_set_value(ui_bCurrent, 100, LV_ANIM_OFF);
    lv_obj_set_width(ui_bCurrent, 175);
    lv_obj_set_height(ui_bCurrent, 30);
    lv_obj_set_x(ui_bCurrent, 0);
    lv_obj_set_y(ui_bCurrent, 5);
    lv_obj_set_align(ui_bCurrent, LV_ALIGN_CENTER);
    lv_obj_set_style_bg_color(ui_bCurrent, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_bCurrent, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui_bCurrent, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_bCurrent, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui_bCurrent, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_pad(ui_bCurrent, 1, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(ui_bCurrent, lv_color_hex(0x243DC3), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_bCurrent, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    ui_lCurrent = lv_label_create(ui_bCurrent);
    lv_obj_set_width(ui_lCurrent, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_lCurrent, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_lCurrent, LV_ALIGN_CENTER);
    lv_label_set_text(ui_lCurrent, "100A");
    lv_obj_set_style_text_color(ui_lCurrent, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_lCurrent, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_pnextPage1 = lv_obj_create(ui_Screen1);
    lv_obj_set_width(ui_pnextPage1, 80);
    lv_obj_set_height(ui_pnextPage1, 30);
    lv_obj_set_x(ui_pnextPage1, 50);
    lv_obj_set_y(ui_pnextPage1, 100);
    lv_obj_set_align(ui_pnextPage1, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_pnextPage1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_pnextPage1, lv_color_hex(0xC89632), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_pnextPage1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_pnextPage1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui_pnextPage1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_pnextPage1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui_pnextPage1, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_pad(ui_pnextPage1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_lnextPage1 = lv_label_create(ui_pnextPage1);
    lv_obj_set_width(ui_lnextPage1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_lnextPage1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_lnextPage1, LV_ALIGN_CENTER);
    lv_label_set_text(ui_lnextPage1, "next Page");

    lv_obj_add_event_cb(ui_pnextPage1, ui_event_pnextPage1, LV_EVENT_ALL, NULL);

}
void ui_Screen2_screen_init(void)
{
    ui_Screen2 = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Screen2, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_bMotorTemperature = lv_bar_create(ui_Screen2);
    lv_bar_set_value(ui_bMotorTemperature, 25, LV_ANIM_OFF);
    lv_obj_set_width(ui_bMotorTemperature, 80);
    lv_obj_set_height(ui_bMotorTemperature, 30);
    lv_obj_set_x(ui_bMotorTemperature, -45);
    lv_obj_set_y(ui_bMotorTemperature, -20);
    lv_obj_set_align(ui_bMotorTemperature, LV_ALIGN_CENTER);
    lv_obj_set_style_bg_color(ui_bMotorTemperature, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_bMotorTemperature, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui_bMotorTemperature, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_bMotorTemperature, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui_bMotorTemperature, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_pad(ui_bMotorTemperature, 1, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(ui_bMotorTemperature, lv_color_hex(0x24C33D), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_bMotorTemperature, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    ui_lMotorTemperature = lv_label_create(ui_bMotorTemperature);
    lv_obj_set_width(ui_lMotorTemperature, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_lMotorTemperature, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_lMotorTemperature, LV_ALIGN_CENTER);
    lv_label_set_text(ui_lMotorTemperature, "20°C");
    lv_obj_set_style_text_color(ui_lMotorTemperature, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_lMotorTemperature, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_bAirTemperature = lv_bar_create(ui_Screen2);
    lv_bar_set_value(ui_bAirTemperature, 25, LV_ANIM_OFF);
    lv_obj_set_width(ui_bAirTemperature, 80);
    lv_obj_set_height(ui_bAirTemperature, 30);
    lv_obj_set_x(ui_bAirTemperature, 45);
    lv_obj_set_y(ui_bAirTemperature, -20);
    lv_obj_set_align(ui_bAirTemperature, LV_ALIGN_CENTER);
    lv_obj_set_style_bg_color(ui_bAirTemperature, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_bAirTemperature, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui_bAirTemperature, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_bAirTemperature, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui_bAirTemperature, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_pad(ui_bAirTemperature, 1, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(ui_bAirTemperature, lv_color_hex(0x24C33D), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_bAirTemperature, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    ui_lAirTemperature = lv_label_create(ui_bAirTemperature);
    lv_obj_set_width(ui_lAirTemperature, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_lAirTemperature, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_lAirTemperature, LV_ALIGN_CENTER);
    lv_label_set_text(ui_lAirTemperature, "20°C");
    lv_obj_set_style_text_color(ui_lAirTemperature, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_lAirTemperature, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_lTemp = lv_label_create(ui_Screen2);
    lv_obj_set_width(ui_lTemp, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_lTemp, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_lTemp, 45);
    lv_obj_set_y(ui_lTemp, -50);
    lv_obj_set_align(ui_lTemp, LV_ALIGN_CENTER);
    lv_label_set_text(ui_lTemp, "AirTemp");
    lv_obj_set_style_text_color(ui_lTemp, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_lTemp, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_lTemp1 = lv_label_create(ui_Screen2);
    lv_obj_set_width(ui_lTemp1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_lTemp1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_lTemp1, -45);
    lv_obj_set_y(ui_lTemp1, -50);
    lv_obj_set_align(ui_lTemp1, LV_ALIGN_CENTER);
    lv_label_set_text(ui_lTemp1, "MotorTemp");
    lv_obj_set_style_text_color(ui_lTemp1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_lTemp1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_pPowermode = lv_obj_create(ui_Screen2);
    lv_obj_set_width(ui_pPowermode, 175);
    lv_obj_set_height(ui_pPowermode, 50);
    lv_obj_set_x(ui_pPowermode, 0);
    lv_obj_set_y(ui_pPowermode, -100);
    lv_obj_set_align(ui_pPowermode, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_pPowermode, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_pPowermode, lv_color_hex(0xC89632), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_pPowermode, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_pPowermode, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui_pPowermode, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_pPowermode, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui_pPowermode, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_pad(ui_pPowermode, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_lPowermode = lv_label_create(ui_pPowermode);
    lv_obj_set_width(ui_lPowermode, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_lPowermode, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_lPowermode, LV_ALIGN_CENTER);
    lv_label_set_text(ui_lPowermode, "Fast");

    ui_bBrakePedal = lv_bar_create(ui_Screen2);
    lv_bar_set_value(ui_bBrakePedal, 25, LV_ANIM_OFF);
    lv_obj_set_width(ui_bBrakePedal, 30);
    lv_obj_set_height(ui_bBrakePedal, 80);
    lv_obj_set_x(ui_bBrakePedal, -70);
    lv_obj_set_y(ui_bBrakePedal, 80);
    lv_obj_set_align(ui_bBrakePedal, LV_ALIGN_CENTER);
    lv_obj_set_style_bg_color(ui_bBrakePedal, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_bBrakePedal, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui_bBrakePedal, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_bBrakePedal, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui_bBrakePedal, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_pad(ui_bBrakePedal, 1, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(ui_bBrakePedal, lv_color_hex(0xC3243D), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_bBrakePedal, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    ui_bGasPedal = lv_bar_create(ui_Screen2);
    lv_bar_set_value(ui_bGasPedal, 25, LV_ANIM_OFF);
    lv_obj_set_width(ui_bGasPedal, 30);
    lv_obj_set_height(ui_bGasPedal, 80);
    lv_obj_set_x(ui_bGasPedal, -30);
    lv_obj_set_y(ui_bGasPedal, 80);
    lv_obj_set_align(ui_bGasPedal, LV_ALIGN_CENTER);
    lv_obj_set_style_bg_color(ui_bGasPedal, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_bGasPedal, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui_bGasPedal, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_bGasPedal, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui_bGasPedal, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_pad(ui_bGasPedal, 1, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(ui_bGasPedal, lv_color_hex(0x24C33D), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_bGasPedal, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    ui_lSpeed = lv_label_create(ui_Screen2);
    lv_obj_set_width(ui_lSpeed, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_lSpeed, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_lSpeed, 50);
    lv_obj_set_y(ui_lSpeed, 55);
    lv_obj_set_align(ui_lSpeed, LV_ALIGN_CENTER);
    lv_label_set_text(ui_lSpeed, "100 km/h");
    lv_obj_set_style_outline_color(ui_lSpeed, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_lSpeed, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui_lSpeed, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_pad(ui_lSpeed, 5, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_pnextPage = lv_obj_create(ui_Screen2);
    lv_obj_set_width(ui_pnextPage, 80);
    lv_obj_set_height(ui_pnextPage, 30);
    lv_obj_set_x(ui_pnextPage, 50);
    lv_obj_set_y(ui_pnextPage, 100);
    lv_obj_set_align(ui_pnextPage, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_pnextPage, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_pnextPage, lv_color_hex(0xC89632), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_pnextPage, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_pnextPage, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui_pnextPage, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_pnextPage, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui_pnextPage, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_pad(ui_pnextPage, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_lnextPage = lv_label_create(ui_pnextPage);
    lv_obj_set_width(ui_lnextPage, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_lnextPage, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_lnextPage, LV_ALIGN_CENTER);
    lv_label_set_text(ui_lnextPage, "next Page");

    lv_obj_add_event_cb(ui_pnextPage, ui_event_pnextPage, LV_EVENT_ALL, NULL);

}

void ui_init(void)
{
    lv_disp_t * dispp = lv_disp_get_default();
    lv_theme_t * theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                               true, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    ui_Screen1_screen_init();
    ui_Screen2_screen_init();
    lv_disp_load_scr(ui_Screen1);
}
