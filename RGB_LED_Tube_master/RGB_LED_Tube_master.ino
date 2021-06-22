#include <FastLED.h> 
#include <TimerOne.h>
#include <SoftwareSerial.h>

#define TXSIZE 5

// color definition
CHSV PURE_RED(0, 255, 255);
CHSV PURE_BLUE(160, 255, 255);
CHSV PURE_WHITE(0, 0, 255);
CHSV PURE_BLACK(0, 0, 0);
CHSV WHITE_ONE(0, 0, 152);

// variable definition
int time_int = 50;
int func_choice = 4;
int slave_number = 2;
int color_shift = 0;
int lower_limit = 150;
int upper_limit = 190;
CHSV choosen_color = PURE_RED;

// init softwareSerial interfaces, RX=0;2, TX=1;3
SoftwareSerial rs485(0, 1);
SoftwareSerial bluetooth_con(2, 3);

void send_data(int adress, int hue, int sat, int val)
/*
     @brief -> sends the color information as an byte array to the given adress
     @param adress -> int adress of the slave deveice
     @param hue -> int angle of the color, 0-255
     @param sat -> int the saturation of the color, 0-255
     @param val -> int value of the color, 0-255
*/
{
  byte message[TXSIZE] = {byte("<"), byte(adress), byte(hue), byte(sat), byte(val)};
  rs485.write(message, TXSIZE);
}

void rainbow(int slave_number, int color_shift)
/*
    @brief -> sets all tubes to a rainbow animation
    @param slave_number -> int number how many slave deveices are connected
    @param color_shift -> int shift of the color angle between the deveices, 0-x
*/
{
  for (int i = 0; i <= 255; i++)
  {
    CHSV hsv(i, 255, 255);
    for (int j = 0; j < slave_number; j++) {
      send_data(j, (hsv[0] + (j * color_shift)) % 255, hsv[1], hsv[2]);
    }
    delay(time_int); // vary animation speed
  }
}

void color_fade(int slave_number, int color_shift, int lower_limit, int upper_limit)
/*
     @brief -> fades from the lower limit of hue to the upper limit and backwards
     @param slave_number -> int number how many slave deveices are connected
     @param color_shift -> int shift of the color angle between the deveices, 0-x
     @param lower_limit -> int angle of the color to start with, 0-255
     @param upper_limit -> int angle of the color to stop and reverse, 0-255
     @note -> lower limit has to be a smaller number than upper limit
*/
{
  for (int i = lower_limit; i <= upper_limit; i++)
  {
    CHSV hsv(i, 255, 255);
    for (int j = 0; j < slave_number; j++) {
      send_data(j, (hsv[0] + (j * color_shift)) % 255, hsv[1], hsv[2]);
    }
    delay(time_int);
  }
  for (int i = upper_limit; i >= lower_limit; i--)
  {
    CHSV hsv(i, 255, 255);
    for (int j = 0; j < slave_number; j++) {
      send_data(j, (hsv[0] + (j * color_shift)) % 255, hsv[1], hsv[2]);
    }
    delay(time_int);
  }
}

void police_light(int slave_number)
/*
     @brief -> mimics a police light
     @param slave_number -> int number how many slave deveices are connected
*/
{
  int delay_fast = 75;
  int delay_slow = 200;
  for (int j = 0; j < 2; j++)
  {
    for (int i = 0; i < slave_number; i++)
    {
      if (i < (slave_number / 2)) send_data(i, PURE_RED[0], PURE_RED[1], PURE_RED[2]);
    }
    delay(delay_fast);
    for (int i = 0; i < slave_number; i++)
    {
      send_data(i, PURE_BLACK[0], PURE_BLACK[1], PURE_BLACK[2]);
    }
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
    for (int i = 0; i < slave_number; i++)
    {
      send_data(i, PURE_BLACK[0], PURE_BLACK[1], PURE_BLACK[2]);
    }
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
    for (int i = 0; i < slave_number; i++)
    {
      send_data(i, PURE_BLACK[0], PURE_BLACK[1], PURE_BLACK[2]);
    }
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
}

void half_one_color(int slave_number, CHSV color_one, CHSV color_two)
{
  for (int i = 0; i < slave_number; i++)
  {
    if (i < slave_number / 2) send_data(i, color_one[0], color_one[1], color_one[2]);
    else send_data(i, color_two[0], color_two[1], color_two[2]);
  }
  delay(500);
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
  Timer1.initialize(1000);
  Timer1.attachInterrupt(serial_data);
}

void loop()
{
  switch (func_choice)
  {
    case 0:
      rainbow(slave_number, color_shift);
      break;
    case 1:
      color_fade(slave_number, color_shift, lower_limit, upper_limit);
      break;
    case 2:
      all_one_color(slave_number, choosen_color, color_shift);
      break;
    case 3:
      police_light(slave_number);
    case 4:
      half_one_color(slave_number, PURE_RED, PURE_BLUE);
  }
}
