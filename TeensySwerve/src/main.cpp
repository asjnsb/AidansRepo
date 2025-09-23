#include <Arduino.h>
#include <WiFi.h>
#include <Motoron.h>
#include <micro_ros_platformio.h>
#include <rcl/rcl.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>
#include <tnsy_interfaces/msg/tnsy_controller.h>
#include <my_cpp_functions/blinkLed.h>

//LAST: the matrix board will connect to FBISurveillance van, but not the hotspot

tnsy_interfaces__msg__TnsyController tnsymsg = *tnsy_interfaces__msg__TnsyController__create(); // create a message to hold the data from the subscription
rcl_subscription_t subscriber;
rclc_executor_t executor;
rclc_support_t support;
rcl_allocator_t allocator;
rcl_node_t node;
rcl_timer_t timer;
MotoronI2C mc;
WiFiSTAClass wifiSTA;
WiFiGenericClass wifiGEN;

// User constants
const int maxSpeed = 800;
int timer_timeout = 1; // in milliseconds, how often the timer callback is 

// WiFi configuration
//================================================
const char ssid[] = "TeensyHotspot";
const char password[] = "TeensyPass";
char* ssidh = "TeensyHotspot";
char* passwordh = "TeensyPass";
IPAddress agent_ip(192,168,1,205);
uint16_t agent_port = 8888;
IPAddress local_ip(192,168,1,123);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,0,0);
//================================================

// Function Declarations
// Function for easy error handling when initialzing things
#define RCCHECK(fn) { rcl_ret_t temp_rc = fn; if((temp_rc != RCL_RET_OK)){error_loop();}}
// Same function but doesn't call the error loop
#define RCSOFTCHECK(fn) { rcl_ret_t temp_rc = fn; if((temp_rc != RCL_RET_OK)){}}
void timer_callback(rcl_timer_t * timer, int64_t last_call_time);
void subscription_callback(const void * msgin);
void error_loop();
String wifiStatusString(int status);
void configureSerial();
void WiFiconnect();
bool scanforNetwork(const char ssid[]);

void setup(){
  configureSerial();
  
  blink_led(5,50, "white");
  Serial.println("Hello Tnsy World");
  delay(500);
  
  /* scanforNetworks takes annoyingly long to run
  while(!(scanforNetwork(ssidh))){
    blink_led(2,300, "blue");
    delay(500);
  }*/
  
  WiFiconnect();

  //motoron setup
  int maxAcc = 500;
  int maxDec = 1000;
  mc.reinitialize();
  mc.disableCrc();
  mc.clearResetFlag();
  mc.setMaxAcceleration(1,maxAcc);
  mc.setMaxDeceleration(1,maxDec);
  mc.setMaxAcceleration(2,maxAcc);
  mc.setMaxDeceleration(2,maxDec);

  blink_led(3,150, "cyan");
  delay(500);

  allocator = rcl_get_default_allocator();

  //create init_options
  RCCHECK(rclc_support_init(&support, 0, NULL, &allocator));

  // create node (&node, node name, namespace, &support)
  RCCHECK(rclc_node_init_default(&node, "ESP32Node", "", &support));

  // create subscriber with "reliable" qos. use rclc_subscription_init_best_effort() for "best effort"
  RCCHECK(rclc_subscription_init_default(
    &subscriber,
    &node,
    ROSIDL_GET_MSG_TYPE_SUPPORT(tnsy_interfaces, msg, TnsyController),
    "nameSpace1/tnsy_controller"));

  // create timer
  RCCHECK(rclc_timer_init_default(
    &timer,
    &support,
    RCL_MS_TO_NS(timer_timeout),
    timer_callback));

  // create executor (&executor, &support context, # of handles, &allocator)
  RCCHECK(rclc_executor_init(&executor, &support.context, 2, &allocator));
  RCCHECK(rclc_executor_add_timer(&executor, &timer));
  RCCHECK(rclc_executor_add_subscription(&executor, &subscriber, &tnsymsg, subscription_callback, ON_NEW_DATA));

  blink_led(5,50, "green");
  RCSOFTCHECK(rclc_executor_spin(&executor));
  
  RCCHECK(rcl_subscription_fini(&subscriber, &node));
  RCCHECK(rcl_timer_fini(&timer));
  RCCHECK(rcl_node_fini(&node));
}

void loop() {
  delay(1000);
}

void timer_callback(rcl_timer_t * timer, int64_t last_call_time){
  blink_led(1,0,"Green");
  RCLC_UNUSED(last_call_time);
  if (timer != NULL) {
    // main timer area
    float motorSpeed = (maxSpeed * tnsymsg.translation_magnitude)*cos(tnsymsg.translation_angle * M_PI / 180.0);
    mc.setSpeed(1, motorSpeed); // set speed for motor 1
    mc.setSpeed(2, motorSpeed); // set speed for motor 2

  }
}

void subscription_callback(const void * msgin){
  //tnsymsg = *msgin; // copy the message to the global variable tnsymsg
}

// error loop
void error_loop() {
  // if error occurs, loop forever?
  // is there a function to soft reset the board?
  while(1){
    Serial.println("Error occurred, restarting...");
        (3,250, "red");
    esp_restart();
  }
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

void configureSerial(){
  // Configure serial transport
  Wire.begin();
  Serial.begin(115200);
  //set_microros_serial_transports(Serial);
}

void WiFiconnect() {
  uint8_t wifistatus;
  uint8_t oldwifistatus;
  
  WiFi.disconnect();

  WiFi.mode(WIFI_STA);
  //WiFi.config(local_ip, gateway, subnet);
  
  wifistatus = WiFi.begin(ssidh, passwordh);

  // Set a timeout for the connection attempt in ms
  unsigned long start_time = millis();
  const unsigned long timeout = 60000;

  blink_led(2, 50, "blue");
  Serial.print("Connecting to WiFi");
  do {
    wifistatus = WiFi.status();

    // Check if the timeout has been reached
    if (millis() - start_time > timeout) {
      Serial.println("\nWi-Fi connection timed out. Restarting...");
      blink_led(3,50, "red");
      esp_restart();
    }
    
    // Blink and wait to give the ESP32 time to connect
    if (wifistatus == oldwifistatus){
      Serial.print(".");
    } else {
      Serial.print("\n" + wifiStatusString(wifistatus));
    }

    blink_led(1, 250, "blue"); 

    oldwifistatus = wifistatus;
  }while(wifistatus != WL_CONNECTED);
  
  Serial.println("\nWi-Fi connected successfully!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Set up the Micro-ROS transport
  set_microros_wifi_transports(ssidh, passwordh, agent_ip, agent_port);
  blink_led(3, 50, "green"); // Blink to indicate success
}

bool scanforNetwork(const char ssid[]){
  int n = 0;
  n = WiFi.scanNetworks();
  if (n == 0) {
    blink_led(1, 100, "red");
    return false;

  } else if (n > 0) {
    blink_led(n, 100, "blue");
    Serial.print("There are ");
    Serial.print(n);
    Serial.println(" networks visible");
    for (int i = 0; i < n; i++) {
      Serial.print(String(i) + "<" + String(n) + "= " + String(i<n) + " ");
      Serial.print("Network #" + String(i) + ": ");
      Serial.println(WiFi.SSID(i));
      if (WiFi.SSID(i) == String(ssid)){
        blink_led(2, 50, "cyan");
        return true;
      }
      delay(100);
    }
  } else {
    return false;
  }
}