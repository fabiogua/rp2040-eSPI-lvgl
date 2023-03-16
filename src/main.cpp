#include <Arduino.h>
#include <lvgl.h>
#include <TFT_eSPI.h>
#include <XPT2046_Touchscreen.h>
#include <FlexCAN.h>
#include <kinetis_flexcan.h>
FlexCAN CANReceiver(100000);
CAN_message_t msg;

/*Change to your screen resolution*/
static const uint16_t screenWidth = 240;
static const uint16_t screenHeight = 320;

#define TFT_BL 13
uint8_t TftBackground = 150;

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[screenWidth * 10];

/* I added this varies */

uint16_t rawPointMinX = 200;
uint16_t rawPointMaxX = 3400;
uint16_t rawPointMinY = 800;
uint16_t rawPointMaxY = 4095;
uint16_t screenPointX;
uint16_t screenPointY;
lv_obj_t *labelPoint;
lv_indev_t *mouse_indev;
lv_obj_t *cursor_obj;
lv_indev_drv_t indev_drv;
lv_obj_t *ui_labelSpeed;
lv_obj_t *ui_labelCurrent;
lv_obj_t *ui_labelVolt;
lv_obj_t *ui_labelAirTemp;
lv_obj_t *ui_labelMotorTemp;
lv_obj_t *ui_barVoltage;
lv_obj_t *ui_barCurrent;
lv_obj_t *ui_panelRtd;
lv_obj_t *ui_panelCi;
lv_obj_t *ui_panelCal;
lv_obj_t *ui_panelBms;
lv_obj_t *ui_panelImd;
lv_obj_t *ui_panelRgb;
lv_obj_t *ui_Label1;
lv_obj_t *ui_Label2;
lv_obj_t *ui_Label3;
lv_obj_t *ui_Label4;
lv_obj_t *ui_Label5;
lv_obj_t *ui_Label6;

TFT_eSPI tft = TFT_eSPI(screenWidth, screenHeight); /* TFT instance */

#define CS_PIN 8
#define TIRQ_PIN 2

XPT2046_Touchscreen ts(CS_PIN, TIRQ_PIN); // Param 2 - Touch IRQ Pin - interrupt enabled polling

#if LV_USE_LOG != 0
/* Serial debugging */
void my_print(const char *buf)
{
  Serial.printf(buf);
  Serial.flush();
}
#endif

/* Display flushing */
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
  uint32_t w = (area->x2 - area->x1 + 1);
  uint32_t h = (area->y2 - area->y1 + 1);

  tft.startWrite();
  tft.setAddrWindow(area->x1, area->y1, w, h);
  tft.pushColors((uint16_t *)&color_p->full, w * h, true);
  tft.endWrite();

  lv_disp_flush_ready(disp);
}

void touch_xpt2046_init(void)
{
  ts.begin();
  ts.setRotation(0);
}
void my_touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data)
{
  if (ts.touched())
  {
    data->state = LV_INDEV_STATE_PR;
    TS_Point p = ts.getPoint();
    screenPointX = screenWidth - screenWidth * (p.x - rawPointMinX) / (rawPointMaxX - rawPointMinX);
    screenPointY = screenHeight - screenHeight * (p.y - rawPointMinY) / (rawPointMaxY - rawPointMinY);

    data->point.x = screenPointX;
    data->point.y = screenPointY;
  }
  else
  {
    data->state = LV_INDEV_STATE_REL;
  }
}

