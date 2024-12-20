#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Joy


class MyNode(Node):
      def __init__(self):
            super().__init__("joy_translator_node")
            self.joyMsg = Joy
            self.create_timer(0.1, self.timerCallback)
            self.create_timer(1, self.loggerCallback)
            self.create_subscription(Joy, 'joy', self.listener_callback, 10)
            self.get_logger().info("Joy Translator Init Complete")
      
      def loggerCallback(self):
            self.get_logger().info(str(self.joyMsg.buttons))

      def timerCallback(self):
            lX = self.joyMsg.axes[0]
            lY = self.joyMsg.axes[1]
            rX = self.joyMsg.axes[2]
            rY = self.joyMsg.axes[3]
            #self.get_logger().info("Left X: %.2f Left Y: %.2f Right X: %.2f Right Y: %.2f" %(lX, lY, rX, rY))
            self.get_logger().info("%.2f" %(lX))
      
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