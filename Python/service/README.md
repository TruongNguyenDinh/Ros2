# ROS2 Service — Yêu cầu và Phản hồi

Trong ROS2, **Service** đảm nhận việc **trao đổi dữ liệu theo mô hình “yêu cầu - phản hồi”** giữa hai node:

- **Client node**: gửi *request* (yêu cầu) và chờ nhận *response* (phản hồi).
- **Server node**: luôn hoạt động để lắng nghe *request* từ client, xử lý dữ liệu, và gửi lại *response*.

> **Ghi nhớ:**  
> - Node **server** luôn chạy nền để chờ yêu cầu.  
> - Node **client** thường chỉ hoạt động tạm thời — sau khi nhận được kết quả, nó có thể kết thúc vòng đời.

---

## 1. Tạo gói dịch vụ (Service Interface)

Trước tiên, ta cần tạo một **package** chứa định nghĩa giao tiếp `.srv`.

```bash
ros2 pkg create --build-type ament_cmake add_two_ints
```

Bên trong package `add_two_ints`, tạo thư mục `srv` và file `SumTwoNums.srv` như sau:

```
├── workspace
│   ├── build 
│   ├── install
│   ├── log
│   ├── src
│       ├── add_two_ints
│       │   ├── CMakeLists.txt
│       │   ├── package.xml
│       │   ├── srv
│       │       ├── SumTwoNums.srv
```

### Nội dung file `SumTwoNums.srv`

```bash
# Request
int64 a
int64 b
---
# Response
int64 sum
```

---

##  2. Cấu hình trong `CMakeLists.txt`

Thêm vào cuối file:

```cmake
find_package(rosidl_default_generators REQUIRED)

rosidl_generate_interfaces(${PROJECT_NAME}
  "srv/SumTwoNums.srv"
)
```

---

##  3. Cập nhật `package.xml`

Thêm vào phần phụ thuộc:

```xml
<build_depend>rosidl_default_generators</build_depend>
<exec_depend>rosidl_default_runtime</exec_depend>
<member_of_group>rosidl_interface_packages</member_of_group>
```

---

##  4. Tạo Service Nodes (Client & Server)

Tạo package cho các node service:

```bash
ros2 pkg create --build-type ament_python service_nodes --dependencies rclpy
```

Cấu trúc thư mục:

```
├── workspace
│   ├── src
│       ├── add_two_ints
│       │   ├── srv/SumTwoNums.srv
│       ├── service_nodes
│           ├── package.xml
│           ├── setup.py
│           ├── service_nodes
│           │   ├── service_cl_node.py
│           │   ├── service_sv_node.py
```

---

### File `service_sv_node.py` (Server)

```python
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

```

---

###  File `service_cl_node.py` (Client)

```python
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


```

---

## 5. Khai báo trong `setup.py`

Thêm vào phần `entry_points`:

```python
entry_points={
    'console_scripts': [
        'server_node = service_nodes.service_sv_node:main',
        'client_node = service_nodes.service_cl_node:main',
    ],
},
```

---

##  6. Build và Chạy

Build toàn bộ workspace:
```bash
colcon build
source install/setup.bash
```

Chạy **server node**:
```bash
ros2 run service_nodes server_node
```

Chạy **client node**:
```bash
ros2 run service_nodes client_node 2 3
```

Kết quả:
```bash
# Client output:
[INFO] [srv_client_node]: The response for 2 + 3 = 5

# Server output:
[INFO] [srv_server_node]: Request: 2 || 3 => Response: 5
```

---

## 🔍 7. Kiểm tra Service đang hoạt động

```bash
ros2 service list -t
```

Kết quả ví dụ:
```
/sum_to_nums [add_two_ints/srv/SumTwoNums]
```

Xem chi tiết interface:
```bash
ros2 interface show add_two_ints/srv/SumTwoNums
```

Kết quả:
```bash
# Request
int64 a
int64 b
---
# Response
int64 sum
```

---

## 🧭 8. Gọi Service trực tiếp bằng lệnh

```bash
ros2 service call /sum_to_nums add_two_ints/srv/SumTwoNums "{a: 3, b: 5}"
```

Phản hồi:
```bash
requester: making request: add_two_ints.srv.SumTwoNums_Request(a=3, b=5)

response:
add_two_ints.srv.SumTwoNums_Response(sum=8)
```

---

##  Tổng kết

| Thành phần | Vai trò | Mô tả |
|-------------|----------|-------|
| `.srv` file | Định nghĩa giao tiếp | Xác định dữ liệu yêu cầu & phản hồi |
| Server node | Xử lý yêu cầu | Lắng nghe, tính toán, gửi lại kết quả |
| Client node | Gửi yêu cầu | Gửi dữ liệu, chờ và nhận kết quả |
| Command-line | Kiểm tra và gọi service | Dễ dàng debug hoặc test nhanh |

> Qua ví dụ trên, bạn đã hiểu cách **tạo, build, và sử dụng ROS2 Service** đầy đủ — từ định nghĩa `.srv` cho đến giao tiếp giữa các node Client ↔ Server.
