import rclpy
from rclpy.node import Node

class MinimalParam(Node):
    def __init__(self):
        # Đặt tên node
        super().__init__("minimal_param_node")

        self.declare_parameter(
            'my_parameter', # Đặt tên cho param
            'world' # Giá trị của nó
            ) 
        # Tạo timer để callback
        self.timer = self.create_timer(1,self.param_callback)
    # Hàm callback
    def param_callback(self):
        # Lấy giá trị của param 
        my_param = self.get_parameter('my_parameter').get_parameter_value().string_value
        self.get_logger().info(f'Hello {my_param}')

def main(args=None):
    rclpy.init(args=args)
    node = MinimalParam()
    rclpy.spin(node)

if __name__ == "__main__":
    main()