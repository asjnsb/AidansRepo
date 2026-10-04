#include <WiFi.h>
#include <Arduino.h>
#include <Motoron.h>
#include <rcl/rcl.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>
#include <micro_ros_platformio.h>
#include <my_cpp_functions/myFunctions.h>
#include <tnsy_interfaces/msg/tnsy_controller.h>


//LAST: code is updated to run off of state machines. safety timer implemented. motors sometimes twitch on restart...
//NEXT: look into improving wifi performance via channels?
//ALSO: Maybe just use "drive" and "weapon" insteal of "motor" and "motorBig" and use left & right and front & back (fore aft?) instead of 1 & 2
//AND : 

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
rcl_timer_t timertranslator;
rcl_timer_t timerManager;
MotoronI2C mc1(15);// Set mc1 to i2c channel 15
MotoronI2C mc2(16);

// User vars
const int maxSpeed = 800;
int maxAcc = 500;
int maxDec = 1000;
const float maxWeaponSpeed = 1; // on a scale of 0.0 to 1.0
const float minWeaponSpeed = 0; 
int timer_timeout_translator = 10; // in milliseconds, how frequent the timer callback is 
int timer_timeout_manager = 50; // in milliseconds, how frequent the timer callback is 
unsigned int lastCommTime = 0; // update this every time a communication packet comes through
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
enum manager_state {
  STARTUP_MAN,
  ACTIVE_MAN,
  SHUTDOWN_MAN
};
manager_state managerState = STARTUP_MAN;
enum translator_state {
  STARTUP_TRANS,
  SAFE_TRANS,
  IDLE_TRANS,
  LIVE_TRANS,
  SHUTDOWN_TRANS
};
translator_state translatorState = STARTUP_TRANS;

// Function Declarations
// Function for easy error handling when initialzing things
#define RCCHECK(fn) { rcl_ret_t temp_rc = fn; if((temp_rc != RCL_RET_OK)){error_loop();}}
// Same function but doesn't call the error loop
#define RCSOFTCHECK(fn) { rcl_ret_t temp_rc = fn; if((temp_rc != RCL_RET_OK)){}}
void timer_translator(rcl_timer_t * timertranslator, int64_t last_call_time_translator);
void timer_manager(rcl_timer_t * timerManager, int64_t last_call_time_manager);
void subscription_callback(const void * msgin);
void error_loop();
void configure_pwm();
void setup_motoron();
void update_pwm(float motorA, float motorB);
void rclcBegin();


void setup(){
  Serial.begin(115200);
  matrixInit(0.05);
  Wire.begin(I2C_SDA, I2C_SCL); // begin i2c
  configure_pwm();
  setup_motoron();
  
  blinkLED(1,150, "white");
  Serial.println("Hello Tnsy World");
  
  WiFiconnect(ssid, password);

  rclcBegin();
}

void loop() {
  // don't do anything with this arduino hardware loop, manage all execution with micro ROS
  delay(1000);
}

void timer_manager(rcl_timer_t * timer, int64_t last_call_time){
  RCLC_UNUSED(last_call_time);
  unsigned int loopTime = millis(); 
  if (timer) {
    uint16_t blinkColor = matrix.Color(255, 255, 255);
    unsigned long blinkPeriod = 500;
    unsigned int commGap = loopTime - lastCommTime;
    if (commGap > 3000) { // restart robot if the communication gap is larger than 3 seconds
      translatorState = SHUTDOWN_TRANS;
      managerState = SHUTDOWN_MAN;
    }

    switch (managerState) {
      case STARTUP_MAN:
        managerState = ACTIVE_MAN;
        Serial.print("STm.");
        break;
      case ACTIVE_MAN:
        // Handle active state
        blinkColor = matrix.Color(255, 125, 0);
        switch (translatorState){
          case STARTUP_TRANS:
            translatorState = SAFE_TRANS;
            break;
          case SAFE_TRANS:
            if (tnsymsg.enable_switch) translatorState = LIVE_TRANS;
            blinkPeriod = 1000;
            break;
          case LIVE_TRANS:
            if (!tnsymsg.enable_switch) translatorState = SAFE_TRANS;
            blinkPeriod = 250;
            break;
          case IDLE_TRANS:
            if (commGap < 500){
              if (tnsymsg.enable_switch){ translatorState = LIVE_TRANS;
              } else translatorState = SAFE_TRANS;
            }
            break;
        }// end of translator handling switch case
        driveSpeeds[0] = tnsymsg.translation_magnitude;
        driveSpeeds[1] = tnsymsg.translation_magnitude;
        weaponSpeeds[0] = motorBigSpeedOne;
        weaponSpeeds[1] = motorBigSpeedTwo;
        if (commGap >= 500) {
          translatorState = IDLE_TRANS;
          blinkColor = matrix.Color(255, 0, 0);
        }
        else if (commGap >= 100){
          blinkColor = matrix.Color(255, 0, 255);
          blinkPeriod = 0;
          Serial.print("?");
        }
        else{ 
          Serial.print("!");
        }
        break;
      case SHUTDOWN_MAN:
        Serial.println("Communication timeout reached");
        error_loop();
        break;
    }// end of manager state machine switch case
    matrixUpdate(driveSpeeds, weaponSpeeds, blinkColor, blinkPeriod);
  }
}

