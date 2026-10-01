#include <WiFi.h>
#include <Arduino.h>
#include <Motoron.h>
#include <rcl/rcl.h>
#include <rclc/rclc.h>
#include <driver/mcpwm.h>
#include <rclc/executor.h>
#include <micro_ros_platformio.h>
#include <my_cpp_functions/blinkLed.h>
#include <my_cpp_functions/myLEDMatrix.h>
#include <tnsy_interfaces/msg/tnsy_controller.h>


//LAST: testing at space coast showdown reveals very bad delay in a noisy wifi environment...
//NEXT: Error handling & failsafe and proper translation of controller inputs to drive motors
//ALSO: Maybe just use "drive" and "weapon" insteal of "motor" and "motorBig"
//AND: Use left & right and front & back (fore aft?) instead of 1 & 2

// WiFi configuration
//================================================
char* ssid = "TeensyHotspot";
char* password = "TeensyPass";
IPAddress agent_ip(172,18,98,34);
uint16_t agent_port = 8888;
//================================================

tnsy_interfaces__msg__TnsyController tnsymsg = *tnsy_interfaces__msg__TnsyController__create(); // create a message to hold the data from the subscription
tnsy_interfaces__msg__TnsyController statusmsg = *tnsy_interfaces__msg__TnsyController__create();
rcl_subscription_t subscriber;
rcl_publisher_t publisher;
rclc_executor_t executor;
rclc_support_t support;
rcl_allocator_t allocator;
rcl_node_t node;
rcl_timer_t timer;
MotoronI2C mc1(15);// Set mc1 to i2c channel 15
MotoronI2C mc2(16);

// User vars
const int maxSpeed = 800;
int maxAcc = 500;
int maxDec = 1000;
const float maxWeaponSpeed = 1; // on a scale of 0.0 to 1.0
const float minWeaponSpeed = 0; 
int timer_timeout = 50; // in milliseconds, how frequent the timer callback is 
#define I2C_SCL 1
#define I2C_SDA 2
int intensity = 0;
uint16_t motorSpeedOne = 0;
uint16_t motorSpeedTwo = 0;
float driveSpeeds[] = {0.0, 0.0};
int motorBig_PinTwo = 34;
float motorBigSpeedOne = 0;
float motorBigSpeedTwo = 0;
float weaponSpeeds[] = {0.0, 0.0};
//mcpwm Configuration
const mcpwm_pin_config_t pwmPins = { // the name of the pin needs to match the relevent unit(X)/generator(N): mcpwmXN_out_num
  .mcpwm0a_out_num = 5,
  .mcpwm0b_out_num = 6,
};
//There are two units (0 & 1). Each unit has three timers (0, 1, 2) and two generators (A & B)
const mcpwm_unit_t pwmUnit0 = MCPWM_UNIT_0;
const mcpwm_timer_t pwmTimer0 = MCPWM_TIMER_0;
const mcpwm_generator_t pwmGenA = MCPWM_GEN_A;
const mcpwm_generator_t pwmGenB = MCPWM_GEN_B;
mcpwm_config_t pwmConfig{
  .frequency = 500, // An AM32 MC wants the period to be 2ms
  .cmpr_a = 50, // set the two comparators to a duty cycle of 50% (0% throttle according to an am32 MC)
  .cmpr_b = 50,
  .duty_mode = MCPWM_DUTY_MODE_0, //Active high duty, i.e. duty cycle proportional to high time for asymmetric MCPWM
  .counter_mode = MCPWM_UP_COUNTER
};

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
void configurePWM();
void setupMotoron();
void updatePWM(float motorA, float motorB);
void WiFiconnect();

void setup(){
  configureSerial();
  configurePWM();
  setupMotoron();
  matrixInit(1);
  
  blinkLED(5,50, "white");
  Serial.println("Hello Tnsy World");
  
  WiFiconnect();
  set_microros_wifi_transports(ssid, password, agent_ip, agent_port);

  blinkLED(1,50, "cyan");
  
  blinkLED(1,50, "cyan");

  while(rmw_uros_ping_agent(100, 10)){
    Serial.println("Pinging Agent...");
    blinkLED(1,150, "magenta");
  } 

  allocator = rcl_get_default_allocator();
  //const rosidl_message_type_support_t * TnsyControllerTypeSupport = ROSIDL_GET_MSG_TYPE_SUPPORT(tnsy_interfaces, msg, TnsyController);

  //create init_options
  RCCHECK(rclc_support_init(&support, 0, NULL, &allocator));
  // create node (&node, node name, namespace, &support)
  RCCHECK(rclc_node_init_default(&node, "ESP32Node", "", &support));
  // create subscriber with "reliable" qos. use rclc_subscription_init_best_effort() for "best effort"
  RCCHECK(rclc_subscription_init_best_effort(
    &subscriber,
    &node,
    ROSIDL_GET_MSG_TYPE_SUPPORT(tnsy_interfaces, msg, TnsyController),
    "nameSpace1/tnsy_controller"));
  /*/ create publisher
  RCCHECK(rclc_publisher_init_default(
    &publisher,
    &node,
    ROSIDL_GET_MSG_TYPE_SUPPORT(tnsy_interfaces, msg, TnsyController),
    "tnsy_status"));*/
  // create timer
  RCCHECK(rclc_timer_init_default(
    &timer,
    &support,
    RCL_MS_TO_NS(timer_timeout),
    timer_callback));
  // create executor (&executor, &support context, # of handles, &allocator)
  RCCHECK(rclc_executor_init(&executor, &support.context, 2, &allocator));
  RCCHECK(rclc_executor_add_timer(&executor, &timer));
  RCCHECK(rclc_executor_add_subscription(&executor, &subscriber, &tnsymsg, &subscription_callback, ON_NEW_DATA));
  



  blinkLED(5,50, "green");
  Serial.println("Spinning Executor");
  RCCHECK(rclc_executor_spin(&executor));
  
  RCCHECK(rcl_subscription_fini(&subscriber, &node));
  RCCHECK(rcl_timer_fini(&timer));
  RCCHECK(rcl_node_fini(&node));
}

