#!/usr/bin/env python3
import numpy as np
import rclpy
#import rclpy.exceptions
from rclpy.lifecycle import LifecycleNode
from sensor_msgs.msg import Joy
from tnsy_interfaces.msg._tnsy_controller import TnsyController


class MyNode(LifecycleNode):
      def __init__(self):
            super().__init__("joy_translator_node")
            self.joyMsg = None
            self.timer_ = None
            self.sub_ = None
            self.pub_ = None
            self.timer_period = 0.001 # lower is faster (in Seconds)
            self.counter = 0
            self.counterLimit = 1/self.timer_period # n seconds divided by timer period sets the de-bounce time
            self.tracker = 0
            self.lX, self.lY, self.rX, self.rY, self.throttle = 0.0, 0.0, 0.0, 0.0, 0.0
            numberOfButtons = 7
            self.lastPush = [0] * numberOfButtons # this allows all buttons to be toggles if desired
            self.toggles = [False] * numberOfButtons 
            self.pub_msg = TnsyController()
            self.qosQueueSize = 1
            #self.get_logger().info("IN constructor")
            
      def on_configure(self, state):
            #self.get_logger().info("IN on_configure")
            #self.pub_ = self.create_publisher(TnsyController, 'tnsy_controller', 'Best effort')
            self.pub_ = self.create_lifecycle_publisher(TnsyController, 'tnsy_controller', self.qosQueueSize)
            self.timer_ = self.create_timer(self.timer_period, self.timerCallback)
            self.timer_.cancel()
            return super().on_configure(state)
      
      def on_cleanup(self, state):
            #self.get_logger().info("IN on_cleanup")
            self.destroy_publisher(self.pub_)
            self.destroy_timer(self.timer_)
            return super().on_cleanup(state)
      
      def on_activate(self, state):
            #self.get_logger().info("IN on_activate")
            self.sub_ = self.create_subscription(Joy, 'joy', self.subscriber_callback, 10)
            self.timer_.reset()
            # super() is used in order to activate lifecycle publishers
            return super().on_activate(state)
      
      def on_deactivate(self, state):
            #self.get_logger().info("IN on_deactivate")
            self.sub_ = self.destroy_subscription(self.sub_)
            self.timer_.cancel()
            # super() is used in order to deactiave lifecycle publishers
            return super().on_deactivate(state)
      
      def on_shutdown(self, state):
            #self.get_logger().info("IN on_shutdown")
            self.destroy_subscription(self.sub_)
            self.destroy_publisher(self.pub_)
            self.destroy_timer(self.timer_)
            return super().on_shutdown(state)
      
      def on_error(self, state):
            #self.get_logger().info("IN ON_ERROR")
            self.destroy_subscription(self.sub_)
            self.destroy_publisher(self.pub_)
            self.destroy_timer(self.timer_)
            return super().on_error(state)

      def timerCallback(self):
            self.counter += 1
            if self.joyMsg: # if the joyMsg contains information, update pub_msg
                  self.axesUpdate()
                  self.buttonUpdate()
                  self.publisher(self.pub_msg)
            else: # else return an empty message of type TnsyController
                  self.publisher(TnsyController())
            
            if self.counter >= self.counterLimit:
                  self.counter = 0
                  self.tracker += 1
            if self.tracker > (2**30):
                  self.tracker = 0
                  self.lastPush = 0

      def subscriber_callback(self, msg):
            self.joyMsg = msg
      
      def publisher(self, msg):
            self.pub_.publish(msg)

      def axesUpdate(self):
            # xbox controller axes:
            left_x = 0
            left_y = 1
            right_x = 2
            right_y = 3
            left_trigger = 4
            right_trigger = 5
            # =============Start of axes mapping==================
            self.lX = self.joyMsg.axes[left_x]
            self.lY = self.joyMsg.axes[left_y]
            self.rX = self.joyMsg.axes[right_x]
            self.rY = self.joyMsg.axes[right_y]
            self.weapon = abs(self.joyMsg.axes[left_trigger])
            self.throttle = abs(self.joyMsg.axes[right_trigger])

            leftMagnitude  = np.sqrt(self.lX**2 + self.lY**2)
            rightMagnitude = np.sqrt(self.rX**2 + self.rY**2)
            if leftMagnitude > 1.0:
                  leftMagnitude = 1.0
            if rightMagnitude > 1.0:
                  rightMagnitude = 1.0
            
            # Output angles are +/-180, with 0 at the up position of the joystick, and +90 to the left
            # if Magnitude is something other than 0, set the angle it's pointing. Otherwise assume it's 0deg
            if leftMagnitude:
                  leftAngle = np.rad2deg(np.arctan2(self.lX, self.lY))
            else:
                  leftAngle  = 0.0
            if rightMagnitude:
                  rightAngle = np.rad2deg(np.arctan2(self.rX, self.rY))
            else:
                  rightAngle = 0.0

            self.pub_msg.weapon_speed = self.weapon
            self.pub_msg.translation_magnitude = self.throttle*leftMagnitude
            self.pub_msg.translation_angle = leftAngle
            self.pub_msg.pointing_magnitude = rightMagnitude
            self.pub_msg.pointing_angle = rightAngle
            self.pub_msg.rotation_speed = self.rX
            # =============End of axes mapping==================            
                  
      def buttonUpdate(self):
            """ xbox controller buttons
            0 = A
            1 = B
            2 = X
            3 = Y
            4 = Pizza box
            5 = ?
            6 = Hamburger
            """
            A_button = 0
            B_button = 1
            X_button = 2
            Y_button = 3
            pizzaBox_button = 4
            hamburger_button = 6
            
            # =============Start of button mapping==================
            # Momentary buttons
            self.pub_msg.button_one = bool(self.joyMsg.buttons[A_button])
            # Toggle Buttons
            self.pub_msg.button_two = self.toggleButton(B_button)
            self.pub_msg.button_three = self.toggleButton(X_button)
            self.pub_msg.button_four = self.toggleButton(Y_button)
            self.pub_msg.enable_switch = self.toggleButton(hamburger_button)
            # =============End of button mapping==================

      def toggleButton(self, button):
            if self.joyMsg.buttons[button] == 1 and self.lastPush[button] < self.tracker:
                  self.lastPush[button] = self.tracker
                  if self.toggles[button] == True:
                        self.toggles[button] = False
                  elif self.toggles[button] == False:
                        self.toggles[button] = True

            return self.toggles[button]

def main(args=None):
      # everything between init and shutdown is the node
      rclpy.init(args=args)
      node = MyNode()

      try:
            rclpy.spin(node)
            node.destroy_node()
            rclpy.shutdown()
      except (KeyboardInterrupt): # this try:except catches the user using ctl-c to stop the node from running
            pass      


if __name__ == '__main__':
      main()