# TF2 và Python

> Gói (pkg) mình đặt là static_broadcaster là mình đặt sai. Trong đó vẫn có dynamic broadcaster nhé. Sorry about this. 

## 1. Static Boardcaster

**Mục tiêu:** của nó là phát ra khung tọa độ tĩnh trong ROS2 bằng tf2 - Hệ thống quản lý các phép biến đổi tọa độ.

**Tại sao cần static transforms:** 

Trong ROS2, robot và các cảm biến, mảnh ghép của robot đều có khung tọa độ riêng. Một static transforms là mối quan hệ cố định giữa 2 frame và sẽ không thay đổi theo thời gian ví dụ như:

- Cảm biến lidar sẽ được gắn cố định ở trên đầu, hoặc thân robot.
- Camera gắn trên robot ở phần đầu hoặc thân... 

Link bài hướng dẫn  
[Writing a static broadcaster (Python)](https://docs.ros.org/en/kilted/Tutorials/Intermediate/Tf2/Writing-A-Tf2-Static-Broadcaster-Py.html)

**Mục tiêu bài hướng dẫn:**

- Nhớ lại các tạo gói ROS2 python
- Cách viết node để **broadcast static transform** đến tf2
- Build và chạy node, kiểm tra transform trên `/tf_static`
- Biết khi nào nên dùng static transform trong hệ thống ROS2

> Một số lệnh nhớ

```bash
colcon build
source install/setup.bash

# Nếu bạn làm theo hướng dẫn ROS2 docs
ros2 run learning_tf2_py static_turtle_tf2_broadcaster mystaticturtle 0 0 1 0 0 0

# Nếu bạn chạy repo github của mình
ros2 run static_broadcaster static_tf2_broadcaster mystatic 0 0 1 0 0 0
```

Sau khi chạy xong, mở terminal mới và nhớ `source`:

```bash
ros2 topic echo /tf_static
```

Kết quả:

```yaml
transforms:
- header:
    stamp:
      sec: 1766645328
      nanosec: 423658167
    frame_id: world
  child_frame_id: mystatic
  transform:
    translation:
      x: 0.0
      y: 0.0
      z: 1.0
    rotation:
      x: 0.0
      y: 0.0
      z: 0.0
      w: 1.0
---
```

> Lưu ý: ROS2 phiên bản thấp (ví dụ humble) cần **bỏ `with rclpy.init()`** thì code mới chạy được.

---

## 2. Dynamic Broadcaster

Ngược lại với static broadcaster, dynamic broadcaster xuất bản khung tọa độ **thay đổi theo thời gian**.

Link hướng dẫn ROS2:  
[Writing a broadcaster (Python)](https://docs.ros.org/en/humble/Tutorials/Intermediate/Tf2/Writing-A-Tf2-Broadcaster-Py.html)

**Nội dung:**

- Viết node `broadcast pose của turtle`
- Lấy dữ liệu từ topic `/turtle{1|2}/pose`
- Giải thích code và launch file

---

## 3. Listener

**Mục tiêu:**

- Nghe TF tree
- Tra cứu (`lookup`) quan hệ giữa hai frame bất kỳ

Listener lắng nghe transform giữa hai frame và xử lý theo mục đích mong muốn (điều khiển, tính toán, v.v.)

---

## 4. Toán học biến đổi

### 4.1 Chuyển từ Euler sang Quaternion

Quaternion dùng trong ROS / Robotics để tránh **gimbal lock**.

- Thứ tự xoay: XYZ (roll – pitch – yaw)
- Thứ tự trả về: `[q_x, q_y, q_z, q_w]`
- Chuẩn ROS2 / tf2 (ZYX)

$$
q_x = sin(φ/2)cos(θ/2)cos(ψ/2) - cos(φ/2)sin(θ/2)sin(ψ/2)
$$

$$
q_y = cos(φ/2)sin(θ/2)cos(ψ/2)
    + sin(φ/2)cos(θ/2)sin(ψ/2)
$$

$$
q_z = cos(φ/2)cos(θ/2)sin(ψ/2)
    - sin(φ/2)sin(θ/2)cos(ψ/2)
$$

$$
q_w = cos(φ/2)cos(θ/2)cos(ψ/2)
    + sin(φ/2)sin(θ/2)sin(ψ/2)
$$

$$
q = [q_x, q_y, q_z, q_w]^T
$$

---

### 4.2 Công thức khoảng cách

$$
distance = \sqrt{(x_{target} - x_{turtle2})^2 + (y_{target} - y_{turtle2})^2}
$$

Trong code:

```python
msg.linear.x = scale_forward_speed * math.sqrt(
    t.transform.translation.x ** 2 +
    t.transform.translation.y ** 2
)
```

Do turtle2 được lấy làm gốc nên:

```latex
distance = sqrt(x^2 + y^2)
```

---

### 4.3 Công thức góc định hướng

$$
θ = atan2(Δy, Δx)
$$
$$
Δy = y_{target} - y_{turtle2}
$$
$$
Δx = x_{target} - x_{turtle2}
$$

Rút gọn:

$$
θ = atan2(y, x)
$$

Ngoài ra có thể dùng:

$$
θ = atan(y/x)
$$

Nhưng cần **xử lý ngoại lệ chia cho 0**.

---

## 5. Tổng kết

### 5.1 Broadcaster

- Xuất bản quan hệ biến đổi giữa các frame
- Bao gồm:
  - Vector tịnh tiến `[x y z]`
  - Hướng quay (quaternion / RPY)

Ma trận biến đổi:

```latex
T = | R  t |
    | 0  1 |
```

---

### 5.2 Listener

- Lắng nghe và tra cứu transform
- Biết vị trí tương đối giữa các frame

$$
\vec{p}_{A->B} = T^B_A.\vec{p}
$$



