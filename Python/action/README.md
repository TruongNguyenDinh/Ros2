# Action
## Khái niệm
Trong ROS2, Action là một cơ chế giao tiếp cho các tác vụ mất thời gian để hoàn thành (long-running tasks), cho phép:
- Gửi một yêu cầu đến robot (goal)
- Robot thực hiện tác vụ (có thể mất vài giây → vài phút)
- Robot gửi feedback liên tục (tiến độ)
- Khi xong, robot trả về kết quả cuối cùng (result)
- Có thể huỷ tác vụ bất kỳ lúc nào (cancel goal)
## Cấu trúc
Một action luôn bao gồm 3 thành phần
```bash
#Goal
data_type name
---
#Result
data_type name
---
#Feedback
data_type name
```
## Hoạt động

Khi một action client + server hoạt động, luồng dữ liệu sẽ như sau

Client:
- Gửi goal
- Nhận feedback (callback) trong quá trình server đang xử lý
- Nhận kết quả cuối (result) sau khi server xử lý xong

Server:
- Nhận goal
- Chấp nhận hoặc từ chối
- Thực hiện tác vụ (có thể loop)
- Gửi feedback sau mỗi phiên xử lý
- Khi xong thì sẽ gửi result lại cho client
## Tạo action
Tương tự như tạo service ta sẽ sử dụng cmake để làm

Bước 1: Tạo pkg action
```bash
ros2 pkg create --build-type ament_cmake action_interfaces
```
Bước 2: Tạo thư mục action trong pkg action_interfaces vừa tạo
```bash
cd action_interfaces
mkdir action
```
Bước 3: Tạo tệp tin `Fibonacci.action` bên trong thư mục `action`
```
├── workspace
    ├─── build 
    ├─── install
    ├─── log
    ├─── src
        ├─── action_interfaces
        ├      ├─── src
        ├      ├─── include
        ├      ├─── CMakeLists.txt
        ├      ├─── package.xml
        ├      ├─── action
        ├             ├─── Fibonacci.action
```
Nội dung:
```bash
#Request
int32 order
---
#Result
int32[] sequence
---
#Feedback
int32[] partial_sequence
```
Thêm đường dẫn vào CMakeList
```bash
# Thêm ở đây
find_package(rosidl_default_generators REQUIRED)

rosidl_generate_interfaces(${PROJECT_NAME}
  "action/Fibonacci.action"
)
# Kết thúc thêm
```
Thêm depend vào package.xml
```bash
  <!-- Đoạn thêm -->
  <buildtool_depend>rosidl_default_generators</buildtool_depend>

  <depend>action_msgs</depend>

  <member_of_group>rosidl_interface_packages</member_of_group>
  <!-- Kết thúc -->
```
## Tạo action node 
### Tạo package python
```bash
# Sử dụng câu lệnh quen thuộc
ros2 pkg create --build-type ament_python action_nodes
```
Trong pkg vừa tạo, tạo hai files `fibonacci_action_client.py` và `fibonacci_action_server.py` trong thư mục `action_nodes`
```
├── workspace
    ├─── build 
    ├─── install
    ├─── log
    ├─── src
        ├─── action_interfaces
        ├      ├─── src
        ├      ├─── include
        ├      ├─── CMakeLists.txt
        ├      ├─── package.xml
        ├      ├─── action
        ├             ├─── Fibonacci.action
        ├        
        ├─── action_nodes
        ├      ├─── resource
        ├      ├─── test
        ├      ├─── action_nodes
        ├      ├        ├─── fibonacci_action_server.py
        ├      ├        ├─── fibonacci_action_client.py               
        ├      ├─── setup.py
        ├      ├─── package.xml
```
### Server
```python
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
```
### Client
```python
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
            goal_msg = Fibonacci.Goal()
            goal_msg.order = order
            self._action_client.wait_for_server()

            self._send_goal_future = self._action_client.send_goal_async(
                goal_msg,
                feedback_callback = self.feedback_callback
            )
            self._send_goal_future.add_done_callback(self.goal_response_callback)
        
    def goal_response_callback(self,future):
        goal_handle = future.result()
        if not goal_handle.accepted:
            self.get_logger().info('Goal rejected :(')
            return
        self.get_logger().info('Goal accepted')

        self._get_result_future = goal_handle.get_result_async()
        self._get_result_future.add_done_callback(self.get_result_callback)

    def get_result_callback(self, future):
        result = future.result().result
        self.get_logger().info(f'result: {result.sequence}')
        rclpy.shutdown()  
    def feedback_callback(self, feedback_msg):
        feedback = feedback_msg.feedback
        self.get_logger().info(f'Received: {feedback.partial_sequence}')
        
def main(args=None):
    rclpy.init(args=args)
    action_client = FiboActionClient()
    action_client.send_goal(10)
    rclpy.spin(action_client)

if __name__ =="__main__":
    main()
```
### Config trong setup.py
```bash
entry_points={
        'console_scripts': [
            'action_client = action_nodes.fibonacci_action_client:main',
            'action_server = action_nodes.fibonacci_action_server:main',
        ],
},
```
# Tổng kết
Như vậy qua hưỡng dẫn trên, ta đã biết `action` có tác dụng gì ? Cách tạo ra action, server và client để giao tiếp thông qua action như nào.






