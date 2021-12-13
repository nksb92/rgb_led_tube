#include <FastLED.h>

#define RED_PIN 6
#define GREEN_PIN 9
#define BLUE_PIN 10

CRGB rgb;
int slave_adress = 0;
const int message_length = 4;
byte message[message_length];
int list[message_length];

void setup() {
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if (Serial.available()) {
    byte incoming_byte = Serial.read();
    Serial.println(int(incoming_byte));
    if (incoming_byte  == byte(-1))
    {
      Serial.readBytes(message, message_length);
      for (int i = 0; i < message_length; i++)
      {
        list[i] = int(message[i]);
      }
    }
  }

  if (list[0] == slave_adress)
  {
    CHSV hsv(list[1], list[2], list[3]);
    hsv2rgb_rainbow(hsv, rgb);
    analogWrite(RED_PIN, rgb[0]);
    analogWrite(GREEN_PIN, rgb[1]);
    analogWrite(BLUE_PIN, rgb[2]);
  }
}
