import rclpy
from rclpy.node import Node
from std_msgs.msg import String
import serial

class LedController(Node):
    def __init__(self):
        super().__init__('ledc_controller_node')
        # Cổng Serial Arduino
        self.ser = serial.Serial('/dev/ttyUSB0', 9600)
        # Subscriber để nhận lệnh từ topic 'led_control'
        self.subscription = self.create_subscription(
            String,
            'led_control',
            self.callback,
            10
        )

    def callback(self, msg):
        # Gửi lệnh tới Arduino qua Serial
        self.ser.write((msg.data + "\n").encode())
        self.get_logger().info(f"Sent to Arduino: {msg.data}")

def main(args=None):
    rclpy.init(args=args)
    node = LedController()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.ser.close() 
        node.destroy_node()
        rclpy.shutdown()

if __name__ == '__main__':
    main()
