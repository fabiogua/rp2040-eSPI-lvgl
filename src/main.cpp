#include <Arduino.h>
#include <lvgl.h>
#include <TFT_eSPI.h>
#include <XPT2046_Touchscreen.h>
#include <FlexCAN.h>
#include <kinetis_flexcan.h>
#include <ui.h>

FlexCAN CANReceiver(100000);
CAN_message_t message;

/*Change to your screen resolution*/
static const uint16_t screenWidth = 240;
static const uint16_t screenHeight = 320;

#define UPDATE_RATE 100

#define TFT_BL 13
uint8_t TftBackground = 10;

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

TFT_eSPI tft = TFT_eSPI(screenWidth, screenHeight); /* TFT instance */

#define CS_PIN 8
#define TIRQ_PIN 2

XPT2046_Touchscreen ts(CS_PIN, TIRQ_PIN); // Param 2 - Touch IRQ Pin - interrupt enabled polling

// Define the message structure
struct CanMessage
{
  uint8_t status;
  uint8_t shutdown;
  float speed;
  float current;
  float motorTemp;
  float airTemp;
  float dcVoltage;
  uint32_t power;
  uint8_t powermode;
  float brakePedalValue;
  float gasPedalValue;
};

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

  ui_init();

  // Initialize the input device driver
  //  static lv_indev_drv_t indev_drv;
  lv_indev_drv_init(&indev_drv);
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  indev_drv.read_cb = my_touchpad_read;
  lv_indev_drv_register(&indev_drv);
  /*
  // add a cursor
  mouse_indev = lv_indev_drv_register(&indev_drv);
  lv_IMG_DECLARE(mouse_cursor_icon);                  //Declare the image source.
  cursor_obj = lv_img_create(lv_scr_act());     // Create an image object for the cursor
  lv_img_set_src(cursor_obj, LV_SYMBOL_GPS);    // Set the image source
  lv_indev_set_cursor(mouse_indev, cursor_obj); // Connect the image  object to the driver
*/
  Serial.println("Setup done");
}

void loop()
{
  while (CANReceiver.available())
  {
    // Read the message
    CAN_message_t message;
    CANReceiver.read(message);
    CanMessage canMsg;

    // Serial.println(message.buf[0]);
    if (message.buf[0] == 192)
    {
      // Decode the message
      if (message.buf[1] == 0)
      {
        canMsg.status = message.buf[2];
        canMsg.shutdown = message.buf[3];
        canMsg.speed = ((uint16_t)message.buf[4] << 8 | message.buf[5]) / 100.0;
        canMsg.current = ((uint16_t)message.buf[6] << 8 | message.buf[7]) / 100.0;

        Serial.print(canMsg.status);
        Serial.print("\t");

        switch (canMsg.shutdown)
        {
        case 1:
          lv_label_set_text(ui_lShutdown, "BSPD");
          break;
        case 2:
          lv_label_set_text(ui_lShutdown, "Mainhoop or HVD");
          break;
        case 3:
          lv_label_set_text(ui_lShutdown, "Dashboard or Inertia or BOTS");
          break;
        case 4:
          lv_label_set_text(ui_lShutdown, "BMS");
          break;
        case 5:
          lv_label_set_text(ui_lShutdown, "IMD");
          break;

        default:
          lv_label_set_text(ui_lShutdown, "HV Closed");
          break;
        }

        Serial.print(canMsg.shutdown);
        Serial.print("\t");

        lv_label_set_text_fmt(ui_lSpeed, "%.2fkm/h", canMsg.speed);
        Serial.print(canMsg.speed);
        Serial.print("\t");

        lv_label_set_text_fmt(ui_lCurrent, "%.2fA", canMsg.current);
        lv_bar_set_value(ui_bCurrent, canMsg.current, LV_ANIM_OFF);
        Serial.print(canMsg.current);
        Serial.print("\n");
      }
      else if (message.buf[1] == 1)
      {

        canMsg.motorTemp = ((uint16_t)message.buf[2] << 8 | message.buf[3]) / 100.0;
        canMsg.airTemp = ((uint16_t)message.buf[4] << 8 | message.buf[5]) / 100.0;
        canMsg.dcVoltage = ((uint16_t)message.buf[6] << 8 | message.buf[7]) / 100.0;

        lv_label_set_text_fmt(ui_lMotorTemperature, "%.2f°C", canMsg.motorTemp);
        lv_bar_set_value(ui_bMotorTemperature, canMsg.motorTemp, LV_ANIM_OFF);
        Serial.print(canMsg.motorTemp);
        Serial.print("\t");

        lv_label_set_text_fmt(ui_lAirTemperature, "%.2f°C", canMsg.airTemp);
        lv_bar_set_value(ui_bAirTemperature, canMsg.motorTemp, LV_ANIM_OFF);
        Serial.print(canMsg.airTemp);
        Serial.print("\t");

        lv_label_set_text_fmt(ui_lBatteryVoltage, "%.2f V", canMsg.dcVoltage);
        lv_bar_set_value(ui_bBatteryVoltage, canMsg.dcVoltage, LV_ANIM_OFF);
        Serial.print(canMsg.dcVoltage);
        Serial.print("\n");
      }
      else if (message.buf[1] == 2)
      {
        canMsg.power = ((uint32_t)message.buf[2] << 24) | (message.buf[3] << 16) | (message.buf[4] << 8) | message.buf[5];
        canMsg.powermode = message.buf[6];

        Serial.print(canMsg.power);
        Serial.print("\n");

        switch (canMsg.powermode)
        {
        case 1:
          lv_label_set_text(ui_lPowermode, "Fast");
          break;
        case 2:
          lv_label_set_text(ui_lPowermode, "Faast");
          break;
        default:
          lv_label_set_text(ui_lPowermode, "Normal");
          break;
        }

        Serial.print(canMsg.powermode);
        Serial.print("\n");
      }
    }
    else if (message.buf[0] == 32)
    {
      uint16_t newValue16 = message.buf[1] | (message.buf[2] << 8);
      canMsg.brakePedalValue = (float)newValue16 / 65535.0;

      lv_bar_set_value(ui_bBrakePedal, canMsg.brakePedalValue * 1000, LV_ANIM_OFF);
      Serial.print(canMsg.brakePedalValue);
      Serial.print("\n");
    }
    else if (message.buf[0] == 33)
    {

      // change line below when type of pedal_value_t changes
      uint16_t newValue16 = message.buf[1] | (message.buf[2] << 8);
      canMsg.gasPedalValue = (float)newValue16 / 65535.0;

      lv_bar_set_value(ui_bGasPedal, canMsg.gasPedalValue * 1000, LV_ANIM_OFF);
      Serial.print(canMsg.gasPedalValue);
      Serial.print("\n");
    }
  }
  lv_timer_handler(); /* let the GUI do its work */
  delay(0.01);
}