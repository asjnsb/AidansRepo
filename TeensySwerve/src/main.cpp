#include <Arduino.h>
#include <WiFi.h>
#include <Motoron.h>
#include <micro_ros_platformio.h>
#include <rcl/rcl.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>
#include <tnsy_interfaces/msg/tnsy_controller.h>
#include <my_cpp_functions/blinkLed.h>

//LAST: The motors don't work. the PWM one is constantly resetting and the i2c one claims it isn't receiving communication
//PWM: the constant resetting could be the PWM signal being interrupted constantly, and I need to send a constant signal that I modify instead
//I2C: I think this is working now, I just need to get the board to react to changes in the joy commands
//ALSO: need to make sure the robot fails safe

tnsy_interfaces__msg__TnsyController tnsymsg = *tnsy_interfaces__msg__TnsyController__create(); // create a message to hold the data from the subscription
rcl_subscription_t subscriber;
rclc_executor_t executor;
rclc_support_t support;
rcl_allocator_t allocator;
rcl_node_t node;
rcl_timer_t timer;
MotoronI2C mc;

// User constants
const int maxSpeed = 800;
const int maxWeaponSpeed = 255; // 0-255 is full range?
const int minWeaponSpeed = 0; // this might be a value if the controller is in bi-directional mode
int timer_timeout = 0.1; // in milliseconds, how often the timer callback is 
const int motorChannel_BigTwo = 33;
const int motorChannel_BigOne = 34;
#define I2C_SCL 1
#define I2C_SDA 2
//I don't think these are needed
//const int pwmFrequency = 4000000; //40 MHz is the max I believe
//const int pwmResolution = 16; //16 bit is the max I believe

// WiFi configuration
//================================================
char* ssid = "TeensyHotspot";//"FBISurveillanceVan#23";
char* password = "TeensyPass";//"m@xsT0pT0uchingTh@T";
IPAddress agent_ip(10,206,72,34);
uint16_t agent_port = 8888;
//================================================

// Function Declarations
// Function for easy error handling when initialzing things
#define RCCHECK(fn) { rcl_ret_t temp_rc = fn; if((temp_rc != RCL_RET_OK)){error_loop();}}
// Same function but doesn't call the error loop
#define RCSOFTCHECK(fn) { rcl_ret_t temp_rc = fn; if((temp_rc != RCL_RET_OK)){}}
void timer_callback(rcl_timer_t * timer, int64_t last_call_time);
void subscription_callback(const void * msgin);
void error_loop();
String wifiStatusString(uint8_t status);
void configureSerial();
void WiFiconnect();

void setup(){
  configureSerial();
  
  blink_led(5,50, "white");
  Serial.println("Hello Tnsy World");
  delay(500);
  
  WiFiconnect();
  
  //set_microros_serial_transports(Serial);
  set_microros_wifi_transports(ssid, password, agent_ip, agent_port);

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


  blink_led(1,150, "cyan");


  RCCHECK(rmw_uros_ping_agent(100, 10)); // (delay between attempts in ms, number of attempts)

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
  Serial.println("Spinning Executor");
  RCSOFTCHECK(rclc_executor_spin(&executor));
  
  RCCHECK(rcl_subscription_fini(&subscriber, &node));
  RCCHECK(rcl_timer_fini(&timer));
  RCCHECK(rcl_node_fini(&node));
}

void loop() {
  delay(1000);
}

void timer_callback(rcl_timer_t * timer, int64_t last_call_time){
  RCLC_UNUSED(last_call_time);
  if (timer != NULL) {

    // main timer area
    if (tnsymsg.enable_switch){
      neopixelWrite(14, 255, 0, 0);// (g, r, b)
      // not sure if these sin & cos are correct
      float motorSpeedOne = (maxSpeed * tnsymsg.translation_magnitude)*cos(tnsymsg.translation_angle * M_PI / 180.0);
      float motorSpeedTwo = (maxSpeed * tnsymsg.translation_magnitude)*sin(tnsymsg.translation_angle * M_PI / 180.0);
      
      int motorBigSpeedOne = 0;
      int motorBigSpeedTwo = 0;

      if(tnsymsg.button_one){
        motorBigSpeedOne = maxWeaponSpeed;
        motorBigSpeedTwo = 0;
      }else{
        motorBigSpeedOne = tnsymsg.weapon_speed * maxWeaponSpeed;
        motorBigSpeedTwo = tnsymsg.weapon_speed * maxWeaponSpeed;
      }

      mc.setSpeed(1, motorSpeedOne);
      //mc.setSpeed(2, motorSpeedTwo);
      analogWrite(motorChannel_BigOne, motorBigSpeedOne);
      analogWrite(motorChannel_BigTwo, motorBigSpeedTwo);

    }else{
      neopixelWrite(14, 0, 255, 0); // (g, r, b)
      mc.setSpeed(1, 0);
      //mc.setSpeed(2, 0);
      analogWrite(motorChannel_BigOne, minWeaponSpeed);
      analogWrite(motorChannel_BigTwo, minWeaponSpeed);
    }
  }
}

void subscription_callback(const void * msgin){
  // This doesn't need to contain anything for ROS to update the message variable (defined elsewhere)
  //tnsymsg = *msgin; // copy the message to the global variable tnsymsg
}

// error loop
void error_loop() {
  // if error occurs, loop forever?
  // is there a function to soft reset the board?
  while(1){
    Serial.println("Error occurred, restarting...");
    blink_led(3,250, "red");
    esp_restart();
  }
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

void configureSerial(){
  // Configure serial transport
  Wire.begin(I2C_SDA, I2C_SCL);
  Serial.begin(115200);
}

void WiFiconnect() {
  uint8_t wifistatus;
  uint8_t oldwifistatus;
  
  WiFi.disconnect();
  WiFi.mode(WIFI_STA);
  wifistatus = WiFi.begin(ssid, password);

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

  Serial.println();
  blink_led(3, 50, "green"); // Blink to indicate success
}