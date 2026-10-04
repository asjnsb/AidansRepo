#include <Arduino.h>
#include <driver/mcpwm.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

#define PIN 14

// Create the matrix object based on the actual thing
// Switching the first piexel around with NEO_MATRIX_BOTTOM/TOP & NEO_MATRIX_RIGHT/LEFT will adjust what orientation things are displayed in
// Current orientation is USBC port down (bottom+right)
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, PIN,
    NEO_MATRIX_BOTTOM + NEO_MATRIX_RIGHT +
    NEO_MATRIX_ROWS + NEO_MATRIX_PROGRESSIVE,
    NEO_RGB + NEO_KHZ800);

bool blinkOn = false;
unsigned long callTime = 0;
unsigned long lastBlink = 0;
uint16_t forward = matrix.Color(0, 255, 0);
uint16_t reverse = matrix.Color(255, 0, 0);
uint32_t orange = matrix.Color(255, 200, 0);
float driveCompare[] = {
    1.0/8.0,
    2.0/8.0,
    3.0/8.0,
    4.0/8.0,
    5.0/8.0,
    6.0/8.0,
    7.0/8.0,
    1.0
}; // I know it's not hard to do, but this way these calcs only happen once rather than every time the function is called.
float weaponCompare[] = {
    1.0/16.0,
    2.0/16.0,
    3.0/16.0,
    4.0/16.0,
    5.0/16.0,
    6.0/16.0,
    7.0/16.0,
    8.0/16.0,
    9.0/16.0,
    10.0/16.0,
    11.0/16.0,
    12.0/16.0,
    13.0/16.0,
    14.0/16.0,
    15.0/16.0,
    1.0
};

// brightness 0-1.0. if brightness = 0, matrix will be minimum brightness
void matrixInit(float brightness){
    matrix.begin();

    uint8_t brightnessValue;
    if (brightness <= 0) brightnessValue = 1;
    else if (brightness > 1) brightnessValue = 255;
    else brightnessValue = brightness * 255;
    matrix.setBrightness(brightnessValue);
}

// this function is here partly to maintain legacy code and partly to have a blink function that doesn't have to be continuously called.
void blinkLED(int times, int delayTime, String color){

    uint16_t ledColor = matrix.Color(255, 255, 255);

    matrix.clear();

    if (color == "red"){
        ledColor = matrix.Color(255, 0, 0);

    } else if (color == "green"){
        ledColor = matrix.Color(0, 255, 0);

    } else if (color == "blue"){
        ledColor = matrix.Color(0, 0, 255);

    } else if (color == "yellow"){
        ledColor = matrix.Color(255, 255, 0);

    } else if (color == "cyan"){
        ledColor = matrix.Color(0, 255, 255);

    } else if (color == "magenta"){
        ledColor = matrix.Color(255, 0, 255);
        
    } else {
        ledColor = matrix.Color(255, 255, 255);
        
    }
    for (int i = 0; i < times; i++){
        
        matrix.drawRect(0, 0, 2, 2, ledColor);
        matrix.drawRect(6, 0, 2, 2, ledColor);
        matrix.drawRect(0, 6, 2, 2, ledColor);
        matrix.drawRect(6, 6, 2, 2, ledColor);
        matrix.show();
        delay(delayTime);

        matrix.drawRect(0, 0, 2, 2, 0);
        matrix.drawRect(6, 0, 2, 2, 0);
        matrix.drawRect(0, 6, 2, 2, 0);
        matrix.drawRect(6, 6, 2, 2, 0);
        matrix.show();
        delay(delayTime);
    }
}

// blinkPeriod in ms
void statusBlink(uint16_t color, unsigned long blinkPeriod = 500){
    if (blinkPeriod <= 0 ) blinkOn = true;
    else if (callTime - lastBlink >= blinkPeriod) {
        lastBlink = callTime;
        blinkOn = !blinkOn;
    }

    if (!blinkOn) color = 0;
    
    matrix.drawRect(0, 0, 2, 2, color);
    matrix.drawRect(6, 0, 2, 2, color);
    matrix.drawRect(0, 6, 2, 2, color);
    matrix.drawRect(6, 6, 2, 2, color);
}

