#!/usr/bin/env python3
import numpy as np
import rclpy
#import rclpy.exceptions
from rclpy.lifecycle import LifecycleNode
from sensor_msgs.msg import Joy
from tnsy_interfaces.msg._tnsy_controller import TnsyController

"""
LAST: dissolved the controller class into two funcitons of MyNode. Also implemented counters and trackers to enable a
delay-free toggle button
"""

class MyNode(LifecycleNode):
      def __init__(self):
            super().__init__("joy_translator_node")
            self.joyMsg = None
            self.timer_ = None
            self.sub_ = None
            self.pub_ = None
            self.timer_period = 0.05 # lower is faster
            self.counter = 0
            self.counterLimit = 0.5/self.timer_period # n seconds divided by timer period
            self.tracker = 0
            self.lastPush = 0
            self.lX, self.lY, self.rX, self.rY, self.throttle = 0.0, 0.0, 0.0, 0.0, 0.0
            self.enable = False
            self.pub_msg = TnsyController()
            #self.get_logger().info("IN constructor")
            
      def on_configure(self, state):
            #self.get_logger().info("IN on_configure")
            self.pub_ = self.create_lifecycle_publisher(TnsyController, 'tnsy_controller', 10)
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
            self.sub_ = self.create_subscription(Joy, 'joy', self.listener_callback, 10)
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

      def listener_callback(self, msg):
            self.joyMsg = msg
      
      def publisher(self, msg):
            self.pub_.publish(msg)

      def axesUpdate(self):
            """ xbox controller axes:
            0 = left x
            1 = left y
            2 = right x
            3 = right y
            4 = left trigger
            5 = right trigger
            """
            # =============Start of axes mapping==================
            self.lX = self.joyMsg.axes[0]
            self.lY = self.joyMsg.axes[1]
            self.rX = self.joyMsg.axes[2]
            self.rY = self.joyMsg.axes[3]
            self.throttle = abs(self.joyMsg.axes[5])

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
            # =============Start of button mapping==================
            
            button = self.joyMsg.buttons[6]
            if button == 1 and self.lastPush < self.tracker:
                  self.lastPush = self.tracker
                  if self.enable == True:
                        self.enable = False
                  elif self.enable == False:
                        self.enable = True

            self.pub_msg.enable_switch = self.enable
            # =============End of button mapping==================

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