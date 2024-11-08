#include <Arduino.h>
#include <micro_ros_platformio.h>
#include <micro_ros_utilities/string_utilities.h>

#include <rcl/rcl.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>

#include <std_msgs/msg/string.h>

rcl_publisher_t publisher;
std_msgs__msg__String msg;
//delete this comment
rclc_executor_t executor;
rclc_support_t support;
rcl_allocator_t allocator;
rcl_node_t node;
rcl_timer_t timer;

// Function for easy error handling when initialzing things
#define RCCHECK(fn) { rcl_ret_t temp_rc = fn; if((temp_rc != RCL_RET_OK)){error_loop();}}
// Same function but doesn't call the error loop
#define RCSOFTCHECK(fn) { rcl_ret_t temp_rc = fn; if((temp_rc != RCL_RET_OK)){}}

// error loop
void error_loop() {
  // if error occurs, loop forever?
  while(1){
    delay(100);
  }
}

int counter = 0;

void timer_callback(rcl_timer_t * timer, int64_t last_call_time){
  RCLC_UNUSED(last_call_time);
  if (timer != NULL) {
    // the message must match the message type of the publisher
    sprintf(msg.data.data, "Look at me! #%d", counter++);
    msg.data.size = strlen(msg.data.data);
    RCSOFTCHECK(rcl_publish(&publisher, &msg, NULL));
  }
}

void setup(){
  // Configure serial transport
  Serial.begin(115200);
  set_microros_serial_transports(Serial);
  delay(2000);

  allocator = rcl_get_default_allocator();

  //create init_options
  RCCHECK(rclc_support_init(&support, 0, NULL, &allocator));

  // create node
  RCCHECK(rclc_node_init_default(&node, "Aidans_node", "", &support));

  // create publisher
  RCCHECK(rclc_publisher_init_default(
    &publisher,
    &node,
    ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, String),
    "/Aidans_node_publisher"));
  
  // create timer
  const unsigned int timer_timeout = 5000;
  RCCHECK(rclc_timer_init_default(
    &timer,
    &support,
    RCL_MS_TO_NS(timer_timeout),
    timer_callback));
  
  // create executor
  RCCHECK(rclc_executor_init(&executor, &support.context, 1, &allocator));
  RCCHECK(rclc_executor_add_timer(&executor, &timer));

  //Fill the array with a known (nothing?) sequence
  msg.data.data = (char * ) malloc(200 * sizeof(char));
  msg.data.size = 0;
  msg.data.capacity = 200;
  RCSOFTCHECK(rclc_executor_spin(&executor));
}

void loop() {
  delay(100000);
  //RCSOFTCHECK(rclc_executor_spin_some(&executor, RCL_MS_TO_NS(1000)));
}