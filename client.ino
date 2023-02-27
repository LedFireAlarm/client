#define NUM_LEDS 2
#include "FastLED.h"
#define R_PIN 16
#define L_PIN 17
#define delimiter ";"
#define serial_baudrate 9600

CRGB l_leds[NUM_LEDS];
CRGB r_leds[NUM_LEDS];
byte counter;

void setup() {
  FastLED.addLeds<WS2811, R_PIN, GRB>(l_leds, NUM_LEDS);
  FastLED.addLeds<WS2811, L_PIN, GRB>(r_leds, NUM_LEDS);
  Serial.begin(serial_baudrate);
  FastLED.setBrightness(255);
}
void loop() {
  if (Serial.available() > 0) {
    String incomingStr = Serial.readString();
    incomingStr.trim();
    int left_clr = (incomingStr.substring(0, incomingStr.indexOf(delimiter))).toInt();
    int right_clr = (incomingStr.substring(incomingStr.indexOf(delimiter)+1, -1)).toInt();
    for (int i = 0; i < NUM_LEDS; i++ ) {
      
      if (left_clr >= 0) {
        l_leds[i].setRGB(0,  0, floor(255 / 100 * left_clr));
      }
      else {
        l_leds[i].setRGB(abs(floor(255 / 100 * left_clr)), 0, 0);        
      }
      if (right_clr >= 0) {
        r_leds[i].setRGB(0, 0, floor(255 / 100 * right_clr));
      }
      else {
        r_leds[i].setRGB(abs(floor(255 / 100 * right_clr)), 0, 0);        
      }
    }
    counter++;        // counter меняется от 0 до 255 (тип данных byte)
    FastLED.show();
    delay(5);         // скорость движения радуги    
    Serial.print(incomingStr);
  }
    
}
