#include <FastLED.h>

#define TXSIZE 5

void send_data(int adress, int hue, int sat, int val)
{
  byte message[TXSIZE] = {byte("<"), byte(adress), byte(hue), byte(sat), byte(val)};
  Serial.write(message, TXSIZE);
}

void rainbow(int slave_number, int color_shift)
/*
   Sets all tubes to a rainbow animation, if wanted with a shift in color per tube
   Shift of 0 sets all the same color
*/
{
  for (int i = 0; i <= 255; i++)
  {
    CHSV hsv(i, 255, 255);
    for (int j = 0; j <= slave_number; j++) {
      send_data(j, (hsv[0] + (j * color_shift)) % 255, hsv[1], hsv[2]);
    }
    delay(50); // vary animation speed
  }
}

void color_fade(int slave_number, int color_shift, int lower_limit, int upper_limit)
{
  /*

  */
  for (int i = lower_limit; i <= upper_limit; i++)
  {
    CHSV hsv(i, 255, 255);
    for (int j = 0; j <= slave_number; j++) {
      send_data(j, (hsv[0] + (j * color_shift)) % 255, hsv[1], hsv[2]);
    }
    delay(50);
  }
  for (int i = upper_limit; i >= lower_limit; i--)
  {
    CHSV hsv(i, 255, 255);
    for (int j = 0; j <= slave_number; j++) {
      send_data(j, (hsv[0] + (j * color_shift)) % 255, hsv[1], hsv[2]);
    }
    delay(50);
  }
}

void one_color(int adress, int hue, int sat, int val, int color_shift)
/*
   Sets all tubes to one color, if wanted with a shift in color per tube
*/
{

  send_data(adress, (hue + adress * color_shift) % 255, sat, val);

}

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  one_color(1, 160, 255, 255, 0);
  one_color(0, 0, 255, 255, 0);
  //color_fade(1, 0, 0, 50);
  //rainbow(1, 50);
}
