# Một số lệnh bạn cần nhớ khi dùng tf2
## 1. view_frames
view_frames tạo ra một sơ đồ các `frame` được tf2 `broadcast` đi qua ROS.
Nói đơn giản là nó sẽ hiển thị các `frame` có mối quan hệ như nào với nhau và một số thông tin khác.
> Lưu ý rằng tiện ích này chỉ hoạt động trên Linux
```bash
ros2 run tf2_tools view_frames
```
## 2. Using tf2_echo
tf2_echo xuất ra báo cáo phép biến đổi `transform`giữa hai `frame` bất kỳ được `broadcaster` phát đi qua ROS.
```bash
ros2 run tf2_ros tf2_echo [source_frame] [target_frame]
```
> Lưu ý rằng: bạn phải chạy các node trước để đảm bảo có các `transfrom` được `tf2 broadcast ` qua ROS.
## 3.Rviz
Rviz cung cấp cho bạn một cái nhìn trực quan về các `transforms` đang được `broadcaster` broadcasts.
```bash
rviz2
```
# Các nguyên lý cơ bản của Quaternion
Bạn có thể tham khảo trước ý tưởng: (Link)[https://docs.ros.org/en/humble/Tutorials/Intermediate/Tf2/Quaternion-Fundamentals.html]

## 1. Quaternion là gì ?

- **Quaternion**: là một cách biểu diễn hướng và trục xoay thông qua 4 số `[x y z w]`
- Ưu điểm: Gọn nhẹ, hiệu quả và dễ nhìn hơn ma trận xoay.
- Trong ROS2:
    - `w` nằm **cuối**(Khác với một số thư viện khác).
    - **Quaternionn đơn vị (unit)** biểu diễn **xoay hợp lệ**(độ dài = 1). Nếu không cần chuẩn hóa nó `normalize` 
    - Ví dụ ta có: quaternion mặc định (không xoay): `[0 0 0 1]` 

## 2. Các kiểu Quaternion trong ROS2
Trong ROS2 dùng hai kiểu Quaternion:
- tf2::Quaternion (dùng trong C++)
- geometry_msgs::msg::Quaternion (message trong topic). Ta có thể chuyển đổi qua lại bằng API của `tf2_geometry_msgs`

```cpp
// Với tf::Quaternion
#include <tf2/LinearMath/Quaternion.h>
...

tf2::Quaternion q;
// Khởi tạo quaternion với đầu vào là các trục xoay:
// roll - pitch - yaw
q.setRPY(0, 0, 0);
// Kết quả đầu ra sẽ là [0 0 0 1]
RCLCPP_INFO(this->get_logger(), "%f %f %f %f",
            q.x(), q.y(), q.z(), q.w());
```
Trong `đó độ lớn của q` sẽ bằng 1. Từ công thức tính sau:
$$ |q| = x^2 + y^2 + z^2 + w^2 = 1 $$

Nếu `Quaternion` khác 1 thì có thể dẫn đến sai lệch phép quay do có (scale) vì đó là phép quay không thuần túy 

Trong trường hợp không bằng 1 ta cần chuẩn hóa nó để tránh cảnh báo: `Quaternion is not normalized
` từ ROS.

```cpp
q.normalize();
```
Bây giờ ta đã có đối tượng `q` là `Quaternion` , bây giờ ta muốn chuyển nó sang msg ta có thể làm như sau:
```cpp
#include <tf2_geometry_msgs/tf2_geometry_msgs.hpp>
...

tf2::Quaternion tf2_quat, tf2_quat_from_msg;
tf2_quat.setRPY(roll, pitch, yaw);
// Chuyển từ tf2::Quaternion sang geometry_msgs::msg::Quaternion
geometry_msgs::msg::Quaternion msg_quat = tf2::toMsg(tf2_quat);

// Chuyển geometry_msgs::msg::Quaternion sang tf2::Quaternion
tf2::convert(msg_quat, tf2_quat_from_msg);
// hoặc là
tf2::fromMsg(msg_quat, tf2_quat_from_msg);
```
Trong `Python` thì không có phép tưởng đương. Thay vì đó ta sẽ sử dụng `list`:
```python
from geometry_msgs.msg import Quaternion
...

# Tạo ra một list các số floats, nó phải tương đương với tf2
# Quaternion thuộc tính [x y z w]
quat_tf = [0.0, 1.0, 0.0, 0.0]

# Chuyển đổi list msg_quat
msg_quat = Quaternion(x=quat_tf[0], y=quat_tf[1], z=quat_tf[2], w=quat_tf[3])
```
## 3. Các phép tính toán với Quaternion trong ROS2
### 3.1. Nghĩ theo RPY rồi chuyển sang quaternion
Ta thường tính **roll – pitch – yaw** (quay quanh X, Y, Z) dưới dạng góc rồi **chuyển thành quaternion**, vì đó dễ hình dung hơn.  
- Các hàm chuyển RPY → quaternion có sẵn (ví dụ `quaternion_from_euler` trong Python).
### 3.2 Áp dụng phép quay quaternion
Để áp dụng được phép quay của một Quaternion tới một `pose` ta thực hiện bằng cách: lấy Quaternion của vị trí hiện tại **Nhân với quaternion mong muốn** rồi sau đó ta `normalize()` kết quả đó (nếu cần thiết).
> Lưu ý : Thứ tự nhân sẽ rất quan trọng nên ta phải nhân đúng thứ tự.

C++
```cpp
#include <tf2_geometry_msgs/tf2_geometry_msgs.hpp>
...

tf2::Quaternion q_orig, q_rot, q_new;

q_orig.setRPY(0.0, 0.0, 0.0); // Vị trí ban đầu

q_rot.setRPY(3.14159, 0.0, 0.0); // Quaternion mong muốn. Xoay pose trước đó quanh trục X 180*
q_new = q_rot * q_orig;
q_new.normalize(); // Chuẩn hóa
```
Python
```python
q_orig = quaternion_from_euler(0, 0, 0)
# Xoay pose trước đó quanh trục X 180*
q_rot = quaternion_from_euler(3.14159, 0, 0)
q_new = quaternion_multiply(q_rot, q_orig)
```
### 3.3 Nghịch đảo Quaternion
Đơn giản là ta đổi dấu các vị trí `x y z` với `w` giữ nguyên
```bash
q[0] = -q[0] // x
q[1] = -q[1] // y
q[2] = -q[2] // z
```
### 3.4 Sự tương đối của phép quay
Giả dụ trong cùng một `frame` ta có hai phép quay `q_1` và `q_2`. Bạn muốn tìm phép quay tương đối `q_r` để có thể đưa từ `q_1` đến `q_2` theo công thức:
$$ q_2 = q_r * q_1$$
Vậy để tìm được `q_r` ta cần tính theo công thức 
$$ q_r = q_2 * invert(q_1) $$
Theo đó ta có ví dụ
```python
def quaternion_multiply(q0, q1):
    """
    Nhân hai Quaternion.

    Đầu vào
    :param q0: một mảng 4 phần tử cho Quaternion 1 (q01, q11, q21, q31)
    :param q1: một mảng phần tử cho Quaternion 2 (q02, q12, q22, q32)

    Output
    :return: một mảng 4 phần tử đầu ra là q3 (q03,q13,q23,q33)

    """
    # Trích xuất phần từ từ q0
    x0 = q0[0]
    y0 = q0[1]
    z0 = q0[2]
    w0 = q0[3]

    # Trích xuất phần từ từ q1
    x1 = q1[0]
    y1 = q1[1]
    z1 = q1[2]
    w1 = q1[3]

    # Thực hiện phép nhân mâ trận q0 và q1T
    q0q1_w = w0 * w1 - x0 * x1 - y0 * y1 - z0 * z1
    q0q1_x = w0 * x1 + x0 * w1 + y0 * z1 - z0 * y1
    q0q1_y = w0 * y1 - x0 * z1 + y0 * w1 + z0 * x1
    q0q1_z = w0 * z1 + x0 * y1 - y0 * x1 + z0 * w1

    # Tạo ra mảng kết quả
    final_quaternion = np.array([q0q1_w, q0q1_x, q0q1_y, q0q1_z])

    # Trả về mảng kết quả
    return final_quaternion

q1_inv[0] = -prev_pose.pose.orientation.x   # Nghịch đảo bằng phủ định
q1_inv[1] = -prev_pose.pose.orientation.y   # Nghịch đảo bằng phủ định
q1_inv[2] = -prev_pose.pose.orientation.z   # Nghịch đảo bằng phủ định
q1_inv[3] = prev_pose.pose.orientation.w    # Đừng động vời cái này

q2[0] = current_pose.pose.orientation.x
q2[1] = current_pose.pose.orientation.y
q2[2] = current_pose.pose.orientation.z
q2[3] = current_pose.pose.orientation.w

qr = quaternion_multiply(q2, q1_inv)
```
