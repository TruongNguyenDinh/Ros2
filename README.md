# Introduction

## 1. Node

- Chạy turtlessim

```bash
ros2 run turtlesim turtlesim_node
```

- Cách hiển thị `node`

```bash
ros2 node -h <h là lệnh muốn gọi>
```

- Xem các `node` đang hoạt động khi gọi con rùa

```bash
ros2 node list
```

Ta được kết quả `/turtlesim`

- Để có thể xem thông tin của node ta dùng

```bash
ros2 node info <node_name>
```

Với node `/turtlesim` sẽ là:

```bash
ros2 node info /turtlesim
```

Như vậy ta tổng kết được:

```bash
Commands:
  info  Output information about a node
  list  Output a list of available nodes

  Call `ros2 node <command> -h` for more detailed usage.
```

## 2. Topic

Giữ nguyên node con rùa đang chạy. Ta mở một ternimal mới và sử dụng lệnh

```bash
ros2 topic list
```

Ta sẽ được kết quả sau:

```bash
/parameter_events
/rosout
/turtle1/cmd_vel
/turtle1/color_sensor
/turtle1/pose
```

Kết quả trên chính là những topic mà con rùa đang giao tiếp trong mạng ROS2.

Ngoài ra ta còn có các lệnh khác trong `topic`

```bash
Commands:
  bw     Hiển thị độ rộng kênh được sử dụng bởi topic
  delay  Hiển thị độ trễ của topic dựa trên sự chênh lệch thời gian
  echo   Xuất ra nội dung, dữ liệu của topic
  find   Output a list of available topics of a given type
  hz     Đưa ra tốc độ khung hình hay tỉ lệ frame hiển thị trên màn hình
  info   Đưa ra thông tin về topic 
  list   Đưa ra một danh sách các topic đang hoạt động
  pub    Dùng để xuất bản kiểu dữ liệu một cách thủ công
  type   In ra kiểu dữ liệu của message

  Call `ros2 topic <command> -h` for more detailed usage.
```

## 3. Message

Message là nội dung hoặc dữ liệu mà giữa các node giao tiếp thông qua topic.

Để tạo một message, trước tiên ta cần một `workspace` để làm việc.

### 3.1 Tạo Workspace

- Bước 1: Tạo một folder workspace

- Bước 2: Trong folder workspace tạo một folder tên là `src`

```
workspace
    ├──src
```

- Bước 3 : Quay lại thư mục `workspace` gõ lệnh

```bash
colcon build
```

Lưu ý: nếu chưa cài colcon có thể xem cài đặt `colcon` ở đây. [Link]([GitHub - TruongNguyenDinh/Ros2](https://github.com/TruongNguyenDinh/Ros2/tree/main))

Sau khi build thành công ta sẽ có cây thư mục như sau

```
workspace
    ├──build
    ├──install
    ├──log
    ├──src
```

### 3.2 Tạo package message

- Để tạo được package message ta cần cho nó vào package CMake.

- pkg msg: viết tắt cho package message

Giả sử muốn tạo pkg msg có tên `intnums` ta viết lệnh sau:

```bash
ros2 pkg create --build-type ament_cmake <package_name>
```

Theo đó ta có:

```bash
ros2 pkg create --build-type ament_cmake intnums
```

Khi tạo xong ta có được cây thư mục sau:

```bash
├── workspace
    ├─── build 
    ├─── install
    ├─── log
    ├─── src
        ├─── intnums
        ├      ├─── src
        ├      ├─── include
        ├      ├─── CMakeLists.txt
        ├      ├─── package.xml

```

Tiếp theo ta tạo thư mục `msg` trong thư mục `intnums`

Sau đó ta sẽ tạo các file `message` trong thư mục `msg` ta vừa tạo

- Lưu ý: tên folder bắt buộc phải là `msg`

- Tên các `file *.msg` phải viết hoa chữ cái đầu. 

```bash

├── workspcae
    ├─── build 
    ├─── install
    ├─── log
    ├─── src
        ├─── intnums
        ├      ├─── src
        ├      ├─── include
        ├      ├─── CMakeLists.txt
        ├      ├─── package.xml
        ├      ├─── msg
        ├             ├─── IntNumData.msg
        ├             ├─── NameIntNumData.msg



```

- Trong file `IntNumData.msg` có nội dung cơ bản như sau

```bash
int64 num_a
int64 num_b
```

- Trong file `NameIntNumData.msg` có nội dung như sau

```bash
string name 
IntNumData int_num_data
```

Tiếp đó ta sẽ khai báo hai msg mới này trong file `Cmakelist.txt` như sau dán ở dòng 13:

```bash
find_package(rosidl_default_generators REQUIRED)

rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/IntNumData.msg"
  "msg/NameIntNumData.msg"
 )
```

Sau đó ta sẽ khai báo tiếp trong file `packages.xml` như sau ở dòng 11:

```bash
<build_depend>rosidl_default_generators</build_depend>

<exec_depend>rosidl_default_runtime</exec_depend>

<member_of_group>rosidl_interface_packages</member_of_group>
```

Như vậy bạn đã xong phần giới thiệu cơ bản, hay quay lại nhánh Python để tiếp tục tìm hiểu thêm tại đây: [Link]([GitHub - TruongNguyenDinh/Ros2 at Python](https://github.com/TruongNguyenDinh/Ros2/tree/Python))