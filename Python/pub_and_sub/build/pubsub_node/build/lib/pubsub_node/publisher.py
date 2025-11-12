import rclpy
from rclpy.node import Node
# Gọi message ta vừa tạo
from intnums.msg import NameIntNumData

class PublisherMsg(Node):
    def __init__(self):
        super().__init__('publisher_msg')
        # Tạo publisher với topic tên là : send_int
        self.publisher_ = self.create_publisher(
            NameIntNumData, # Loại dữ liệu
            'send_int', #Tên đặt cho topic
            10
        )
        self.timer = self.create_timer(0.5,self.publish_nums) # Tạo timer ( 2Hz)
        self.get_logger().info("This node is started")

    # Tạo hàm để publish 
    def publish_nums(self):
        # Tạo message để xuất bản
        msg = NameIntNumData()
        # Truyền dữ liệu cho message. Lưu ý gọi đúng tên được cấp trong file .msg
        msg.name = "I'm publishing !"
        msg.int_num_data.num_a = 1
        msg.int_num_data.num_b = 2

        # Gửi xuất bản
        self.publisher_.publish(msg)
        self.get_logger().info(f'publishing : name {msg.name} | number a: {msg.int_num_data.num_a} | number b : {msg.int_num_data.num_b}')
    
def main(args=None):
    rclpy.init(args=args)
    node = PublisherMsg()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        node.get_logger().info("Node stopped by user")
    finally:
        node.destroy_node()
        rclpy.shutdown()
if __name__ =="__main__":
    main()


