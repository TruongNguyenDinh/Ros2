import rclpy
from rclpy.action import ActionClient
from rclpy.node import Node
# Đưa action tạo 
from action_interfaces.action import Fibonacci

class FiboActionClient(Node):
    def __init__(self):
        super().__init__("fibo_action_client")
        self._action_client = ActionClient(
            self, #trỏ chính nó
            Fibonacci, #Loại action
            'fibonacci' #Tên action
        )
    def send_goal(self,order):
            # Khởi tạo goal
            goal_msg = Fibonacci.Goal()
            # Lấy mục tiêu
            goal_msg.order = order
            # Đợi server, nếu server không phản hồi thì sẽ chặn ở đây
            self._action_client.wait_for_server()
            # Gửi goal đến server và feedback
            self._send_goal_future = self._action_client.send_goal_async(
                goal_msg,
                feedback_callback = self.feedback_callback #Gửi feedback và nhận
            )
            #Gọi callback kết quả
            self._send_goal_future.add_done_callback(self.goal_response_callback)
        
    def goal_response_callback(self,future):
        #Trạng thái của phản hồi sau khi kết nối tới server từ chối | chấp nhận
        goal_handle = future.result()
        if not goal_handle.accepted:
            self.get_logger().info('Goal rejected :(')
            return
        self.get_logger().info('Goal accepted')

        self._get_result_future = goal_handle.get_result_async()
        self._get_result_future.add_done_callback(self.get_result_callback)

    def get_result_callback(self, future):
        #Nhận kết quả cuối cùng khi server hoàn tất
        result = future.result().result
        self.get_logger().info(f'result: {result.sequence}')
        rclpy.shutdown() 
     
    def feedback_callback(self, feedback_msg):
        feedback = feedback_msg.feedback
        #Debug feedback
        self.get_logger().info(f'Received: {feedback.partial_sequence}')
        
def main(args=None):
    rclpy.init(args=args)
    action_client = FiboActionClient()
    action_client.send_goal(10)
    rclpy.spin(action_client)

if __name__ =="__main__":
    main()

