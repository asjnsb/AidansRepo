#include <Arduino.h>
#include <WiFi.h>
#include <Udp.h>

// WiFi configuration
//================================================
const char* ssid = "TeensyHotspot";
const char* password = "TeensyPass";
//================================================

// Function prototypes
//void blink_led(int times, int delayTime);
void WiFiconnect();
String wifiStatusString(int status);

void setup() {
  delay(3000);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  blink_led(2, 125);
  Serial.println("Hello Teensy World");

  WiFiconnect();

}

void loop() {
  blink_led(1, 1000);

  String wifiStatus = wifiStatusString(WiFi.status());

  Serial.println("WiFi Status: " + wifiStatus);
}

void blink_led(int times, int delayTime){
  for (int i = 0; i < times; i++){
    digitalWrite(LED_BUILTIN, HIGH); 
    delay(delayTime);
    digitalWrite(LED_BUILTIN, LOW);
    delay(delayTime);
  }
}

void WiFiconnect() {
  uint8_t wifistatus;
  uint8_t oldwifistatus;
  
  WiFi.disconnect();

  WiFi.mode(WIFI_AP);  

  if(WiFi.softAP(ssid, password)){
    Serial.println("AP Created Successfully");
    blink_led(3, 50);
  } else{
    Serial.println("AP Creation Failed, Restarting Board...");
    blink_led(20,50);
    ESP.restart();
  }
  
  IPAddress myIP = WiFi.softAPIP();

  Serial.println("Starting "+ String(ssid));
  Serial.println("Pass = " + String(password));
  Serial.println("AP IP = "+ String(myIP));
}

String wifiStatusString(int status){
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