
// **************************************************************
// RGB LED TUBES V2
// **************************************************************

#include <FastLED.h>
#include <OneButton.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeMonoBold9pt7b.h>
#include <Fonts/FreeMonoBold12pt7b.h>

// define values for oled display
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_RESET     -1
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// define encoder pins and encoder button pin
#define encoder_pin_a 2
#define encoder_pin_b 3
#define button_pin 4

// define rgb output pins
#define red_pin 5
#define green_pin 6
#define blue_pin 9

// define variables
CHSV hsv_val(0, 255, 128);
CHSV rainbow_var(0, 255, 255);
CRGB white_color(255, 200, 190);
CRGB warm_white(255, 138, 18);
CRGB black_color(0, 0, 0);
CHSV fire_orange(25, 255, 175);

// define pre choosen colors
CRGB cyan(0, 255, 190);
CRGB pink(255, 0, 65);
CRGB green(0, 255, 0);
CRGB pink_two(255, 0, 255);
CRGB orange(255, 175, 0);
CRGB blue(0, 80, 255);
CRGB purple(120, 0, 255);
CRGB lime(136, 255, 0);

// names for the pre defined colors
char* predefined_names[] =
{
  "WHITE",
  "WHITE-2",
  "CYAN",
  "PINK",
  "GREEN",
  "PINK-2",
  "ORANGE",
  "BLUE",
  "PURPLE",
  "LIME",
};

CRGB predefined_colors[] =
{
  white_color,
  warm_white,
  cyan,
  pink,
  green,
  pink_two,
  orange,
  blue,
  purple,
  lime,
};

// variables for later use
unsigned long last_millis = 0;
unsigned long last_updated = 0;
unsigned long last_rotary_millis_a = 100;
unsigned long last_rotary_millis_b = 100;
int color_pos = 0;
int bright_fac = 80;
int t_interval = 200;
int t_int_fire = 150;
int inc_step = 1;
int hue_inc = 1;
int sat_percent = 100;
int val_percent = 100;
int speed_percent = 75;
int t_up_display = 100;
bool light_on = false;
bool disp_updated = true;

// init rotary encoder vars
volatile unsigned int encoder_pos = 0;  // a counter for the dial
unsigned int last_reported_pos = 1;   // change management
static boolean rotating = false;    // debounce management

// interrupt service routine vars
boolean a_set = false;
boolean b_set = false;

// init button to have multiple button modes with OneButton.h
OneButton btn = OneButton(
                  button_pin,  // Input pin for the button
                  true,        // Button is active LOW
                  true         // Enable internal pull-up resistor
                );

// enums for mode switching
enum main_stage {
  HSV,
  EFFECT,
  PREC
};

enum hsv_stage {
  HUE,
  SAT,
  VAL
};

enum effect_stage {
  RAINBOW,
  STROBE,
  FIRE
};

// defined variables for switching modes
main_stage main_stage_sw = HSV;
hsv_stage hsv_stage_sw = HUE;
effect_stage effect_stage_sw = RAINBOW;

// **************************************************************
// functions for the EFFECT stage
// **************************************************************
void rainbow()
/*
   @brief cycles through the color palete of a rainbow
*/
{
  if (millis() - last_millis >= t_interval)
  {
    if (t_interval < 100)
    {
      hue_inc = map(t_interval, 10, 100, 5, 2);
    }
    else
    {
      hue_inc = 1;
    }
    rainbow_var[0] += hue_inc;
    hsv_color_out(rainbow_var);
    last_millis = millis();
  }
}

void fire()
/*
   @brief simulating a fireplace with pulsating light
*/
{
  if (millis() - last_millis >= t_int_fire)
  {
    CHSV temp;
    // randomizing the interval, hue and value
    t_int_fire = t_interval + random(0, 100);
    temp.hue = fire_orange.hue + random(-3, 3);
    temp.sat = fire_orange.sat;
    temp.val = fire_orange.val + random(0, 20);

    hsv_color_out(temp);
    last_millis = millis();
  }
}