void driveDisplay(float power[]){
    if (power[0] >= driveCompare[0]) matrix.drawPixel(0, 5, forward);
    if (power[0] >= driveCompare[1]) matrix.drawPixel(1, 5, forward);
    if (power[0] >= driveCompare[2]) matrix.drawPixel(0, 4, forward);
    if (power[0] >= driveCompare[3]) matrix.drawPixel(1, 4, forward);
    if (power[0] >= driveCompare[4]) matrix.drawPixel(0, 3, forward);
    if (power[0] >= driveCompare[5]) matrix.drawPixel(1, 3, forward);
    if (power[0] >= driveCompare[6]) matrix.drawPixel(0, 2, forward);
    if (power[0] >= driveCompare[7]) matrix.drawPixel(1, 2, forward);
    
    if (power[0] <= -driveCompare[0]) matrix.drawPixel(0, 2, reverse);
    if (power[0] <= -driveCompare[1]) matrix.drawPixel(1, 2, reverse);
    if (power[0] <= -driveCompare[2]) matrix.drawPixel(0, 3, reverse);
    if (power[0] <= -driveCompare[3]) matrix.drawPixel(1, 3, reverse);
    if (power[0] <= -driveCompare[4]) matrix.drawPixel(0, 4, reverse);
    if (power[0] <= -driveCompare[5]) matrix.drawPixel(1, 4, reverse);
    if (power[0] <= -driveCompare[6]) matrix.drawPixel(0, 5, reverse);
    if (power[0] <= -driveCompare[7]) matrix.drawPixel(1, 5, reverse);


    if (power[1] >= driveCompare[0]) matrix.drawPixel(7, 5, forward);
    if (power[1] >= driveCompare[1]) matrix.drawPixel(6, 5, forward);
    if (power[1] >= driveCompare[2]) matrix.drawPixel(7, 4, forward);
    if (power[1] >= driveCompare[3]) matrix.drawPixel(6, 4, forward);
    if (power[1] >= driveCompare[4]) matrix.drawPixel(7, 3, forward);
    if (power[1] >= driveCompare[5]) matrix.drawPixel(6, 3, forward);
    if (power[1] >= driveCompare[6]) matrix.drawPixel(7, 2, forward);
    if (power[1] >= driveCompare[7]) matrix.drawPixel(6, 2, forward);

    if (power[1] <= -driveCompare[0]) matrix.drawPixel(7, 2, reverse);
    if (power[1] <= -driveCompare[1]) matrix.drawPixel(6, 2, reverse);
    if (power[1] <= -driveCompare[2]) matrix.drawPixel(7, 3, reverse);
    if (power[1] <= -driveCompare[3]) matrix.drawPixel(6, 3, reverse);
    if (power[1] <= -driveCompare[4]) matrix.drawPixel(7, 4, reverse);
    if (power[1] <= -driveCompare[5]) matrix.drawPixel(6, 4, reverse);
    if (power[1] <= -driveCompare[6]) matrix.drawPixel(7, 5, reverse);
    if (power[1] <= -driveCompare[7]) matrix.drawPixel(6, 5, reverse);
    
}

