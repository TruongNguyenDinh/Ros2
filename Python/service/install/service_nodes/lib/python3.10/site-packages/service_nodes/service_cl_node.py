import rclpy
from rclpy.node import Node
import sys
# Gọi service để lấy dữ liệu
from add_two_ints.srv import SumTwoNums

class SrvClientNode(Node):
    def __init__(self):
        # Đặt tên node, ở đây là service
        super().__init__('srv_client_node')
        # Tạo ra một client node mới 
        self.cli = self.create_client(
            SumTwoNums, # Loại service
            'sum_to_nums' # Tên service được đặt bên server
        )

        # Kiểm tra kết nối 
        # -nếu server mà nó đang lắng nghe chưa hoạt động thì chờ và ghi log 
        # -nếu server hoạt động thì sẽ thực hiện việc đẩy request

        while not self.cli.wait_for_service(timeout_sec=1.0):
            self.get_logger().info("The service node is not active, waiting ...")
        
        #Tạo ra đối tượng để yêu cầu
        self.req = SumTwoNums.Request()

    def send_request(self,a,b):
        self.req.a = a
        self.req.b = b

        #Gửi yêu cầu đi 
        return self.cli.call_async(self.req)
def main():
    rclpy.init()
    # Tạo client node
    cli_srv = SrvClientNode()
    try:
        # Lấy hai số đầu vào
        a,b =int(sys.argv[1]), int(sys.argv[2])
        # Gửi yêu cầu đi
        sender = cli_srv.send_request(a,b)
        # Chờ cho đến khi nhận phản hồi hoặc sẽ thất bại
        rclpy.spin_until_future_complete(cli_srv,sender)

        response = sender.result()
        cli_srv.get_logger().info(
            f'The response for {a} + {b} = {response.sum}'
        )
    except KeyboardInterrupt:
        cli_srv.get_logger().info("This node is stopped by user ")
    finally:
        cli_srv.destroy_node()
        rclpy.shutdown()

