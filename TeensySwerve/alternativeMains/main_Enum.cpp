#include <Arduino.h>
#include <WiFi.h>
#include <Motoron.h>
#include <micro_ros_platformio.h>
#include <rcl/rcl.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>
#include <tnsy_interfaces/msg/tnsy_controller.h>

//LAST: WiFi transport can find networks, but won't connect to them.
//NEXT: Finish implementing the scanforNetwork function

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
int wifistatus = WL_IDLE_STATUS;

// WiFi configuration
//================================================
char ssid[] = "FBISurveillanceVan#23";
char password[] = "m@xsT0pT0uchingTh@T";
const char* ssidh = "FBISurveillanceVan#23";
const char* passwordh = "M@xsT0pT0uchingTh@T";
IPAddress agent_ip(192,168,1,205);
size_t agent_port = 8888;
IPAddress local_ip(192,168,1,123);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);
//================================================
//state machine enumerator
enum states {
  WAITING_AGENT,
  AGENT_AVAILABLE,
  AGENT_CONNECTED,
  AGENT_DISCONNECTED
} state;

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

// error loop
void error_loop() {
  // if error occurs, loop forever?
  // is there a function to soft reset the board?
  while(1){
    delay(100);
  }
}

void blink_led(int times, int delayTime){
  for (int i = 0; i < times; i++){
    digitalWrite(LED_BUILTIN, HIGH);    
    delay(delayTime);
    digitalWrite(LED_BUILTIN, LOW);
    delay(delayTime);
  }
}

void subscription_callback(const void * msgin){
  //tnsymsg = *msgin; // copy the message to the global variable tnsymsg
}

void configureSerial(){
  // Configure serial transport
  Wire.begin();
  Serial.begin(115200);
  //set_microros_serial_transports(Serial);
}

void configureWiFi(){

  // Configure WiFi transport
  WiFi.mode(WIFI_STA);

  //WiFi.config(local_ip, gateway, subnet);
  int networkCount = WiFi.scanNetworks();
  blink_led(5,50);
  wifistatus = WiFi.begin(ssidh, passwordh);

  // Wait for connection
  while (wifistatus != WL_CONNECTED) {
    WiFi.mode(WIFI_STA);
    wifistatus = WiFi.begin(ssidh, passwordh);
    blink_led(1,200);
    delay(500);

    // Reconnect if connection failed
    if (WiFi.status() == WL_CONNECT_FAILED){
      blink_led(3,50);
      //WiFi.begin(ssidh, passwordh);
    }
  }

  set_microros_wifi_transports(ssid, password, agent_ip, agent_port);
}

bool scanforNetwork(const char ssid[]){
  int n = WiFi.scanNetworks();
  if (n == 0) {
      return false;

  } else {
    Serial.print("There are ");
    Serial.print(n);
    Serial.println(" networks visible");
    for (int i = 0; i < n; ++i) {
      Serial.println(WiFi.SSID(i));
      if (WiFi.SSID(i) == ssid){
        return true;
      }
    }
  }
}

void setup(){
  configureSerial();

  //User LED setup
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW); // turn on the LED (active low)
  
  blink_led(5,50);
  delay(500);
  
  while(!(scanforNetwork(ssidh))){
    blink_led(2,300);
    delay(500);
  }
  configureWiFi();
  
  blink_led(4,100);
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

  blink_led(3,150);
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

  blink_led(2,200);
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

  blink_led(5,50);
  RCSOFTCHECK(rclc_executor_spin(&executor));
  
  RCCHECK(rcl_subscription_fini(&subscriber, &node));
  RCCHECK(rcl_timer_fini(&timer));
  RCCHECK(rcl_node_fini(&node));
}

void loop() {
  delay(1000);
}