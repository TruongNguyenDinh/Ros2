# Parameter
Parameter là biến cấu hình cho node ROS2, có thể thay đổi lúc chạy (runtime) mà không cần sửa code.

Ví dụ
- `/turtlesim/background_b` là parameter màu nền.
- Robot có parameter: tốc độ tối đa, Kp/Ki/Kd, ngưỡng cảm biến,…

# Viết parameter node
Tạo pkg python
```bash
ros2 pkg create --build-type ament_python param_node --dependencies rclpy
```
Tạo file `minimal_param` trong thư mục `param_node/param_node/`
## Nội dung
```python
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
```
## Setup.py
```bash
    entry_points={
        'console_scripts': [
            'mini_param = param_node.minimal_param:main'
        ],
    },
```
## Build and Source
```bash
colcon build
source install/setup.bash
```
## Run
```bash
ros2 run param_node mini_param
```
Kết quả
```
[INFO] [1763261566.541239348] [minimal_param_node]: Hello world
[INFO] [1763261567.533987439] [minimal_param_node]: Hello world
[INFO] [1763261568.533996889] [minimal_param_node]: Hello world
[INFO] [1763261569.534047893] [minimal_param_node]: Hello world
[INFO] [1763261570.533708831] [minimal_param_node]: Hello world
[INFO] [1763261571.534173987] [minimal_param_node]: Hello world
[INFO] [1763261572.533371646] [minimal_param_node]: Hello world
....
```
# Kết luận
Như vậy bạn vừa đã tìm hiểu vè param và cách để tạo ra một parameter node với python 