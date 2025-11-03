#include <Arduino.h>
#include <WiFi.h>

#define PIN_NEOPIXEL 14

// WiFi configuration
//================================================
const char* ssid = "TeensyHotspot";
const char* password = "TeensyPass";
//================================================

// Function prototypes
void blink_led(int times, int delayTime, String color);
void WiFiconnect();
String wifiStatusString(uint8_t status);

void setup() {
  delay(3000);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  blink_led(2, 125, "blue");
  Serial.println("Hello Tnsy World");

  WiFiconnect();

}

void loop() {
  blink_led(1, 1000, "green");

  String wifiStatus = wifiStatusString(WiFi.status());
  Serial.println(wifiStatus);
}

void WiFiconnect() {
  uint8_t wifistatus;
  uint8_t oldwifistatus;
  
  WiFi.disconnect();

  WiFi.mode(WIFI_AP);  

  if(WiFi.softAP(ssid, password)){
    Serial.println("AP Created Successfully");
    blink_led(3, 50, "green");
  } else{
    Serial.println("AP Creation Failed, Restarting Board...");
    blink_led(20, 50, "red");
    ESP.restart();
  }
  
  IPAddress myIP = WiFi.softAPIP();

  Serial.println("Starting "+ String(ssid));
  Serial.println("Pass = " + String(password));
  Serial.println("AP IP = "+ String(myIP));
}

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

void blink_led(int times, int delayTime, String color){
  int r = 0;
  int g = 0;
  int b = 0;
  int intensity = 170; // max is 255, but that can cause overheating supposedly
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
    neopixelWrite(PIN_NEOPIXEL, g, r, b); // idk why but this is the right order
    delay(delayTime);
    //digitalWrite(LED_BUILTIN, LOW);
    neopixelWrite(PIN_NEOPIXEL, 0, 0, 0);
    delay(delayTime);
  }
}