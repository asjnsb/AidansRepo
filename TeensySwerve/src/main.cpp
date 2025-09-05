#include <Arduino.h>
#include <WiFi.h>
#include <Motoron.h>
#include <micro_ros_platformio.h>
#include <rcl/rcl.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>
#include <tnsy_interfaces/msg/tnsy_controller.h>

//OUTSTANDING: WiFi transport can find networks, but won't connect to them.
//LAST: Discovered that the code is making into the scanforNetwork function, but not all the way through. It also isn't printing to the serial line.
//NEXT: dunno. it's not necessary that serial.println works but it would be nice

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
int counter = 0; // simple counter for the led

// WiFi configuration
//================================================
char ssid[] = "LittleMan";
char password[] = "LittleManPass";
const char* ssidh = "LittleMan";
const char* passwordh = "LittleManPass";
IPAddress agent_ip(192,168,1,205);
size_t agent_port = 8888;
IPAddress local_ip(192,168,1,123);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);
//================================================

#define PIN_NEOPIXEL 14
// Function for easy error handling when initialzing things
#define RCCHECK(fn) { rcl_ret_t temp_rc = fn; if((temp_rc != RCL_RET_OK)){error_loop();}}
// Same function but doesn't call the error loop
#define RCSOFTCHECK(fn) { rcl_ret_t temp_rc = fn; if((temp_rc != RCL_RET_OK)){}}

void timer_callback(rcl_timer_t * timer, int64_t last_call_time){
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

void blink_led(int times, int delayTime, String color){
  int r = 0;
  int g = 0;
  int b = 0;
  if (color == "red"){
    r = 255;
    g = 0;
    b = 0;
  } else if (color == "green"){
    r = 0;
    g = 255;
    b = 0;
  } else if (color == "blue"){
    r = 0;
    g = 0;
    b = 255;
  } else if (color == "yellow"){
    r = 255;
    g = 255;
    b = 0;
  } else if (color == "cyan"){
    r = 0;
    g = 255;
    b = 255;
  } else if (color == "magenta"){
    r = 255;
    g = 0;
    b = 255;
  } else {
    r = 255;
    g = 255;
    b = 255;
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

// error loop
void error_loop() {
  // if error occurs, loop forever?
  // is there a function to soft reset the board?
  while(1){
    blink_led(1,100, "red");
    Serial.println("Error occurred, entering infinite loop");
    delay(1000);
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
  // Optional: WiFi.config(local_ip, gateway, subnet);
  
  wifistatus = WiFi.begin(ssidh, passwordh);

  // Set a timeout for the connection attempt (e.g., 20 seconds)
  unsigned long start_time = millis();
  const unsigned long timeout = 60000;

  blink_led(1, 200, "blue");
  Serial.print("Connecting to WiFi");
  do {
    wifistatus = WiFi.status();

    // Check if the timeout has been reached
    if (millis() - start_time > timeout) {
      Serial.println("\nWi-Fi connection timed out. Restarting...");
      esp_restart();
    }
    
    // Blink and wait to give the ESP32 time to connect
    if (wifistatus == oldwifistatus){
      Serial.print(".");
    } else {
      Serial.print("\nWiFi status: " + wifiStatusString(wifistatus));
    }

    blink_led(1, 200, "blue");
    delay(500); 

    oldwifistatus = wifistatus;
  }while(wifistatus != WL_CONNECTED);
  
  Serial.println("\nWi-Fi connected successfully!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Set up the Micro-ROS transport
  set_microros_wifi_transports(ssid, password, agent_ip, agent_port);
  blink_led(3, 50, "green"); // Blink to indicate success
}

bool scanforNetwork(const char ssid[]){
  int n = WiFi.scanNetworks();
  if (n == 0) {
    blink_led(1, 100, "red");
    return false;

  } else if (n > 0) {
    blink_led(1, 100, "green");
    Serial.print("There are ");
    Serial.print(n);
    Serial.println(" networks visible");
    for (int i = 0; i < n; ++i) {
      Serial.println(WiFi.SSID(i));
      if (WiFi.SSID(i) == String(ssid)){
        blink_led(2, 100, "green");
        return true;
      }
    }
  } else {
    return false;
  }
}

void setup(){
  configureSerial();

  //User LED setup
  //pinMode(LED_BUILTIN, OUTPUT);
  //digitalWrite(LED_BUILTIN, LOW); // turn on the LED (active low)
  
  blink_led(5,50, "white");
  Serial.println("Hello Tnsy World");
  delay(500);
  
  while(!(scanforNetwork(ssidh))){
    blink_led(2,300, "blue");
    delay(500);
  }
  WiFiconnect();
  
  blink_led(4,100, "green");
  delay(500);

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

  blink_led(2,200, "green");
  delay(500);

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