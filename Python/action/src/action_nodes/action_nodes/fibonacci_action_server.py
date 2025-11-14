import rclpy
from rclpy.action import ActionServer
from rclpy.node import Node
import time
# Đường dẫn tới action 
from action_interfaces.action import Fibonacci

class FiboActionServer(Node):
    def __init__(self):
        super().__init__('fibo_action_server')
        # Khởi tạo action
        self.action_server = ActionServer(
            self, #Tham chiếu chính class này
            Fibonacci, #Loại action
            'fibonacci', #Đặt tên cho action
            self.excute_callback #Hàm thực hiện
        )
    def excute_callback(self, goal_handle):
        #
        self.get_logger().info("Excuting goal...")
        
        feedback_msg =Fibonacci.Feedback()
        feedback_msg.partial_sequence = [0,1]

        for i in range(1, goal_handle.request.order):
            #Thêm các số fibo vào mảng partial_sequence
            feedback_msg.partial_sequence.append(
                # Công thức fibo[i] = fibo[i]+ fibo[i-1]
                feedback_msg.partial_sequence[i]+ feedback_msg.partial_sequence[i-1]
            )
            #debug 
            self.get_logger().info(f'Feedback runtime: {feedback_msg.partial_sequence[i]}')
            # Đẩy phản hồi
            goal_handle.publish_feedback(feedback_msg)
            #Phản hồi sau mỗi 1s
            time.sleep(1)
        #Đánh dấu là đã thành công
        goal_handle.succeed()

        #Gọi result 
        result = Fibonacci.Result()
        #Lưu kết quả cuối cùng vào result
        result.sequence = feedback_msg.partial_sequence 

        return result

def main(args=None):
    rclpy.init(args=args)
    fibo_server = FiboActionServer()

    rclpy.spin(fibo_server)

if __name__ == "__main__":
    main()


    
