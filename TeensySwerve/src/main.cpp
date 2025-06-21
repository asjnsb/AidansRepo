#include <Arduino.h>
#include <Wire.h>
#include <Motoron.h>
#include <micro_ros_platformio.h>
#include <rcl/rcl.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>
#include <std_msgs/msg/float32.h>
#include <tnsy_interfaces/msg/tnsy_controller.h>

//LAST: it wasn't publishing things because I needed to tell the executor that there are two handles


std_msgs__msg__Float32 floatmsg;
tnsy_interfaces__msg__TnsyController tnsymsg;
rcl_publisher_t publisher;
rcl_subscription_t subscriber;
rclc_executor_t executor;
rclc_support_t support;
rcl_allocator_t allocator;
rcl_node_t node;
rcl_timer_t timer;
MotoronI2C mc;

// Function for easy error handling when initialzing things
#define RCCHECK(fn) { rcl_ret_t temp_rc = fn; if((temp_rc != RCL_RET_OK)){error_loop();}}
// Same function but doesn't call the error loop
#define RCSOFTCHECK(fn) { rcl_ret_t temp_rc = fn; if((temp_rc != RCL_RET_OK)){}}

// error loop
void error_loop() {
  // if error occurs, loop forever?
  // is there a function to soft reset the board?
  while(1){
    delay(100);
  }
}

void timer_callback(rcl_timer_t * timer, int64_t last_call_time){
  RCLC_UNUSED(last_call_time);
  if (timer != NULL) {
    // the message must match the message type of the publisher
    floatmsg.data = tnsymsg.translation_magnitude;
    RCSOFTCHECK(rcl_publish(&publisher, &floatmsg, NULL));
    
    if (millis() & 2048){
      mc.setSpeed(1,800);
      mc.setSpeed(2,800);
    }else{
      mc.setSpeed(1,-800);
      mc.setSpeed(2,-800);
    }
  }
}

void subscription_callback(const void * msgin){
	const tnsy_interfaces__msg__TnsyController * msg_tnsy =
   (const tnsy_interfaces__msg__TnsyController *)msgin;
  tnsymsg = *msg_tnsy; // copy the message to the global variable tnsymsg
}

void setup(){
  //i2c setup
  Wire.begin();

  //motoron setup
  mc.reinitialize();
  mc.disableCrc();
  mc.clearResetFlag();
  mc.setMaxAcceleration(1,150);
  mc.setMaxDeceleration(1,300);
  mc.setMaxAcceleration(2,150);
  mc.setMaxDeceleration(2,300);

  // Configure serial transport
  Serial.begin(115200);
  set_microros_serial_transports(Serial);

  delay(100);

  allocator = rcl_get_default_allocator();

  //create init_options
  RCCHECK(rclc_support_init(&support, 0, NULL, &allocator));

  // create node (&node, node name, namespace, &support)
  RCCHECK(rclc_node_init_default(&node, "InputNode", "", &support));

  // create publisher (&publisher, &node, typesupport, topic name)
  RCCHECK(rclc_publisher_init_default(
    &publisher,
    &node,
    ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Float32),
    "/esp32_pub"));

  // create subscriber with "reliable" qos. use rclc_subscription_init_best_effort() for "best effort"
  RCCHECK(rclc_subscription_init_default(
    &subscriber,
    &node,
    ROSIDL_GET_MSG_TYPE_SUPPORT(tnsy_interfaces, msg, TnsyController),
    "nameSpace1/tnsy_controller"));

  // create timer
  const unsigned int timer_timeout = 500;
  RCCHECK(rclc_timer_init_default(
    &timer,
    &support,
    RCL_MS_TO_NS(timer_timeout),
    timer_callback));
  
  // create executor
  RCCHECK(rclc_executor_init(&executor, &support.context, 2, &allocator));
  RCCHECK(rclc_executor_add_timer(&executor, &timer));
  RCCHECK(rclc_executor_add_subscription(&executor, &subscriber, &floatmsg, subscription_callback, ON_NEW_DATA))
  
  floatmsg.data = 0.0;

  RCSOFTCHECK(rclc_executor_spin(&executor));
  
  RCCHECK(rcl_subscription_fini(&subscriber, &node));
  RCCHECK(rcl_publisher_fini(&publisher, &node));
  RCCHECK(rcl_timer_fini(&timer));
  RCCHECK(rcl_node_fini(&node));
}

void loop() {
  delay(10000);
  // maybe add stuff here to check if the controller is connected to ROS
}