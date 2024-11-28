#!/usr/bin/env python3
import rclpy
from rclpy.node import Node

class MyNode(Node):
        def __init__(self):
            super().__init__("first_node")
            self.get_logger().info("Hello from ROS2")

def main(args=None):
      # evevrything between init and shutdown is the node
      # init and shutdown are referring to ROS2 communication protocols
      rclpy.init(args=args)
      # below is what is actually creating the node
      node = MyNode()
      #rclpy.spin(node) # making it spin keeps the node alive until it's killed (so callbacks still work)
      rclpy.shutdown()

if __name__ == '__main__':
      main()