void timer_translator(rcl_timer_t * timer, int64_t last_call_time){
  RCLC_UNUSED(last_call_time);
  if (timer) {
    switch (translatorState) {
      case STARTUP_TRANS:    
        //***Set motor speeds***//
        mc1.setSpeed(1, 0);
        mc2.setSpeed(1, 0);
        update_pwm(minWeaponSpeed, minWeaponSpeed);
        Serial.print("STt.");
        break;

      case SAFE_TRANS:
        //***Set motor speeds***//
        mc1.setSpeed(1, motorSpeedOne);
        mc2.setSpeed(1, motorSpeedTwo);
        motorBigSpeedOne = minWeaponSpeed;
        motorBigSpeedTwo = minWeaponSpeed;
        update_pwm(minWeaponSpeed, minWeaponSpeed);
        Serial.print("-");
        break;

      case LIVE_TRANS:
        // Handle error state
        intensity = 5+(tnsymsg.weapon_speed * 250);
        // not sure if these sin & cos are correct
        motorSpeedOne = tnsymsg.translation_magnitude*maxSpeed;//(maxSpeed * tnsymsg.translation_magnitude)*cos(tnsymsg.translation_angle * M_PI / 180.0);
        motorSpeedTwo = tnsymsg.translation_magnitude*maxSpeed;//(maxSpeed * tnsymsg.translation_magnitude)*sin(tnsymsg.translation_angle * M_PI / 180.0);
        motorBigSpeedOne = (tnsymsg.weapon_speed * (maxWeaponSpeed-minWeaponSpeed))+minWeaponSpeed;
        motorBigSpeedTwo = motorBigSpeedOne;
        //***Set motor speeds***//
        mc1.setSpeed(1, motorSpeedOne);
        mc2.setSpeed(1, motorSpeedTwo);
        update_pwm(motorBigSpeedOne, motorBigSpeedTwo);
        Serial.print("_");
        break;

      case IDLE_TRANS:
        // stop drive but keep the weapon spun up
        mc1.setSpeed(1, 0);
        mc2.setSpeed(1, 0);
        update_pwm(motorBigSpeedOne, motorBigSpeedTwo);
        Serial.print(".");
        break;
      
      case SHUTDOWN_TRANS:
        update_pwm(minWeaponSpeed, minWeaponSpeed);
        mc1.setSpeed(1, 0);
        mc2.setSpeed(1, 0);
        break;
      }
    } 
    
    // main timer area
    
}

void subscription_callback(const void * msgin){
  // This doesn't need to contain anything for ROS to update the message variable (defined elsewhere)
  // But I think it does need to exist
  lastCommTime = millis(); // keeps track of when the last comm came through
}

// error loop
void error_loop() {
  while(1){
    Serial.println("Restarting...");
    blinkLED(5,50, "red");
    esp_restart();
  }
}


void configure_pwm(){
  // Set resolution
  int resolutionMultiplier = (int)(10000000 / pwmConfig.frequency); // Default resolution is 10,000,000
  int resolution = pwmConfig.frequency * resolutionMultiplier; // The resolution must be an integer multiple of the frequency
  mcpwm_group_set_resolution(pwmUnit0, resolution); // must be called before mcpwm_init()

  mcpwm_set_pin(pwmUnit0, &pwmPins); // initializes all GPIOs

  mcpwm_init(pwmUnit0, pwmTimer0, &pwmConfig);
  update_pwm(minWeaponSpeed, minWeaponSpeed);
}

void setup_motoron(){
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

void update_pwm(float motorA, float motorB){
  int dutyCycleA = (int)(motorA * 49) + 50;// AM32 0% power is 50% duty. Also it loses the signal if you go 100% duty cycle.
  int dutyCycleB = (int)(motorB * 49) + 50;
  mcpwm_set_duty(pwmUnit0, pwmTimer0, pwmGenA, dutyCycleA);
  mcpwm_set_duty(pwmUnit0, pwmTimer0, pwmGenB, dutyCycleB);
}

void rclcBegin(){
  RCSOFTCHECK(rcl_subscription_fini(&subscriber, &node));
  RCSOFTCHECK(rcl_timer_fini(&timertranslator));
  RCSOFTCHECK(rcl_timer_fini(&timerManager));
  RCSOFTCHECK(rcl_node_fini(&node));

  set_microros_wifi_transports(ssid, password, agent_ip, agent_port);
  blinkLED(1,150, "magenta");
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
  // create timers
  RCCHECK(rclc_timer_init_default(
    &timertranslator,
    &support, 
    RCL_MS_TO_NS(timer_timeout_translator),
    timer_translator));
  RCCHECK(rclc_timer_init_default(
    &timerManager,
    &support,
    RCL_MS_TO_NS(timer_timeout_manager),
    timer_manager));
  // create executor (&executor, &support context, # of handles, &allocator)
  RCCHECK(rclc_executor_init(&executor, &support.context, 3, &allocator));
  RCCHECK(rclc_executor_add_timer(&executor, &timertranslator));
  RCCHECK(rclc_executor_add_timer(&executor, &timerManager));
  RCCHECK(rclc_executor_add_subscription(&executor, &subscriber, &tnsymsg, &subscription_callback, ON_NEW_DATA));

  blinkLED(1,150, "green");

  lastCommTime = millis();
  Serial.println("Spinning Executor");
  RCCHECK(rclc_executor_spin(&executor));
  
  RCCHECK(rcl_subscription_fini(&subscriber, &node));
  RCCHECK(rcl_timer_fini(&timertranslator));
  RCCHECK(rcl_timer_fini(&timerManager));
  RCCHECK(rcl_node_fini(&node));
}