// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.2.1
// LVGL VERSION: 8.3.4
// PROJECT: Display

#ifndef _DISPLAY_UI_H
#define _DISPLAY_UI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

extern lv_obj_t * ui_Screen1;
extern lv_obj_t * ui_bBatteryVoltage;
extern lv_obj_t * ui_lBatteryVoltage;
extern lv_obj_t * ui_bBatteryTemperature;
extern lv_obj_t * ui_lBatteryTemperature;
extern lv_obj_t * ui_pShutdown;
extern lv_obj_t * ui_lShutdown;
extern lv_obj_t * ui_bCurrent;
extern lv_obj_t * ui_lCurrent;
void ui_event_pnextPage1(lv_event_t * e);
extern lv_obj_t * ui_pnextPage1;
extern lv_obj_t * ui_lnextPage1;
extern lv_obj_t * ui_Screen2;
extern lv_obj_t * ui_bMotorTemperature;
extern lv_obj_t * ui_lMotorTemperature;
extern lv_obj_t * ui_bAirTemperature;
extern lv_obj_t * ui_lAirTemperature;
extern lv_obj_t * ui_lTemp;
extern lv_obj_t * ui_lTemp1;
extern lv_obj_t * ui_pPowermode;
extern lv_obj_t * ui_lPowermode;
extern lv_obj_t * ui_bBrakePedal;
extern lv_obj_t * ui_bGasPedal;
extern lv_obj_t * ui_lSpeed;
void ui_event_pnextPage(lv_event_t * e);
extern lv_obj_t * ui_pnextPage;
extern lv_obj_t * ui_lnextPage;






void ui_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
