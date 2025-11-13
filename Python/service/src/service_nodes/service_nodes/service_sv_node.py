import rclpy
from rclpy.node import Node
# Gọi service vừa tạo ra
from add_two_ints.srv import SumTwoNums

class SrvServerNode(Node):
    def __init__(self):
        # Khởi tạo tên node, ở đây là tên service
        super().__init__('srv_server_node')

        # Tạo ra một service mới
        self.srv = self.create_service(
            SumTwoNums, #Loại service
            'sum_to_nums', # Đặt tên cho nó
            self.sum_to_nums_callback, # Gọi hàm callback
        )
    # Tạo callback

    def sum_to_nums_callback(self,request,response):
        # Xử lý callback:
        # - Nhận dữ liệu đầu vào là :  request.a và request.b
        # - Xử lý dữ liệu và phản hồi : response.sum
        response.sum = request.a + request.b

        #Debug dữ liệu
        self.get_logger().info(f'Request: {request.a} || {request.b} => Response: {response.sum}')

        # Trả về đối tượng response
        return response

def main(args=None):
    rclpy.init(args=args)

    srv_node = SrvServerNode()
    try:
        rclpy.spin(srv_node)
    except KeyboardInterrupt:
        srv_node.get_logger().info("This node is stopped by User !")
    finally:
        srv_node.destroy_node()
        rclpy.shutdown()

if __name__ == "__main__":
    main()
