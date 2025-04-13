#!/usr/bin/env python3
import numpy as np
import rclpy
import rclpy.exceptions
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
            self.timer_period = 0.25
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
            lX, lY, rX, rY, throttle, translationSpeed = 0.0, 0.0, 0.0, 0.0, 0.0, 0.0
            pub_msg = TnsyController()
            if self.joyMsg:
                  """ xbox controller axes:
                  0 = left x
                  1 = left y
                  2 = right x
                  3 = right y
                  4 = left trigger
                  5 = right trigger
                  """
                  lX = self.joyMsg.axes[0]
                  lY = self.joyMsg.axes[1]
                  rX = self.joyMsg.axes[2]
                  rY = self.joyMsg.axes[3]
                  throttle = abs(self.joyMsg.axes[5])

                  leftMagnitude  = np.sqrt(lX**2 + lY**2)
                  rightMagnitude = np.sqrt(rX**2 + rY**2)
                  if leftMagnitude > 1.0:
                        leftMagnitude = 1.0
                  if rightMagnitude > 1.0:
                        rightMagnitude = 1.0

                  pub_msg.translation_magnitude = throttle*leftMagnitude
                  
                  # Output angles are +/-180, with 0 at the up position of the joystick
                  leftAngle  = np.rad2deg(np.arctan2(lX, lY))
                  rightAngle = np.rad2deg(np.arctan2(rX, rY))

                  self.get_logger().info("| LMag:%.2f LAng:%.2f | Throttle:%.2f |" %(leftMagnitude,leftAngle, throttle))
            self.publisher(translationSpeed)

      def listener_callback(self, msg):
            self.joyMsg = msg
      
      def publisher(self, msg):
            self.pub_.publish(msg)


def main(args=None):
      # everything between init and shutdown is the node
      rclpy.init(args=args)
      node = MyNode()

      try:
            rclpy.spin(node)
            node.destroy_node()
            rclpy.shutdown()
      except (KeyboardInterrupt):
            pass      


if __name__ == '__main__':
      main()