void setup()
{
  CANReceiver.begin();
  delay(1000);
  Serial.println("CAN Receiver Initialized");

  /* tft backgroud lighting setting */
  pinMode(TFT_BL, OUTPUT);
  analogWrite(TFT_BL, TftBackground);

  Serial.begin(115200); /* prepare for possible serial debug */

  String LVGL_Arduino = "LVGL ver: ";
  LVGL_Arduino += String('V') + lv_version_major() + "." + lv_version_minor() + "." + lv_version_patch();

  Serial.println(LVGL_Arduino);
  Serial.println("I am LVGL_Arduino");

  lv_init();

#if LV_USE_LOG != 0
  lv_log_register_print_cb(my_print); /* register print function for debugging */
#endif

  tft.begin();        /* TFT init */
  tft.setRotation(0); /* Landscape orientation, flipped */

  touch_xpt2046_init();

  lv_disp_draw_buf_init(&draw_buf, buf, NULL, screenWidth * 10);

  // Initialize the display
  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv);
  // Change the following line to your display resolution
  disp_drv.hor_res = screenWidth;
  disp_drv.ver_res = screenHeight;
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.draw_buf = &draw_buf;
  lv_disp_drv_register(&disp_drv);

  
  ui_labelAirTemp = lv_label_create(lv_scr_act());
  lv_obj_set_width(ui_labelAirTemp, LV_SIZE_CONTENT);   /// 1
  lv_obj_set_height(ui_labelAirTemp, LV_SIZE_CONTENT);    /// 1
  lv_obj_set_x(ui_labelAirTemp, -30);
  lv_obj_set_y(ui_labelAirTemp, -122);
  lv_obj_set_align(ui_labelAirTemp, LV_ALIGN_CENTER);
  lv_label_set_text(ui_labelAirTemp, "Airtemp: 0°C");

  ui_labelMotorTemp = lv_label_create(lv_scr_act());
  lv_obj_set_width(ui_labelMotorTemp, LV_SIZE_CONTENT);   /// 1
  lv_obj_set_height(ui_labelMotorTemp, LV_SIZE_CONTENT);    /// 1
  lv_obj_set_x(ui_labelMotorTemp, -30);
  lv_obj_set_y(ui_labelMotorTemp, -100);
  lv_obj_set_align(ui_labelMotorTemp, LV_ALIGN_CENTER);
  lv_label_set_text(ui_labelMotorTemp, "Motortemp 0°C");

  ui_barVoltage = lv_bar_create(lv_scr_act());
  lv_bar_set_range(ui_barVoltage, 240, 403);
  lv_bar_set_value(ui_barVoltage, 240, LV_ANIM_OFF);
  lv_obj_set_width(ui_barVoltage, 200);
  lv_obj_set_height(ui_barVoltage, 30);
  lv_obj_set_x(ui_barVoltage, 0);
  lv_obj_set_y(ui_barVoltage, 75);
  lv_obj_set_align(ui_barVoltage, LV_ALIGN_CENTER);

  ui_barCurrent = lv_bar_create(lv_scr_act());
  lv_bar_set_range(ui_barCurrent, 0, 100);
  lv_bar_set_value(ui_barCurrent, 0, LV_ANIM_OFF);
  lv_obj_set_width(ui_barCurrent, 200);
  lv_obj_set_height(ui_barCurrent, 30);
  lv_obj_set_x(ui_barCurrent, 0);
  lv_obj_set_y(ui_barCurrent, 30);
  lv_obj_set_align(ui_barCurrent, LV_ALIGN_CENTER);

  ui_labelSpeed = lv_label_create(lv_scr_act());
  lv_obj_set_width(ui_labelSpeed, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_height(ui_labelSpeed, LV_SIZE_CONTENT); /// 1
  lv_obj_set_x(ui_labelSpeed, 5);
  lv_obj_set_y(ui_labelSpeed, -40);
  lv_obj_set_align(ui_labelSpeed, LV_ALIGN_CENTER);
  lv_label_set_text(ui_labelSpeed, "100 km/h");

  ui_labelCurrent = lv_label_create(lv_scr_act());
  lv_obj_set_width(ui_labelCurrent, LV_SIZE_CONTENT);   /// 1
  lv_obj_set_height(ui_labelCurrent, LV_SIZE_CONTENT);    /// 1
  lv_obj_set_x(ui_labelCurrent, 3);
  lv_obj_set_y(ui_labelCurrent, 30);
  lv_obj_set_align(ui_labelCurrent, LV_ALIGN_CENTER);
  lv_label_set_text(ui_labelCurrent, "0A");

  ui_labelVolt = lv_label_create(lv_scr_act());
  lv_obj_set_width(ui_labelVolt, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_height(ui_labelVolt, LV_SIZE_CONTENT); /// 1
  lv_obj_set_x(ui_labelVolt, 0);
  lv_obj_set_y(ui_labelVolt, 75);
  lv_obj_set_align(ui_labelVolt, LV_ALIGN_CENTER);
  lv_label_set_text(ui_labelVolt, "240V");

  // Initialize the input device driver
  //  static lv_indev_drv_t indev_drv;
  lv_indev_drv_init(&indev_drv);
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  indev_drv.read_cb = my_touchpad_read;
  lv_indev_drv_register(&indev_drv);

  ui_panelRtd = lv_obj_create(lv_scr_act());
  lv_obj_set_width(ui_panelRtd, 30);
  lv_obj_set_height(ui_panelRtd, 30);
  lv_obj_set_x(ui_panelRtd, -90);
  lv_obj_set_y(ui_panelRtd, 130);
  lv_obj_set_align(ui_panelRtd, LV_ALIGN_CENTER);
  lv_obj_clear_flag(ui_panelRtd, LV_OBJ_FLAG_SCROLLABLE); /// Flags

  ui_panelCi = lv_obj_create(lv_scr_act());
  lv_obj_set_width(ui_panelCi, 30);
  lv_obj_set_height(ui_panelCi, 30);
  lv_obj_set_x(ui_panelCi, -55);
  lv_obj_set_y(ui_panelCi, 130);
  lv_obj_set_align(ui_panelCi, LV_ALIGN_CENTER);
  lv_obj_clear_flag(ui_panelCi, LV_OBJ_FLAG_SCROLLABLE); /// Flags

  ui_panelCal = lv_obj_create(lv_scr_act());
  lv_obj_set_width(ui_panelCal, 30);
  lv_obj_set_height(ui_panelCal, 30);
  lv_obj_set_x(ui_panelCal, -20);
  lv_obj_set_y(ui_panelCal, 130);
  lv_obj_set_align(ui_panelCal, LV_ALIGN_CENTER);
  lv_obj_clear_flag(ui_panelCal, LV_OBJ_FLAG_SCROLLABLE); /// Flags

  ui_panelBms = lv_obj_create(lv_scr_act());
  lv_obj_set_width(ui_panelBms, 30);
  lv_obj_set_height(ui_panelBms, 30);
  lv_obj_set_x(ui_panelBms, 20);
  lv_obj_set_y(ui_panelBms, 130);
  lv_obj_set_align(ui_panelBms, LV_ALIGN_CENTER);
  lv_obj_clear_flag(ui_panelBms, LV_OBJ_FLAG_SCROLLABLE); /// Flags

  ui_panelImd = lv_obj_create(lv_scr_act());
  lv_obj_set_width(ui_panelImd, 30);
  lv_obj_set_height(ui_panelImd, 30);
  lv_obj_set_x(ui_panelImd, 55);
  lv_obj_set_y(ui_panelImd, 130);
  lv_obj_set_align(ui_panelImd, LV_ALIGN_CENTER);
  lv_obj_clear_flag(ui_panelImd, LV_OBJ_FLAG_SCROLLABLE); /// Flags

  ui_panelRgb = lv_obj_create(lv_scr_act());
  lv_obj_set_width(ui_panelRgb, 30);
  lv_obj_set_height(ui_panelRgb, 30);
  lv_obj_set_x(ui_panelRgb, 90);
  lv_obj_set_y(ui_panelRgb, 130);
  lv_obj_set_align(ui_panelRgb, LV_ALIGN_CENTER);
  lv_obj_clear_flag(ui_panelRgb, LV_OBJ_FLAG_SCROLLABLE); /// Flags

  ui_Label2 = lv_label_create(lv_scr_act());
  lv_obj_set_width(ui_Label2, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_height(ui_Label2, LV_SIZE_CONTENT); /// 1
  lv_obj_set_x(ui_Label2, -90);
  lv_obj_set_y(ui_Label2, 105);
  lv_obj_set_align(ui_Label2, LV_ALIGN_CENTER);
  lv_label_set_text(ui_Label2, "RTD");

  ui_Label1 = lv_label_create(lv_scr_act());
  lv_obj_set_width(ui_Label1, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_height(ui_Label1, LV_SIZE_CONTENT); /// 1
  lv_obj_set_x(ui_Label1, -55);
  lv_obj_set_y(ui_Label1, 105);
  lv_obj_set_align(ui_Label1, LV_ALIGN_CENTER);
  lv_label_set_text(ui_Label1, "CI");

  ui_Label3 = lv_label_create(lv_scr_act());
  lv_obj_set_width(ui_Label3, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_height(ui_Label3, LV_SIZE_CONTENT); /// 1
  lv_obj_set_x(ui_Label3, -20);
  lv_obj_set_y(ui_Label3, 105);
  lv_obj_set_align(ui_Label3, LV_ALIGN_CENTER);
  lv_label_set_text(ui_Label3, "CAL");

  ui_Label4 = lv_label_create(lv_scr_act());
  lv_obj_set_width(ui_Label4, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_height(ui_Label4, LV_SIZE_CONTENT); /// 1
  lv_obj_set_x(ui_Label4, 20);
  lv_obj_set_y(ui_Label4, 105);
  lv_obj_set_align(ui_Label4, LV_ALIGN_CENTER);
  lv_label_set_text(ui_Label4, "BMS");

  ui_Label5 = lv_label_create(lv_scr_act());
  lv_obj_set_width(ui_Label5, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_height(ui_Label5, LV_SIZE_CONTENT); /// 1
  lv_obj_set_x(ui_Label5, 55);
  lv_obj_set_y(ui_Label5, 105);
  lv_obj_set_align(ui_Label5, LV_ALIGN_CENTER);
  lv_label_set_text(ui_Label5, "IMD");

  ui_Label6 = lv_label_create(lv_scr_act());
  lv_obj_set_width(ui_Label6, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_height(ui_Label6, LV_SIZE_CONTENT); /// 1
  lv_obj_set_x(ui_Label6, 90);
  lv_obj_set_y(ui_Label6, 105);
  lv_obj_set_align(ui_Label6, LV_ALIGN_CENTER);
  lv_label_set_text(ui_Label6, "RGB");

  // add a cursor
  mouse_indev = lv_indev_drv_register(&indev_drv);
  // LV_IMG_DECLARE(mouse_cursor_icon);                  //Declare the image source.
  cursor_obj = lv_img_create(lv_scr_act());     // Create an image object for the cursor
  lv_img_set_src(cursor_obj, LV_SYMBOL_GPS);    // Set the image source
  lv_indev_set_cursor(mouse_indev, cursor_obj); // Connect the image  object to the driver

  Serial.println("Setup done");
}

void loop()
{
  while (CANReceiver.read(msg))
  {
    if (msg.buf[0] == 16)
    {
      if (msg.buf[1] == 0)
      {
        Serial.print("Status ");
        Serial.println(msg.buf[2]);

        Serial.print("State ");
        Serial.println(msg.buf[3]);

        uint16_t speed16 = ((uint16_t)msg.buf[4] << 8) | (uint16_t)msg.buf[5];
        float speed = (float)speed16 / 100.0;
        lv_label_set_text_fmt(ui_labelSpeed, "%.2f km/h", speed);

        uint16_t current16 = ((uint16_t)msg.buf[6] << 8) | (uint16_t)msg.buf[7];
        float current = (float)current16 / 100.0;
        lv_label_set_text_fmt(ui_labelCurrent, "%.2f A", current);
        lv_bar_set_value(ui_barCurrent, (current16 / 100), LV_ANIM_OFF);
      }
      else if (msg.buf[1] == 1)
      {
        Serial.print("MotorTemp ");
        Serial.println(msg.buf[2]);
        lv_label_set_text_fmt(ui_labelMotorTemp, "MotorTemp: %d°C", msg.buf[2]);


        Serial.print("AirTemp ");
        Serial.println(msg.buf[3]);
        lv_label_set_text_fmt(ui_labelAirTemp, "Airtemp: %d°C", msg.buf[3]);


        uint16_t dcVoltage16 = ((uint16_t)msg.buf[4] << 8) | (uint16_t)msg.buf[5];
        float dcVoltage = (float)dcVoltage16 / 100.0;
        lv_label_set_text_fmt(ui_labelVolt, "%.2f V", dcVoltage);
        lv_bar_set_value(ui_barVoltage, (dcVoltage16 / 100), LV_ANIM_OFF);
      }
    }else if(msg.buf[0]==208){
      if(msg.buf[1]==0){
        lv_obj_set_style_bg_color(ui_panelBms, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
      }else{
        lv_obj_set_style_bg_color(ui_panelBms, lv_color_hex(0xFF0000), LV_PART_MAIN | LV_STATE_DEFAULT);
      }
      Serial.print("BMS: 208 ");
      Serial.println(msg.buf[1]);
    }else if(msg.buf[0]==209){
      if(msg.buf[1]==0){
        lv_obj_set_style_bg_color(ui_panelImd, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
      }else{
        lv_obj_set_style_bg_color(ui_panelImd, lv_color_hex(0xFF0000), LV_PART_MAIN | LV_STATE_DEFAULT);
      }
      Serial.print("IMD: 209 ");
      Serial.println(msg.buf[1]);
    }else if(msg.buf[0]==116){
      if(((msg.buf[1] >> 7) & 0x1)==0){
        lv_obj_set_style_bg_color(ui_panelRtd, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
      }else{
        lv_obj_set_style_bg_color(ui_panelRtd, lv_color_hex(0x00FF00), LV_PART_MAIN | LV_STATE_DEFAULT);
      }
    }else if(msg.buf[0]==115){
      if(((msg.buf[1] >> 7) & 0x1)==0){
        lv_obj_set_style_bg_color(ui_panelCal, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
      }else{
        lv_obj_set_style_bg_color(ui_panelCal, lv_color_hex(0x00FF00), LV_PART_MAIN | LV_STATE_DEFAULT);
      }
    }else if(msg.buf[0]==120){
      if(((msg.buf[1] >> 7) & 0x1)==0){
        lv_obj_set_style_bg_color(ui_panelRgb, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
      }else{
        lv_obj_set_style_bg_color(ui_panelRgb, lv_color_hex(0x00FF00), LV_PART_MAIN | LV_STATE_DEFAULT);
      }
    }
  }
  lv_timer_handler(); /* let the GUI do its work */
  delay(10);
}