import rclpy
from rclpy.node import Node
# Nguồn nhận msg
from intnums.msg import NameIntNumData

class SubcriberMsg(Node):
    def __init__(self):
        super().__init__("subcriber_msg")
        #Nhận dữ liệu phải đúng topic
        self.subscription_ = self.create_subscription(
            NameIntNumData, #Loại dữ liệu
            'send_int', # Tên topic
            self.listener_callback, #Gọi call back
            10, # Hàng đợi
        )
        self.get_logger().info("This subcriber is started")

    # Tạo hàm callback
    def listener_callback(self,msg):
        name = msg.name
        num_a = msg.int_num_data.num_a
        num_b = msg.int_num_data.num_b

        self.get_logger().info(f'name: {name} | num_a = {num_a} | num_b = {num_b}')
def main(args=None):
    rclpy.init(args=args)
    node = SubcriberMsg()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        node.get_logger().info("This node is stopped by User !")
    finally:
        node.destroy_node()
        rclpy.shutdown()
