#include <FastLED.h>
#include <TimerOne.h>
#include <SoftwareSerial.h>

#define TXSIZE 5
#define RXSIZE 12

// color definition
CHSV PURE_RED(0, 255, 255);
CHSV PURE_BLUE(160, 255, 255);
CHSV PURE_WHITE(0, 0, 255);
CHSV PURE_BLACK(0, 0, 0);
CHSV WHITE_ONE(0, 0, 152);

// variable definition
int TIME_DELAY = 20;
int FUNC_CHOICE = 0;
int SLAVE_NUMBER = 2;
int COLOR_SHIFT = 0;
int LOWER_LIMIT = 10;
int UPPER_LIMIT = 150;
CHSV CHOOSEN_COLOR_ONE = PURE_RED;
CHSV CHOOSEN_COLOR_TWO = PURE_BLUE;

// init softwareSerial interfaces, RX=0;2, TX=1;3
SoftwareSerial rs485(0, 1);
SoftwareSerial bluetooth_con(2, 3);

int RANDOM_LIST[32] = {4, 1, 6, 12, 31, 29, 13, 25, 24, 3, 2, 30, 14, 23, 7, 28, 19, 18, 21, 27, 16, 17, 22, 9, 10, 26, 15, 0, 20, 8, 5, 11};

void send_data(int adress, int hue, int sat, int value)
/*
     @brief -> sends the color information as an byte array to the given adress
     @param adress -> int adress of the slave deveice
     @param hue -> int angle of the color, 0-255
     @param sat -> int the saturation of the color, 0-255
     @param value -> int value of the color, 0-255
*/
{
  byte message[TXSIZE] = {byte("<"), byte(adress), byte(hue), byte(sat), byte(value)};
  rs485.write(message, TXSIZE);
}

void blackout(int slave_number)
/*
   @brief -> sets all tubes to the color black
   @param slave_number -> int number how many slave deveices are connected
*/
{
  for (int i = 0; i < slave_number; i++)
  {
    send_data(i, PURE_BLACK[0], PURE_BLACK[1], PURE_BLACK[2]);
  }
}

void flash(int time_delay, int slave_number, CHSV color, int *rand_list)
/*
   @brief -> flashes one tube at a time with a certain delay in an generated "random" order
   @param
*/
{
  blackout(slave_number);
  delay(500);
  send_data((rand_list[0] % slave_number), color[0], color[1], color[2]);
  delay(500);
}

void rainbow(int slave_number, int color_shift, int time_delay)
/*
    @brief -> sets all tubes to a rainbow animation
    @param slave_number -> int number how many slave deveices are connected
    @param color_shift -> int shift of the color angle between the deveices, 0-x
    @param time_delay -> time in milliseconds, gets mulitplied with ten for delay, 0-255
*/
{
  time_delay *= 10;
  for (int i = 0; i <= 255; i++)
  {
    CHSV hsv(i, 255, 255);
    for (int j = 0; j < slave_number; j++) {
      send_data(j, (hsv[0] + (j * color_shift)) % 255, hsv[1], hsv[2]);
    }
    delay(time_delay); // vary animation speed
  }
}

void color_fade(int slave_number, int color_shift, int lower_limit, int upper_limit, int time_delay)
/*
     @brief -> fades from the lower limit of hue to the upper limit and backwards
     @param slave_number -> int number how many slave deveices are connected
     @param color_shift -> int shift of the color angle between the deveices, 0-x
     @param lower_limit -> int angle of the color to start with, 0-255
     @param upper_limit -> int angle of the color to stop and reverse, 0-255
     @note -> lower limit has to be a smaller number than upper limit
     @param time_delay -> time in milliseconds, gets mulitplied with ten for delay, 0-255
*/
{
  time_delay *= 10;
  for (int i = lower_limit; i <= upper_limit; i++)
  {
    CHSV hsv(i, 255, 255);
    for (int j = 0; j < slave_number; j++) {
      send_data(j, (hsv[0] + (j * color_shift)) % 255, hsv[1], hsv[2]);
    }
    delay(time_delay);
  }
  for (int i = upper_limit; i >= lower_limit; i--)
  {
    CHSV hsv(i, 255, 255);
    for (int j = 0; j < slave_number; j++) {
      send_data(j, (hsv[0] + (j * color_shift)) % 255, hsv[1], hsv[2]);
    }
    delay(time_delay);
  }
}

void police_light(int slave_number)
/*
     @brief -> mimics a police light
     @param slave_number -> int number how many slave deveices are connected
*/
{
  int delay_fast = 50;
  int delay_slow = 175;
  for (int j = 0; j < 2; j++)
  {
    for (int i = 0; i < slave_number; i++)
    {
      if (i < (slave_number / 2)) send_data(i, PURE_RED[0], PURE_RED[1], PURE_RED[2]);
    }
    delay(delay_fast);
    blackout(slave_number);
    delay(delay_fast);
  }
  delay(delay_slow);
  for (int j = 0; j < 2; j++)
  {
    for (int i = 0; i < slave_number; i++)
    {
      if (i >= (slave_number / 2)) send_data(i, PURE_BLUE[0], PURE_BLUE[1], PURE_BLUE[2]);
    }
    delay(delay_fast);
    blackout(slave_number);
    delay(delay_fast);
  }
  delay(delay_slow);
  for (int j = 0; j < 2; j++)
  {
    for (int i = 0; i < slave_number; i++)
    {
      send_data(i, WHITE_ONE[0], WHITE_ONE[1], WHITE_ONE[2]);
    }
    delay(delay_fast);
    blackout(slave_number);
    delay(delay_fast);
  }
  delay(delay_slow);
}

