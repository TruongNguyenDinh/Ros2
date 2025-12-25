# TF2 và Python

> Gói (pkg) mình đặt là static_broadcaster là mình đặt sai. Trong đó vẫn có dynamic broadcaster nhé. Sorry about this. 

## 1. Static Boardcaster

**Mục tiêu:** của nó là phát ra khung tọa độ tĩnh trong ROS2 bằng tf2 - Hệ thống quản lý các phép biến đổi tọa độ.

**Tại sao cần static transforms:** 

Trong ROS2, robot và các cảm biến, mảnh ghép của robot đều có  khung tọa độ riêng. Một static transforms là mối quan hệ cố định giữa 2 frame và sẽ không thay đổi theo thời gian ví dụ như:

- Cảm biến lidar sẽ được gắn cố định ở trên đầu, hoặc thân robot.

- Camera gắn trên robot ở phần đầu hoặc thân... 

Link bài hưỡng dẫn [Link]([Writing a static broadcaster (Python) &mdash; ROS 2 Documentation: Kilted documentation](https://docs.ros.org/en/kilted/Tutorials/Intermediate/Tf2/Writing-A-Tf2-Static-Broadcaster-Py.html))

Mục tiêu bài hưỡng dẫn:

- Nhớ lại các tạo gói ROS2 python

- Cách viết node để **broadcast static transform** đến tf2

- Build và chạy node, kiểm tra transform trên `/tf_static` 

- Biết khi nào nên dùng static transform trong hệ thống ROS2.

> Một số lệnh nhớ

```bash
colcon build
source install/setup.bash
# Chạy node
# Nếu bạn làm theo hướng dẫn của ROS2 docs
ros2 run learning_tf2_py static_turtle_tf2_broadcaster mystaticturtle 0 0 1 0 0 0
# Nếu bạn chạy thư mục của github mình
ros2 run static_broadcaster static_tf2_broadcaster mystatic 0 0 1 0 0 0
```

Sau khi chạy xong thì bạn sẽ mở một terminal mới và nhớ  `source` 

```bash
ros2 topic echo /tf_static
```

Kết quả trả về:

```
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

> Lưu ý ở các phiển bản ROS2 thấp như humble thì bản phải bỏ chỗ
> with ở chỗ rclpy.init() đi mới chạy được.

## 2 Dynamic Boardcaster

Ngược với trên thì nó là khung tọa độ thay đổi theo thời gian.

Bài viết hưỡng dẫn của ROS2 [Link]([Writing a broadcaster (Python) &mdash; ROS 2 Documentation: Humble documentation](https://docs.ros.org/en/humble/Tutorials/Intermediate/Tf2/Writing-A-Tf2-Broadcaster-Py.html))

**Nội dung bài viết:**

- Viết một node sẽ `broadcast pose của turtle` (vị trí và hướng) sang tf2, dựa trên dữ liệu nhận được từ topic /turtle{1}|{2}/pose

- Cách làm và giải thích mã nguồn

- Nhớ lại cách dùng và chạy launch file

# 3 Listener

**Mục tiêu**: 

- nghe TF tree

- tra cứu (lookup) quan hệ giữa hai frame bất kì

Nói chung là nó lắng nghe transform giữa hai frame và xử lý theo như yêu cầu mà chúng ta muốn. Các công thức toán học biến đổi vector...

## 4.Toán học biến đổi

**Công thức chuyển từ góc Euler sang Quaternion**

Trong ROS / Robotics, quaternion được dùng để biểu diễn hướng, tránh **gimbal lock** 

Thứ tự xoay : XYZ( yall - pitch - roll)     

Thứ tự trả về: $[q_x,q_y,q_z,q_w]$ 

Quaternion được tính từ các góc Euler (roll–pitch–yaw) theo thứ tự quay ZYX như sau:

$$
q_x = \sin\frac{\phi}{2}\cos\frac{\theta}{2}\cos\frac{\psi}{2}
 - \cos\frac{\phi}{2}\sin\frac{\theta}{2}\sin\frac{\psi}{2}
$$

$$
q_y = \cos\frac{\phi}{2}\sin\frac{\theta}{2}\cos\frac{\psi}{2}
 + \sin\frac{\phi}{2}\cos\frac{\theta}{2}\sin\frac{\psi}{2}
$$

$$
q_z = \cos\frac{\phi}{2}\cos\frac{\theta}{2}\sin\frac{\psi}{2}
 - \sin\frac{\phi}{2}\sin\frac{\theta}{2}\cos\frac{\psi}{2}
$$

$$
q_w = \cos\frac{\phi}{2}\cos\frac{\theta}{2}\cos\frac{\psi}{2}
 + \sin\frac{\phi}{2}\sin\frac{\theta}{2}\sin\frac{\psi}{2}
$$

$$
\mathbf{q} = [q_x, q_y, q_z, q_w]^T
$$



Thứ tự này chuẩn ROS2 / tf2

**Công thức tính khoảng cách**

$$
distance = \sqrt{(x_{target} - x_{turtle2})^2 + (y_{target} - y_{turtle2})^2}
$$

Giải thích đoạn code

```python
scale_forward_speed = 0.5
msg.linear.x = scale_forward_speed * math.sqrt(
   t.transform.translation.x ** 2 +
   t.transform.translation.y ** 2
   #Công thức: distance = sqrt(x^2 +y^2)
)
```

Vì tọa độ con rùa 2 luôn được lấy làm gốc nên luôn luôn bằng 0 (dưới góc nhìn của con rùa 2) chính vì thế ta rút gọn công thức về :

$$
distance = \sqrt{x_{target}^2 + y_{target}^2}
$$

> Lưu ý: Dưới góc nhìn của chính con rùa 2 thì luôn là (0,0) nhưng dưới góc nhìn rùa 1 và world thì khác 0.

**Công thức tính góc xoay ( góc định hướng)**

Ta có công thức:

$$
\theta = atan2(\Delta y,\Delta x) \\ \Delta y = y_{target} - y_{turtle2} \\ \Delta x = x_{target} - x_{turtle2}
$$

Tuy nhiên việc ta chọn turtle2 làm gốc nên công thức rút gọn về dạng:

$$
\theta = atan2(y,x)
$$

Kết quả trả về $(-\pi,\pi]$

Với $\theta$ là góc giữa vector (x,y) và **trục Ox**, tính ngược chiều kim đồng hồ hay nói cách khác là góc mà turtle2 cần quay để hướng về phía **target**.

Ngoài ra ta cũng có một công thức tính 

$$
\theta = atan(y/x)
$$

Tuy nhiên phải **xử lý ngoại lệ tránh chia 0**

## 5 Tổng kết

#### 5.1**Broadcaster** có nhiệm vụ **xuất bản (publish) mối quan hệ biến đổi tọa độ (vị trí + góc quay)** giữa các frame.

`Transform` bao gồm:

- vector tịnh tiến [x y z] 

- Hướng quay [quaternion / roll - pitch - yaw] 

- Công thức:

$$
T = \begin{bmatrix}
R & t \\
1 & 0
\end{bmatrix}
$$

Với R là ma trận xoay, t là ma trận tịnh tiến



#### 5.2 **Listener** có nhiệm vụ **lắng nghe (lookup) các biến đổi đó** để biết vị trí tương đối giữa các frame.

- Công thức:

$$
\vec{p}_{A->B} = T^B_A.\vec{p}
$$