void strobe()
/*
   @brief stroboscope with white color
*/
{
  if (millis() - last_millis >= t_interval)
  {
    if (light_on)
    {
      rgb_color_out(black_color);
      light_on = false;
    }
    else
    {
      rgb_color_out(white_color);
      light_on = true;
    }
    last_millis = millis();
  }
}

// **************************************************************
// functions for outputing color
// **************************************************************
void rgb_color_out(CRGB rgb_var)
/*
   @brief function to output the given rgb color
   @param rgb_var -> rgb color for output
*/
{
  analogWrite(red_pin, rgb_var[0]);
  analogWrite(green_pin, rgb_var[1]);
  analogWrite(blue_pin, rgb_var[2]);
}

void pre_color_out(int factor)
/*
   @brief function to output pre defined color with brightness factor
   @param factor -> brightness factor between 0-100
*/
{
  int len = (sizeof(predefined_colors) / sizeof(predefined_colors[0]));
  if (color_pos >= len) color_pos = 0;
  CRGB temp(predefined_colors[color_pos][0] * factor / 100, predefined_colors[color_pos][1] * factor / 100, predefined_colors[color_pos][2] * factor / 100);
  rgb_color_out(temp);
}

void hsv_color_out(CHSV hsv_var)
/*
   @brief function to output the given hsv color
   @param hsv_var -> hsv color for output
*/
{
  CRGB rgb_var;
  hsv2rgb_rainbow(hsv_var, rgb_var);
  rgb_color_out(rgb_var);
}

// **************************************************************
// functions to center text roughly
// **************************************************************
int get_center_twelve(String s)
/*
   @brief gets roughly the center position for a string with 12pt size
   @param s -> string which should be centered
*/
{
  int len = s.length();
  return 64 - (7 * len);
}

int get_center_nine(String s)
/*
   @brief gets roughly the center position for a string with 9pt size
   @param s -> string which should be centered
*/
{
  int len = s.length();
  return 64 - (5 * len);
}

// **************************************************************
// functions to output text to the oled display
// **************************************************************
void hsv_mode_display(hsv_stage stage)
/*
   @brief displays the information for the hsv color page
*/
{
  int off = 3;
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setFont(&FreeMonoBold12pt7b);
  display.setCursor(43, 20);
  display.print("HSV");
  display.setFont(&FreeMonoBold9pt7b);
  display.setCursor(off, 40);
  display.print("HUE SAT VAL");

  for (int i = 0; i < 3; i++)
  {
    if (i == stage)
    {
      display.fillRect(i * 42 + off, 47, 33, 16, WHITE);
      display.setTextColor(BLACK);
      display.setCursor(i * 42 + off, 60);
      if (i == 0)
      {
        display.print(hsv_val[i]);
      }
      else
      {
        display.print(map(hsv_val[i], 0, 255, 0, 100));
      }
    }
    else
    {
      display.setTextColor(WHITE);
      display.setCursor(i * 42 + off, 60);
      if (i == 0)
      {
        display.print(hsv_val[i]);
      }
      else
      {
        display.print(map(hsv_val[i], 0, 255, 0, 100));
      }
    }
  }
  display.display();
}

void prec_mode_display(int factor)
/*
   @brief displays the information for the pre defined color page
*/
{
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setFont(&FreeMonoBold12pt7b);
  display.setCursor(22, 20);
  display.print("COLORS");
  display.setFont(&FreeMonoBold9pt7b);
  display.setCursor(get_center_nine(predefined_names[color_pos]), 40);
  display.print(predefined_names[color_pos]);
  display.setCursor(30, 60);
  display.print("%:");
  display.fillRect(62, 47, 33, 16, WHITE);
  display.setTextColor(BLACK);
  display.setCursor(62, 60);
  display.print(factor);
  display.display();
}

void effect_mode_display()
/*
   @brief displays the information for the effect mode page
*/
{
  char* e_name = "";
  // getting the name of the effect and map the interval
  // to a speed value from 1 to 100
  switch (effect_stage_sw)
  {
    case RAINBOW:
      e_name = "RAINBOW";
      break;
    case STROBE:
      e_name = "STROBE";
      break;
    case FIRE:
      e_name = "FIRE";
      break;
  }
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setFont(&FreeMonoBold12pt7b);
  display.setCursor(get_center_twelve("EFFECTS"), 20);
  display.print("EFFECTS");
  display.setFont(&FreeMonoBold9pt7b);
  display.setCursor(get_center_nine(e_name), 40);
  display.print(e_name);
  display.setCursor(10, 60);
  display.print("Speed:");
  display.fillRect(80, 47, 33, 16, WHITE);
  display.setTextColor(BLACK);
  display.setCursor(80, 60);
  display.print(speed_percent);
  display.display();
}