void all_one_color(int slave_number, CHSV color, int color_shift)
/*
   @brief -> sets all tubes to one color
   @param slave_number -> int number how many slave deveices are connected
   @param color -> CHSV color to be displayed
   @param color_shift -> int shift of the color angle between the deveices, 0-x
*/
{
  for (int i = 0; i < slave_number; i++)
  {
    send_data(i, (color[0] + i * color_shift) % 255, color[1], color[2]);
  }
  delay(500);
}

void half_one_color(int slave_number, CHSV color_one, CHSV color_two)
/*
   @brief -> sets half of all slave deveices to the first color and the other half to the other color
   @param slave_number -> int number how many slave deveices are connected
   @param color_one -> CHSV color for the first half
   @param color_two -> CHSV color for the seccond half
*/
{
  for (int i = 0; i < slave_number; i++)
  {
    if (i < slave_number / 2) send_data(i, color_one[0], color_one[1], color_one[2]);
    else send_data(i, color_two[0], color_two[1], color_two[2]);
  }
  delay(500);
}

void breathe(int slave_number, int color_shift, int lower_limit, int upper_limit, CHSV color, int time_delay)
/*
   @brief -> fades the brightness from the lower limit to the upper limit and back
   @param slave_number -> int number how many slave deveices are connected
   @param color_shift -> int shift of the color angle between the deveices, 0-x
   @param lower_limit -> int angle of the color to start with, 0-255
   @param upper_limit -> int angle of the color to stop and reverse, 0-255
   @note -> lower limit has to be a smaller number than upper limit
   @param color -> CHSV color for the tubes
   @param time_delay -> time in milliseconds, gets mulitplied with ten for delay, 0-255
*/
{
  color[2] = lower_limit;
  for (int i = lower_limit; i <= upper_limit; i++)
  {
    for (int j = 0; j < slave_number; j++) {
      send_data(j, (color[0] + (j * color_shift)) % 255, color[1], i);
    }
    delay(time_delay);
  }
  for (int i = upper_limit; i >= lower_limit; i--)
  {
    for (int j = 0; j < slave_number; j++) {
      send_data(j, (color[0] + (j * color_shift)) % 255, color[1], i);
    }
    delay(time_delay);
  }
}

void running_light(int time_delay, int slave_number, CHSV color_one, CHSV color_two)
/*
   @brief -> running light, one tube at a time with "background" color
   @param time delay -> time in milliseconds
   @param slave_number -> int number how many slave deveices are connected
   @param color_one -> CHSV color of the "background"
   @param color_two -> CHSV color of the running light
*/
{
  for (int i = 0; i < slave_number; i++)
  {
    for (int j = 0; i < slave_number; j++)
    {
      if (j == i) send_data(j, color_two[0], color_two[1], color_two[2]);
      else send_data(j, color_one[0], color_one[1], color_one[2]);
    }
    delay(time_delay);
  }
}

void serial_data()
/*
   @brief -> interrupts the main programm and reads the bluetooth data in
*/
{
  if (bluetooth_con.available() > 0)
  {
    byte character = bluetooth_con.read();
    if (character == byte("<")) {
      byte message[9];
      bluetooth_con.readBytes(message, 9);
    }
  }
}

void setup()
{
  delay(1000);
  // begin of the Serial communication
  bluetooth_con.begin(9600);
  rs485.begin(9600);
  delay(100);
  // init the timer interrupt
  Timer1.initialize(1000);
  Timer1.attachInterrupt(serial_data);
}

void loop()
{
  switch (FUNC_CHOICE)
  {
    case 0:
      rainbow(SLAVE_NUMBER, COLOR_SHIFT, TIME_DELAY);
      break;
    case 1:
      color_fade(SLAVE_NUMBER, COLOR_SHIFT, LOWER_LIMIT, UPPER_LIMIT, TIME_DELAY);
      break;
    case 2:
      all_one_color(SLAVE_NUMBER, CHOOSEN_COLOR_ONE, COLOR_SHIFT);
      break;
    case 3:
      police_light(SLAVE_NUMBER);
      break;
    case 4:
      half_one_color(SLAVE_NUMBER, CHOOSEN_COLOR_ONE, CHOOSEN_COLOR_TWO);
      break;
    case 5:
      breathe(SLAVE_NUMBER, COLOR_SHIFT, LOWER_LIMIT, UPPER_LIMIT, CHOOSEN_COLOR_ONE, TIME_DELAY);
      break;
    case 6:
      flash(TIME_DELAY, SLAVE_NUMBER, CHOOSEN_COLOR_ONE, RANDOM_LIST);
      break;
    case 7:
      running_light(TIME_DELAY, SLAVE_NUMBER, CHOOSEN_COLOR_ONE, CHOOSEN_COLOR_TWO);
      break;
  }
}