void loop() {
  delay(1000);
}

void timer_callback(rcl_timer_t * timer, int64_t last_call_time){
  RCLC_UNUSED(last_call_time);
  //maybe move all the tsnymsg queries to the front to speed them up? (by assigning variables to them)
  uint16_t blinkColor = 0;

  if (timer) {
    // main timer area
    intensity = 5+(tnsymsg.weapon_speed * 250);

    if (tnsymsg.enable_switch){
      
      //neopixelWrite(14, intensity, 0, 0);// (g, r, b)
      
      // not sure if these sin & cos are correct
      motorSpeedOne = tnsymsg.translation_magnitude*maxSpeed;//(maxSpeed * tnsymsg.translation_magnitude)*cos(tnsymsg.translation_angle * M_PI / 180.0);
      motorSpeedTwo = tnsymsg.translation_magnitude*maxSpeed;//(maxSpeed * tnsymsg.translation_magnitude)*sin(tnsymsg.translation_angle * M_PI / 180.0);

      motorBigSpeedOne = (tnsymsg.weapon_speed * (maxWeaponSpeed-minWeaponSpeed))+minWeaponSpeed;
      motorBigSpeedTwo = motorBigSpeedOne;

      blinkColor = matrix.Color(0, 255, 0);

    }else{
      //neopixelWrite(14, 0, intensity, 0);// (g, r, b)
      motorSpeedOne = 0;
      motorSpeedTwo = 0;
      motorBigSpeedOne = minWeaponSpeed;
      motorBigSpeedTwo = minWeaponSpeed;
      blinkColor = matrix.Color(255, 0, 0);
    }

    driveSpeeds[0] = tnsymsg.translation_magnitude;
    driveSpeeds[1] = tnsymsg.translation_magnitude;
    weaponSpeeds[0] = motorBigSpeedOne;
    weaponSpeeds[1] = motorBigSpeedTwo;

    matrixUpdate(blinkColor, driveSpeeds, weaponSpeeds);
    //***Set motor speeds***//
    mc1.setSpeed(1, motorSpeedOne);
    mc2.setSpeed(1, motorSpeedTwo);
    updatePWM(motorBigSpeedOne, motorBigSpeedOne);
    
  }
}

void subscription_callback(const void * msgin){
  // This doesn't need to contain anything for ROS to update the message variable (defined elsewhere)
  // But I think it does need to exist
}

// error loop
void error_loop() {
  while(1){
    Serial.println("Error occurred, restarting...");
    blinkLED(3,250, "red");
    esp_restart();
  }
}


//===========================START OF CUSTOM FUNCTIONS========================================

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

void configurePWM(){
  // Set resolution
  int resolutionMultiplier = (int)(10000000 / pwmConfig.frequency); // Default resolution is 10,000,000
  int resolution = pwmConfig.frequency * resolutionMultiplier; // The resolution must be an integer multiple of the frequency
  mcpwm_group_set_resolution(pwmUnit0, resolution); // must be called before mcpwm_init()

  mcpwm_set_pin(pwmUnit0, &pwmPins); // initializes all GPIOs

  mcpwm_init(pwmUnit0, pwmTimer0, &pwmConfig);
}

void setupMotoron(){
  mc1.reinitialize();
  mc2.reinitialize();

  mc1.disableCrc();
  mc2.disableCrc();

  mc1.clearResetFlag();
  mc2.clearResetFlag();

  mc1.setMaxAcceleration(1,maxAcc);
  mc2.setMaxAcceleration(1,maxAcc);

  mc1.setMaxDeceleration(1,maxDec);
  mc2.setMaxDeceleration(1,maxDec);
}

void updatePWM(float motorA, float motorB){
  int dutyCycleA = (int)(motorA * 49) + 50;// AM32 0% power is 50% duty. Also it loses the signal if you go 100% duty cycle.
  int dutyCycleB = (int)(motorB * 49) + 50;
  mcpwm_set_duty(pwmUnit0, pwmTimer0, pwmGenA, dutyCycleA);
  mcpwm_set_duty(pwmUnit0, pwmTimer0, pwmGenB, dutyCycleB);
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

  blinkLED(2, 50, "blue");
  Serial.print("Connecting to WiFi");
  do {
    wifistatus = WiFi.status();

    // Check if the timeout has been reached
    if (millis() - start_time > timeout) {
      Serial.println("\nWi-Fi connection timed out. Restarting...");
      blinkLED(3,50, "red");
      esp_restart();
    }
    
    // Blink and wait to give the ESP32 time to connect
    if (wifistatus == oldwifistatus){
      Serial.print(".");
    } else {
      Serial.print("\n" + wifiStatusString(wifistatus));
    }

    blinkLED(1, 250, "blue"); 

    oldwifistatus = wifistatus;
  }while(wifistatus != WL_CONNECTED);

  Serial.println();
  blinkLED(3, 50, "green"); // Blink to indicate success
}