// **************************************************************
// setting up the arduino
// **************************************************************
void setup()
{

  // init display and display a start up message
  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
  display.clearDisplay();
  display.setFont(&FreeMonoBold12pt7b);
  display.setTextColor(WHITE);
  display.setCursor(get_center_twelve("LED"), 25);
  display.println("LED");
  display.println("CONTROLER");
  display.display();
  delay(1000);
  // define the led output pin modes
  pinMode(red_pin, OUTPUT);
  pinMode(green_pin, OUTPUT);
  pinMode(blue_pin, OUTPUT);

  // setting the encoder pins to input, no internal pull-up resistor needed
  // because pull-up resistors are on board
  pinMode(encoder_pin_a, INPUT);
  pinMode(encoder_pin_b, INPUT);

  // attaching the interrupts
  attachInterrupt(0, do_encoder_a, CHANGE); // encoder pin on interrupt 0 (pin 2)
  attachInterrupt(1, do_encoder_b, CHANGE); // encoder pin on interrupt 1 (pin 3)

  // attaching the button functions
  btn.attachClick(handle_press);
  btn.attachLongPressStart(handle_long_press);

  // setting the color for the first mode
  hsv_color_out(hsv_val);
  hsv_mode_display(hsv_stage_sw);

  // pseudo random init
  randomSeed(0);

  // get the starting time
  last_millis = millis();
}

// **************************************************************
// main programm loop
// **************************************************************
void loop()
{
  if (millis() - last_updated > t_up_display)
  {
    disp_updated = true;
    last_updated = millis();
  }
  rotating = true;
  btn.tick();
  switch (main_stage_sw)
  {
    case HSV:
      if (disp_updated)
      {
        hsv_mode_display(hsv_stage_sw);
        disp_updated = false;
      }
      break;
    case PREC:
      if (disp_updated)
      {
        prec_mode_display(bright_fac);
        disp_updated = false;
      }
      break;
    case EFFECT:
      if (disp_updated)
      {
        effect_mode_display();
        disp_updated = false;
      }
      switch (effect_stage_sw)
      {
        case RAINBOW:
          rainbow();
          break;
        case STROBE:
          strobe();
          break;
        case FIRE:
          fire();
          break;
      }
      break;
  }
}

// **************************************************************
// functions and interrupts to handle user input
// **************************************************************
void handle_press()
/*
   @brief switches the modes in the main modes
*/
{
  switch (main_stage_sw)
  {
    case HSV:
      switch (hsv_stage_sw)
      {
        case HUE:
          hsv_stage_sw = SAT;
          break;
        case SAT:
          hsv_stage_sw = VAL;
          break;
        case VAL:
          hsv_stage_sw = HUE;
          break;

      }
      hsv_color_out(hsv_val);
      break;
    case PREC:
      color_pos ++;
      pre_color_out(bright_fac);
      break;
    case EFFECT:
      switch (effect_stage_sw)
      {
        case RAINBOW:
          effect_stage_sw = STROBE;
          t_interval = map(speed_percent, 1, 100, 1500, 40);
          break;
        case STROBE:
          effect_stage_sw = FIRE;
          t_interval = map(speed_percent, 1, 100, 600, 10);
          break;
        case FIRE:
          effect_stage_sw = RAINBOW;
          t_interval = map(speed_percent, 1, 100, 500, 10);
          break;
      }
      break;
  }
  disp_updated = true;
}

void handle_long_press()
/*
   @brief switches the main mode
*/
{
  switch (main_stage_sw) {
    case HSV:
      main_stage_sw = PREC;
      pre_color_out(bright_fac);
      break;
    case EFFECT:
      main_stage_sw = HSV;
      hsv_color_out(hsv_val);
      break;
    case PREC:
      main_stage_sw = EFFECT;
      break;
  }
  disp_updated = true;
}

