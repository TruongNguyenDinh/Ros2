# Publisher and subcriber
Để tạo được `publisher` và `subcriber` bằng python trước hết ta cần tạo ra một package bằng python
```python
# Cú pháp :
ros2 pkg create --build-type ament_python <package_name>
```
Theo đó ta có được :
```python
ros2 pkg create --build-type ament_python pubsub_node
```
Sau khi tạo xong package, cấu trúc cây thư mục sẽ được như sau:
```
├── workspace
│   ├── build
│   ├── install
│   ├── log
│   └── src
│       ├── intnums
│       │   ├── src
│       │   ├── include
│       │   ├── CMakeLists.txt
│       │   ├── package.xml
│       │   └── msg
│       │       ├── IntNumData.msg
│       │       └── NameIntNumData.msg
│       │
│       └── pubsub_node
│           ├── resource
│           ├── test
│           ├── pubsub_node
│           ├── setup.py
│           └── package.xml
```
Tiếp đó, trong thư mục pubsub_node nằm trong package pubsub_node bạn tạo hai file `publisher.py` và `subcriber.py`
```
|── pubsub_node
│           ├── resource
│           ├── test
│           ├── pubsub_node
│           │   ├── publisher.py #here
|           │   ├── subcriber.py #here
│           ├── setup.py
│           └── package.xml
```
## Publisher content
```python
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
```
## Subcriber content
```python
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
        # Các msg.attr phải đúng với bên publish
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
if __name__ == "__main__":
    main()
```
Bước tiếp bạn hãy mở file `setup.py` trong package và thêm các thông tin vào trong `entry_points`
```bash
    #Thêm cách đường dẫn file vào trong entry_point
    entry_points={
        'console_scripts': [
            'publish_nums = pubsub_node.publisher:main',
            'subcriber_nums = pubsub_node.subcriber:main',
        ],
    },
```
Sau khi hoàn thiện các công đoạn trên, bạn hãy mở terminal và build:
```bash
colcon build
```
Sau khi build xong bạn đừng quên `source` nó để ros2 nhận biết có nội dung mới
```bash
source install/setup.bash
```
## Chạy 
Để chạy hai nodes trên vừa tạo, bạn hãy mở hai terminal và gõ cho từng bên.
> Chú ý hãy chạy : source install/setup.bash cho từng terminal trước để đảm bảo ros2 nhận được nội dung mới
### Terminal 1
```bash
source install/setup.bash
ros2 run pubsub_node publish_nums
```
Khi đó bạn sẽ có được: 
```
[INFO] [1762962685.027486422] [publisher_msg]: This node is started
[INFO] [1762962685.522679279] [publisher_msg]: publishing : name I'm publishing ! | number a: 1 | number b : 2
[INFO] [1762962686.022879149] [publisher_msg]: publishing : name I'm publishing ! | number a: 1 | number b : 2
[INFO] [1762962686.522653007] [publisher_msg]: publishing : name I'm publishing ! | number a: 1 | number b : 2
...
```
### Terminal 2
```bash
source install/setup.bash
ros2 run pubsub_node subcriber_nums
```
Khi đó sẽ nhận được:
```
[INFO] [1762962830.148252510] [subcriber_msg]: This subcriber is started
[INFO] [1762962830.523022489] [subcriber_msg]: name: I'm publishing ! | num_a = 1 | num_b = 2
[INFO] [1762962831.023680081] [subcriber_msg]: name: I'm publishing ! | num_a = 1 | num_b = 2
[INFO] [1762962831.522688674] [subcriber_msg]: name: I'm publishing ! | num_a = 1 | num_b = 2
[INFO] [1762962832.023619610] [subcriber_msg]: name: I'm publishing ! | num_a = 1 | num_b = 2
...
```
Như vậy: Hai node đã thành công giao tiếp với nhau
# Tổng kết
Qua trên, bạn đã được tìm hiều về `publisher` và `subcriber`.Bạn đã thành công trong việc cho hai node giao tiếp với nhau thông qua `topic`.

