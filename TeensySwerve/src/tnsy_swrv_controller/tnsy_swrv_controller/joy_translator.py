#!/usr/bin/env python3
import rclpy
from rclpy.lifecycle import State, LifecycleNode, LifecycleState, TransitionCallbackReturn
from sensor_msgs.msg import Joy

"""
Got lifecycle node setup properly. dunno why there's a lifecycle publisher but no lifecycle subscriber
Next steps are to see about on_error and if that can handle ctrl-C
"""

class MyNode(LifecycleNode):
      def __init__(self):
            super().__init__("joy_translator_node")
            self.joyMsg = None
            self.timer_0 = None
            self.timer_1 = None
            self.sub_ = None
            self.get_logger().info("IN constructor")
            
      def on_configure(self, state):
            self.get_logger().info("IN on_configure")
            self.timer_0 = self.create_timer(0.1, self.timer0Callback)
            self.timer_1 = self.create_timer(1, self.timer1Callback)
            self.timer_0.cancel()
            self.timer_1.cancel()
            return super().on_configure(state)
      
      def on_cleanup(self, state):
            self.get_logger().info("IN on_cleanup")
            self.destroy_subscription(self.sub_)
            self.destroy_timer(self.timer_0)
            self.destroy_timer(self.timer_1)
            return super().on_cleanup(state)
      
      def on_activate(self, state):
            self.get_logger().info("IN on_active")
            self.sub_ = self.create_subscription(Joy, 'joy', self.listener_callback, 10)
            self.timer_1.reset()
            self.timer_0.reset()
            # super() is used in order to activate lycycle subs/pubs
            return super().on_activate(state)
      
      def on_deactivate(self, state):
            self.get_logger().info("IN on_deactivate")
            self.sub_ = self.destroy_subscription(self.sub_)
            self.timer_1.cancel()
            self.timer_0.cancel()
            # super() is used in order to deactiave lycycle subs/pubs
            return super().on_deactivate(state)
      
      def on_shutdown(self, state):
            self.get_logger().info("IN on_shutdown")
            self.sub_ = self.destroy_subscription(self.sub_)
            self.destroy_timer(self.timer_0)
            self.destroy_timer(self.timer_1)
            return super().on_shutdown(state)
      
      def timer1Callback(self):
            if self.joyMsg:
                  self.get_logger().info(str(self.joyMsg.buttons))

      def timer0Callback(self):
            lX, lY, rX, rY = 0.0, 0.0, 0.0, 0.0
            if self.joyMsg:
                  lX = self.joyMsg.axes[0]
                  lY = self.joyMsg.axes[1]
                  rX = self.joyMsg.axes[2]
                  rY = self.joyMsg.axes[3]
                  self.get_logger().info("Left X: %.2f Left Y: %.2f Right X: %.2f Right Y: %.2f" %(lX, lY, rX, rY))
                  #self.get_logger().info("%.2f" %(lX))

      
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