void do_encoder_a()
/*
   @brief interrupt function of the rotary encoder, right turn
*/
{
  // stopping interrupts
  cli();

  // update the display in loop, set the flag in ISR
  disp_updated = true;

  // calculating the inc step based on the speed of the rotary encoders turning
  inc_step = 1 << (int((1000 / (millis() - last_rotary_millis_a)) / 40));

  if ( rotating ) delay (1);  // wait a little until the bouncing is done
  if ( digitalRead(encoder_pin_a) != a_set ) { // debounce once more
    a_set = !a_set;
    // adjust counter + if A leads B
    if ( a_set && !b_set )
      switch (main_stage_sw) {
        case HSV:
          switch (hsv_stage_sw) {
            case HUE:
              hsv_val.hue += inc_step;
              break;
            case SAT:
              sat_percent += inc_step;
              if (sat_percent > 100) sat_percent = 100;
              hsv_val.sat = map(sat_percent, 0, 100, 0, 255);
              break;
            case VAL:
              val_percent += inc_step;
              if (val_percent > 100) val_percent = 100;
              hsv_val.val = map(val_percent, 0, 100, 0, 255);
              break;
          }
          hsv_color_out(hsv_val);
          break;
        case EFFECT:
          speed_percent += inc_step;
          if (speed_percent > 100) speed_percent = 100;
          switch (effect_stage_sw)
          {
            case RAINBOW:
              t_interval = map(speed_percent, 1, 100, 500, 10);
              break;
            case STROBE:
              t_interval = map(speed_percent, 1, 100, 1500, 40);
              break;
            case FIRE:
              t_interval = map(speed_percent, 1, 100, 600, 10);
              break;
          }
          break;
        case PREC:
          bright_fac += inc_step;
          if (bright_fac > 100) bright_fac = 100;
          pre_color_out(bright_fac);
          break;
      }
    rotating = false;  // no more debouncing until loop() hits again
  }
  // saving the time for next interrupt
  last_rotary_millis_a = millis();

  // starting interrupts again
  sei();
}

void do_encoder_b()
/*
   @brief interrupt function of the rotary encoder, left turn
*/
{
  // stopping interrupts
  cli();

  // update the display in loop, set the flag in ISR
  disp_updated = true;

  // calculating the inc step based on the speed of the rotary encoders turning
  inc_step = 1 << (int((1000 / (millis() - last_rotary_millis_b)) / 40));

  if ( rotating ) delay (1);
  if ( digitalRead(encoder_pin_b) != b_set ) {
    b_set = !b_set;
    //  adjust counter - 1 if B leads A
    if ( b_set && !a_set )
      switch (main_stage_sw) {
        case HSV:
          switch (hsv_stage_sw) {
            case HUE:
              hsv_val.hue -= inc_step;
              break;
            case SAT:
              sat_percent -= inc_step;
              if (sat_percent < 0) sat_percent = 0;
              hsv_val.sat = map(sat_percent, 0, 100, 0, 255);
              break;
            case VAL:
              val_percent -= inc_step;
              if (val_percent < 0) val_percent = 0;
              hsv_val.val = map(val_percent, 0, 100, 0, 255);
              break;
          }
          hsv_color_out(hsv_val);
          break;
        case EFFECT:
          speed_percent -= inc_step;
          if (speed_percent < 1) speed_percent = 1;
          switch (effect_stage_sw)
          {
            case RAINBOW:
              t_interval = map(speed_percent, 1, 100, 500, 10);
              break;
            case STROBE:
              t_interval = map(speed_percent, 1, 100, 1500, 40);
              break;
            case FIRE:
              t_interval = map(speed_percent, 1, 100, 600, 10);
              break;
          }
          break;
        case PREC:
          bright_fac -= inc_step;
          if (bright_fac < 0) bright_fac = 0;
          pre_color_out(bright_fac);
          break;
      }
    rotating = false; // no more debouncing until loop() hits again
  }
  // saving the time for next interrupt
  last_rotary_millis_b = millis();

  // starting interrupts again
  sei();
}
