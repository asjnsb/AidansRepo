#!/usr/bin/env python3
import rclpy
from rclpy.node import Node

class MyNode(Node):
      def __init__(self):
            super().__init__("first_node")
            self.counter_ = 0
            self.create_timer(1.0, self.timerCallback)
      def timerCallback(self):
            self.get_logger().info("Meowdy " + str(self.counter_))
            self.counter_ += 1

def main(args=None):
      # evevrything between init and shutdown is the node
      # init and shutdown are referring to ROS2 communication protocols
      rclpy.init(args=args)
      # below is what is actually creating the node
      node = MyNode()
      rclpy.spin(node) # making it spin keeps the node alive until it's killed (and enables callbacks to work)
      rclpy.shutdown()

# This is for running the script directly from the terminal
if __name__ == '__main__':
      main()