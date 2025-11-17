import rclpy
from rclpy.node import Node
from std_msgs.msg import String
import serial
import threading
import sys
class SerialDebugNode(Node):
    def __init__(self,port,topic,baudrate):
        super().__init__('serial_debug_node')

        self.port = port
        self.baudrate = baudrate
        # Open serial
        try:
            self.ser_ = serial.Serial(self.port,self.baudrate,timeout=0.1)
        except Exception as e:
            self.get_logger().error(f'Cannot open serial: {self.port}: {e}')
            exit(1)

        # Publisher
        self.pub_ = self.create_publisher(
            String, #type message
            topic,
            10
        )

        thread = threading.Thread(target=self.read_serial)
        thread.daemon = True
        thread.start()

    def read_serial(self):
        while True:
            if self.ser_.in_waiting:
                try:
                    line = self.ser_.readline().decode('utf-8',errors='ignore').strip()
                    if line:
                        msg = String()
                        msg.data = line
                        self.pub_.publish(msg)
                        self.get_logger().info(f'Published : {msg.data}')
                except Exception as e:
                    self.get_logger().error(f'serial read error: {e}')

def main(args=None):
    rclpy.init(args=args)
    if len(sys.argv) < 4:
        print("Usage: ros2 run serial_log serial_debug_node <serial_port> <topic_name> <baudrate>")
        exit(1)
    
    port = sys.argv[1]
    topic = sys.argv[2]
    try:
        baudrate = int(sys.argv[3])
    except ValueError as e:
        print(f'baudrate wrong: {e}')
        exit(1)
    node = SerialDebugNode(port,topic,baudrate)

    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        node.get_logger().info("This node has been stopped by user !")
    finally:
        node.ser_.close()
        node.destroy_node()
        rclpy.shutdown()

if __name__ == "__main__":
    main()

        
