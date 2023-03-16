#include <Arduino.h>
#include <lvgl.h>
#include <TFT_eSPI.h>
#include <XPT2046_Touchscreen.h>
#include <FlexCAN.h>
#include <kinetis_flexcan.h>
// #include <ui/ui_helpers.h>

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
lv_obj_t *labelCurrent;
lv_obj_t *labelVoltage;
lv_obj_t *labelSpeed;
lv_indev_t *mouse_indev;
lv_obj_t *cursor_obj;
lv_indev_drv_t indev_drv;

lv_obj_t *roller1;

TFT_eSPI tft = TFT_eSPI(screenWidth, screenHeight); /* TFT instance */

#define CS_PIN 8
#define TIRQ_PIN 2

// XPT2046_Touchscreen ts(CS_PIN);
// #define TIRQ_PIN 22
// XPT2046_Touchscreen ts(CS_PIN); // Param 2 - NULL - No interrupts
// XPT2046_Touchscreen ts(CS_PIN, 255);  // Param 2 - 255 - No interrupts
XPT2046_Touchscreen ts(CS_PIN, TIRQ_PIN); // Param 2 - Touch IRQ Pin - interrupt enabled polling

#if LV_USE_LOG != 0
/* Serial debugging */
void my_print(const char *buf)
{
  Serial.printf(buf);
  Serial.flush();
}
#endif

void event_handler(lv_event_t *e)
{
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t *obj = lv_event_get_target(e);
  if (code == LV_EVENT_VALUE_CHANGED)
  {
    char buf[32];
    lv_roller_get_selected_str(obj, buf, sizeof(buf));
    LV_LOG_USER("Selected month: %s\n", buf);
  }
}
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

    screenPointX = screenWidth * (p.x - rawPointMinX) / (rawPointMaxX - rawPointMinX);
    screenPointY = screenHeight * (p.y - rawPointMinY) / (rawPointMaxY - rawPointMinY);

    screenPointX = screenWidth - screenWidth * (p.x - rawPointMinX) / (rawPointMaxX - rawPointMinX);
    screenPointY = screenHeight - screenHeight * (p.y - rawPointMinY) / (rawPointMaxY - rawPointMinY);

    screenPointX = screenPointX;
    screenPointY = screenPointY;
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

  /*Initialize the display*/
  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv);
  /*Change the following line to your display resolution*/
  disp_drv.hor_res = screenWidth;
  disp_drv.ver_res = screenHeight;
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.draw_buf = &draw_buf;
  lv_disp_drv_register(&disp_drv);

  /*Initialize the input device driver*/
  // static lv_indev_drv_t indev_drv;
  lv_indev_drv_init(&indev_drv);
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  indev_drv.read_cb = my_touchpad_read;
  lv_indev_drv_register(&indev_drv);

  /* add a cursor */
  mouse_indev = lv_indev_drv_register(&indev_drv);
  // LV_IMG_DECLARE(mouse_cursor_icon);                  /*Declare the image source.*/
  cursor_obj = lv_img_create(lv_scr_act());     /*Create an image object for the cursor */
  lv_img_set_src(cursor_obj, LV_SYMBOL_GPS);    /*Set the image source*/
  lv_indev_set_cursor(mouse_indev, cursor_obj); /*Connect the image  object to the driver*/

  /* Create simple label */
  lv_obj_t *label = lv_label_create(lv_scr_act());
  lv_label_set_text(label, LVGL_Arduino.c_str());
  lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);

  labelPoint = lv_label_create(lv_scr_act());
  lv_obj_align(labelPoint, LV_ALIGN_CENTER, 0, 20);

  labelCurrent = lv_label_create(lv_scr_act());
  lv_obj_align(labelCurrent, LV_ALIGN_CENTER, 0, 40);

  labelVoltage = lv_label_create(lv_scr_act());
  lv_obj_align(labelVoltage, LV_ALIGN_CENTER, 0, 60);

  labelSpeed = lv_label_create(lv_scr_act());
  lv_obj_align(labelSpeed, LV_ALIGN_CENTER, 0, 80);

  roller1 = lv_roller_create(lv_scr_act());
  lv_roller_set_options(roller1,
                        "Welcome\n"
                        "My\n"
                        "Program",
                        LV_ROLLER_MODE_INFINITE);
  lv_roller_set_visible_row_count(roller1, 4);
  lv_obj_center(roller1);
  lv_obj_add_event_cb(roller1, event_handler, LV_EVENT_ALL, NULL);
  lv_obj_align(roller1, LV_ALIGN_CENTER, 0, -80);

  Serial.println("Setup done");
}

void loop()
{
  while (CANReceiver.read(msg))
  {
    // toggle LEDs
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
        lv_label_set_text_fmt(labelSpeed, "Speed: %.2f km/h", speed);

        // this->setSpeed(speed);
        Serial.print("Speed ");
        Serial.print(speed);
        Serial.println("km/h");

        uint16_t current16 = ((uint16_t)msg.buf[6] << 8) | (uint16_t)msg.buf[7];
        float current = (float)current16 / 100.0;
        lv_label_set_text_fmt(labelCurrent, "Current: %.2f A", current);
        // this->setCurrent(current);
        Serial.print("Current ");
        Serial.print(current);
        Serial.println("A");
      }
      else if (msg.buf[1] == 1)
      {
        Serial.print("MotorTemp ");
        Serial.println(msg.buf[2]);

        Serial.print("AirTemp ");
        Serial.println(msg.buf[3]);

        uint16_t dcVoltage16 = ((uint16_t)msg.buf[4] << 8) | (uint16_t)msg.buf[5];
        float dcVoltage = (float)dcVoltage16 / 100.0;
        lv_label_set_text_fmt(labelVoltage, "Voltage: %.2f V", dcVoltage);
      }
    }
  }
  lv_label_set_text_fmt(labelPoint, "Point: %d, %d", screenPointX, screenPointY);
  lv_timer_handler(); /* let the GUI do its work */
  delay(1);
}