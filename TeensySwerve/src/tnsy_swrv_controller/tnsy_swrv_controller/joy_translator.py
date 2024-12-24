#!/usr/bin/env python3
import numpy as np
import rclpy
import rclpy.exceptions
from rclpy.lifecycle import LifecycleNode
from sensor_msgs.msg import Joy

"""
I don't think I'm going to figure out how to cleaning shutdown the node after a keyboard interrupt while also using python... :(
"""

class MyNode(LifecycleNode):
      def __init__(self):
            super().__init__("joy_translator_node")
            self.joyMsg = None
            self.timer_ = None
            self.sub_ = None
            #self.get_logger().info("IN constructor")
            
      def on_configure(self, state):
            #self.get_logger().info("IN on_configure")
            self.timer_ = self.create_timer(3, self.timerCallback)
            self.timer_.cancel()
            return super().on_configure(state)
      
      def on_cleanup(self, state):
            #self.get_logger().info("IN on_cleanup")
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
            self.destroy_timer(self.timer_)
            return super().on_shutdown(state)
      
      def on_error(self, state):
            #self.get_logger().info("IN ON_ERROR")
            self.destroy_subscription(self.sub_)
            self.destroy_timer(self.timer_)
            return super().on_error(state)

      def timerCallback(self):
            lX, lY, rX, rY = 0.0, 0.0, 0.0, 0.0
            if self.joyMsg:
                  lX = self.joyMsg.axes[0]
                  lY = self.joyMsg.axes[1]
                  rX = self.joyMsg.axes[2]
                  rY = self.joyMsg.axes[3]

                  leftrho = np.sqrt(lX**2 + lY**2)
                  leftphi = np.rad2deg(np.arctan2(lY, lX))
                  rightrho = np.sqrt(rX**2 + rY**2)
                  rightphi = np.rad2deg(np.arctan2(rY, rX))

                  self.get_logger().info("| LR:%.2f LP:%.2f | RR:%.2f RP:%.2f |" %(leftrho,leftphi,rightrho,rightphi))

      def listener_callback(self, msg):
            self.joyMsg = msg
            

def main(args=None):
      # evevrything between init and shutdown is the node
      rclpy.init(args=args)

      node = MyNode()
      rclpy.spin(node)
      node.destroy_node()
      rclpy.shutdown()
      


if __name__ == '__main__':
      main()