# ROS 2 Launch File

## 1. Giới thiệu

Launch file trong ROS 2 được sử dụng để **khởi chạy và cấu hình nhiều node cùng lúc** trong một hệ thống robot.  
Thay vì phải chạy từng node riêng lẻ bằng lệnh `ros2 run`, launch file cho phép người dùng **tập trung toàn bộ cấu hình hệ thống vào một file duy nhất**.

ROS 2 hỗ trợ launch file ở nhiều định dạng như:
- Python (`.py`)
- XML (`.xml`)
- YAML (`.yaml`)

Trong ví dụ này, launch file được viết dưới dạng **XML**.

> Bạn có thể tham khảo thêm cách viết bằng **python, yaml**

---

## 2. Công dụng của launch file

Launch file có các công dụng chính sau:

- Khởi chạy nhiều node đồng thời
- Thiết lập namespace cho từng node để tránh xung đột topic
- Cấu hình mức log (`log-level`) cho từng node
- Remap topic giữa các node mà không cần sửa code nguồn
- Giúp hệ thống ROS 2 dễ quản lý, dễ mở rộng và dễ bảo trì

Launch file đặc biệt quan trọng trong các hệ thống:
- Nhiều node
- Nhiều robot
- Các hệ thống điều khiển phân tán

---

## 3. Ví dụ launch file

```xml
<?xml version="1.0" encoding="UTF-8"?>
<launch>
    <node pkg="turtlesim" exec="turtlesim_node" name="sim" namespace="turtlesim1"
          args="--ros-args --log-level info" />

    <node pkg="turtlesim" exec="turtlesim_node" name="sim" namespace="turtlesim2"
          args="--ros-args --log-level warn" />

    <node pkg="turtlesim" exec="mimic" name="mimic">
        <remap from="/input/pose" to="/turtlesim1/turtle1/pose"/>
        <remap from="/output/cmd_vel" to="/turtlesim2/turtle1/cmd_vel"/>
    </node>
</launch>
<!-- src: ros2 docs-->
```

---

## 4. Giải thích ví dụ

### 4.1 Khai báo launch file

```xml
<?xml version="1.0" encoding="UTF-8"?>
<launch>
```

Dòng khai báo XML cho biết file sử dụng chuẩn XML 1.0 với mã hóa UTF-8.  
Thẻ `<launch>` là thẻ gốc, dùng để chứa toàn bộ các node được khởi chạy.

---

### 4.2 Node turtlesim thứ nhất

```xml
<node pkg="turtlesim" exec="turtlesim_node" name="sim"
      namespace="turtlesim1"
      args="--ros-args --log-level info" />
```

Node này chạy chương trình `turtlesim_node` trong package `turtlesim`.

- `name="sim"`: tên node
- `namespace="turtlesim1"`: tạo không gian tên riêng cho node
- `--ros-args`: báo hiệu các tham số phía sau là tham số của ROS 2
- `--log-level info`: đặt mức log ở chế độ info để thuận tiện cho việc theo dõi và debug

Node này đóng vai trò **rùa dẫn đầu (leader)**.

---

### 4.3 Node turtlesim thứ hai

```xml
<node pkg="turtlesim" exec="turtlesim_node" name="sim"
      namespace="turtlesim2"
      args="--ros-args --log-level warn" />
```

Node này cũng chạy `turtlesim_node` nhưng nằm trong namespace khác.

- Namespace `turtlesim2` giúp tránh xung đột topic
- Mức log `warn` giúp giảm số lượng thông tin hiển thị trên terminal

Node này đóng vai trò **rùa đi theo (follower)**.

---

### 4.4 Node mimic

```xml
<node pkg="turtlesim" exec="mimic" name="mimic">
```

Node `mimic` là một node trung gian có sẵn trong package `turtlesim`.

Nhiệm vụ của node này:
- Nhận thông tin pose từ rùa thứ nhất
- Tạo lệnh điều khiển vận tốc
- Gửi lệnh đó cho rùa thứ hai

---

### 4.5 Remapping topic

```xml
<remap from="/input/pose" to="/turtlesim1/turtle1/pose"/>
```

Remap topic đầu vào của node `mimic`:
- `/input/pose` là topic mặc định mà `mimic` subscribe
- `/turtlesim1/turtle1/pose` là topic pose thực tế của rùa thứ nhất

```xml
<remap from="/output/cmd_vel" to="/turtlesim2/turtle1/cmd_vel"/>
```

Remap topic đầu ra của node `mimic`:
- `/output/cmd_vel` là topic mà `mimic` publish
- `/turtlesim2/turtle1/cmd_vel` là topic điều khiển vận tốc của rùa thứ hai

---

## 5. Nguyên lý hoạt động tổng thể

- Rùa thứ nhất di chuyển và publish thông tin pose
- Node `mimic` nhận pose của rùa thứ nhất
- Node `mimic` tạo lệnh vận tốc tương ứng
- Rùa thứ hai nhận lệnh vận tốc và di chuyển theo rùa thứ nhất

Mô hình này minh họa rõ cách các node trong ROS 2 giao tiếp với nhau thông qua topic và remapping.

---

## 6. Kết luận

Launch file giúp tổ chức và cấu hình hệ thống ROS 2 một cách rõ ràng và hiệu quả.  
Việc sử dụng launch file cho phép xây dựng các hệ thống robot phức tạp mà không cần chỉnh sửa code nguồn của từng node riêng lẻ.