void weaponDisplay(float power[]){
    if (power[0] >= weaponCompare[0])  matrix.drawPixel(2, 0, orange);
    if (power[0] >= weaponCompare[1])  matrix.drawPixel(3, 0, orange);
    if (power[0] >= weaponCompare[2])  matrix.drawPixel(4, 0, orange);
    if (power[0] >= weaponCompare[3])  matrix.drawPixel(5, 0, orange);
    if (power[0] >= weaponCompare[4])  matrix.drawPixel(2, 1, orange);
    if (power[0] >= weaponCompare[5])  matrix.drawPixel(3, 1, orange);
    if (power[0] >= weaponCompare[6])  matrix.drawPixel(4, 1, orange);
    if (power[0] >= weaponCompare[7])  matrix.drawPixel(5, 1, orange);
    if (power[0] >= weaponCompare[8])  matrix.drawPixel(2, 2, orange);
    if (power[0] >= weaponCompare[9])  matrix.drawPixel(3, 2, orange);
    if (power[0] >= weaponCompare[10]) matrix.drawPixel(4, 2, orange);
    if (power[0] >= weaponCompare[11]) matrix.drawPixel(5, 2, orange);
    if (power[0] >= weaponCompare[12]) matrix.drawPixel(2, 3, orange);
    if (power[0] >= weaponCompare[13]) matrix.drawPixel(3, 3, orange);
    if (power[0] >= weaponCompare[14]) matrix.drawPixel(4, 3, orange);
    if (power[0] >= weaponCompare[15]) matrix.drawPixel(5, 3, orange);

    if (power[1] >= weaponCompare[0])  matrix.drawPixel(5, 7, orange);
    if (power[1] >= weaponCompare[1])  matrix.drawPixel(4, 7, orange);
    if (power[1] >= weaponCompare[2])  matrix.drawPixel(3, 7, orange);
    if (power[1] >= weaponCompare[3])  matrix.drawPixel(2, 7, orange);
    if (power[1] >= weaponCompare[4])  matrix.drawPixel(5, 6, orange);
    if (power[1] >= weaponCompare[5])  matrix.drawPixel(4, 6, orange);
    if (power[1] >= weaponCompare[6])  matrix.drawPixel(3, 6, orange);
    if (power[1] >= weaponCompare[7])  matrix.drawPixel(2, 6, orange);
    if (power[1] >= weaponCompare[8])  matrix.drawPixel(5, 5, orange);
    if (power[1] >= weaponCompare[9])  matrix.drawPixel(4, 5, orange);
    if (power[1] >= weaponCompare[10]) matrix.drawPixel(3, 5, orange);
    if (power[1] >= weaponCompare[11]) matrix.drawPixel(2, 5, orange);
    if (power[1] >= weaponCompare[12]) matrix.drawPixel(5, 4, orange);
    if (power[1] >= weaponCompare[13]) matrix.drawPixel(4, 4, orange);
    if (power[1] >= weaponCompare[14]) matrix.drawPixel(3, 4, orange);
    if (power[1] >= weaponCompare[15]) matrix.drawPixel(2, 4, orange);
}



void matrixUpdate(float drivePower[], float weaponPower[], uint16_t blinkColor, unsigned long blinkPeriod = 500){
    callTime = millis();

    matrix.clear();

    statusBlink(blinkColor, blinkPeriod);
    driveDisplay(drivePower);
    weaponDisplay(weaponPower);
    
    matrix.show();
}

//================MISC FUNCTIONS===============================================

String wifiStatusString(uint8_t status){
  switch(status){
    case WL_NO_SHIELD:
      return "WL_NO_SHIELD";
    case WL_IDLE_STATUS:
      return "WL_IDLE_STATUS";
    case WL_NO_SSID_AVAIL:
      return "WL_NO_SSID_AVAIL";
    case WL_SCAN_COMPLETED:
      return "WL_SCAN_COMPLETED";
    case WL_CONNECTED:
      return "WL_CONNECTED";
    case WL_CONNECT_FAILED:
      return "WL_CONNECT_FAILED";
    case WL_CONNECTION_LOST:
      return "WL_CONNECTION_LOST";
    case WL_DISCONNECTED:
      return "WL_DISCONNECTED";
    default:
      return "UNKNOWN";
  }
}

void WiFiconnect(char* ssid, char* password){
  uint8_t wifistatus;
  uint8_t oldwifistatus;
  
  WiFi.disconnect();
  WiFi.mode(WIFI_STA);
  wifistatus = WiFi.begin(ssid, password);

  // Set a timeout for the connection attempt in ms
  unsigned long start_time = millis();
  const unsigned long timeout = 60000;

  
  Serial.println("Connecting to WiFi");
  do {
    wifistatus = WiFi.status();

    // Check if the timeout has been reached
    if (millis() - start_time > timeout) {
      Serial.println("\nWi-Fi connection timed out. Restarting...");
      blinkLED(1,50, "blue");
      blinkLED(1,50, "red");
      esp_restart();
    }
    
    // Blink and wait to give the ESP32 time to connect
    if (wifistatus == oldwifistatus){
      Serial.print(".");
    } else {
      Serial.print("\n" + wifiStatusString(wifistatus));
    }

    blinkLED(1, 150, "blue"); 

    oldwifistatus = wifistatus;
  }while(wifistatus != WL_CONNECTED);
  Serial.println("");
}