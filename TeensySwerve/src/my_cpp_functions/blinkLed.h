#include <Arduino.h>
#define PIN_NEOPIXEL 14

void blink_led(int times, int delayTime, String color){
  int r = 0;
  int g = 0;
  int b = 0;
  int intensity = 50; // max is 255, but that can cause overheating supposedly
  if (color == "red"){
    r = intensity;
    g = 0;
    b = 0;
  } else if (color == "green"){
    r = 0;
    g = intensity;
    b = 0;
  } else if (color == "blue"){
    r = 0;
    g = 0;
    b = intensity;
  } else if (color == "yellow"){
    r = intensity;
    g = intensity;
    b = 0;
  } else if (color == "cyan"){
    r = 0;
    g = intensity;
    b = intensity;
  } else if (color == "magenta"){
    r = intensity;
    g = 0;
    b = intensity;
  } else {
    r = intensity;
    g = intensity;
    b = intensity;
  }
  for (int i = 0; i < times; i++){
    //digitalWrite(LED_BUILTIN, HIGH); 
    //rgbLedWrite(PIN_NEOPIXEL, r, g, b); 
    neopixelWrite(PIN_NEOPIXEL, g, r, b);// idk why but this is the right order
    delay(delayTime);
    //digitalWrite(LED_BUILTIN, LOW);
    //rgbLedWrite(PIN_NEOPIXEL, 0, 0, 0);
    neopixelWrite(PIN_NEOPIXEL, 0, 0, 0);
    delay(delayTime);
  }
}