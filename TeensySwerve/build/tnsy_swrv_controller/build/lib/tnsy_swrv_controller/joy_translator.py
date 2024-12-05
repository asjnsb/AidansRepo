#!/usr/bin/env python3
import rclpy
from rclpy.node import Node

class MyNode(Node):
      def __init__(self):
            super().__init__("joy_translator_node")
            self.counter_ = 0
            self.create_timer(1.0, self.timerCallback)
      
      def timerCallback(self):
            self.get_logger().info("Meowdy " + str(self.counter_))
            self.counter_ += 1

def main(args=None):
      # evevrything between init and shutdown is the node
      rclpy.init(args=args)

      node = MyNode()
      rclpy.spin(node) 
      
      rclpy.shutdown()


if __name__ == '__main__':
      main()