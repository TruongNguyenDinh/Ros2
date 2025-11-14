# TurtleSim và các lệnh quan sát, điều khiển
Turtlesim là một ứng dụng mô phỏng robot đơn giản, thường dùng để:
- Học ROS2 cơ bản
- Thực hành topic, service, action
- Publish velocity
- Gọi service teleport, reset
- Dùng công cụ `rqt_graph`, `rqt_plot`, `rqt_topic`
## Cài đặt
Nếu chưa cài con rùa
```bash
sudo apt install ros-humble-turtlesim
```
## Chạy turtlesim
```bash
ros2 run turtlesim turtlesim_node
```
Ngay lập tức bạn sẽ thấy cửa sổ nhỏ nền xanh hiển thị con rùa hiện lên
# Các phương thức kiểm tra, thao tác với con rùa hoặc cho tất cả các node đang hoạt động
## Node
Để xem các node đang hoạt động bạn dùng câu lệnh
```bash
# Hiển thị ngắn gọn
ros2 node list
```
```bash
# Kết quả
/turtlesim
```
Ngoài ra bạn có thể thêm các tiền số sau list để xem nhiều hơn
```bash
-a              -c              --no-daemon     --spin-time
--all           --count-nodes   -s              --use-sim-time
```
Xem thông tin node bạn sử dụng info
```bash
#ros2 node info {node}
ros2 node info /turtlesim
```
```bash
#kết quả
/turtlesim
  Subscribers:
    /parameter_events: rcl_interfaces/msg/ParameterEvent
    /turtle1/cmd_vel: geometry_msgs/msg/Twist
....
```
## Topic
Trong `ROS2`, topic là kênh dùng để trao đổi dữ liệu liên tục giữa các node theo phương thức `publish - subcribe`

Topic là gì?

- Là tên của một luồng dữ liệu (data stream)
- Node có thể publish dữ liệu lên topic
- Node khác có thể subscribe để nhận dữ liệu
> Topic giống như "kênh radio": một node phát, một hoặc nhiều node nghe.

Để xem topic đang có bạn sử dụng câu lệnh
```bash
ros2 topic list
```
```bash
# Kết quả
/parameter_events
/rosout
/turtle1/cmd_vel
/turtle1/color_sensor
/turtle1/pose
```
Ngoài ra bạn có thể xem topic đang sử dụng kiểu `msg` nào để giao tiếp thì thêm tiền tố `-t`
```bash
ros2 topic list -t
```
```bash
#Kết quả
/parameter_events [rcl_interfaces/msg/ParameterEvent]
/rosout [rcl_interfaces/msg/Log]
/turtle1/cmd_vel [geometry_msgs/msg/Twist]
/turtle1/color_sensor [turtlesim/msg/Color]
/turtle1/pose [turtlesim/msg/Pose]
```
Xem thông tin của một topic ta sử dụng 
```bash
# ros2 topic info {topic_name}
ros2 topic info /turtle1/pose
# Kết quả
Type: turtlesim/msg/Pose
Publisher count: 1
Subscription count: 0
```
Bạn có thể xem dữ liệu đang được xuất bản thủ công với lệnh `echo`
```bash
ros2 topic echo /turtle1/pose
```
```bash
# Kết quả
x: 5.544444561004639
y: 5.544444561004639
theta: 0.0
linear_velocity: 0.0
angular_velocity: 0.0
---
...
```
Bạn có thể xuất bản dữ liệu thủ công qua lệnh `pub`
```bash
ros2 topic pub /turtle1/cmd_vel geometry_msgs/msg/Twist "{linear: {x: 3.0}, angular: {z: 1.0}}"
```
Khi đó con rùa sẽ chạy vòng tròn
```bash
# Phản hồi 
publisher: beginning loop
publishing #1: geometry_msgs.msg.Twist(linear=geometry_msgs.msg.Vector3(x=3.0, y=0.0, z=0.0), angular=geometry_msgs.msg.Vector3(x=0.0, y=0.0, z=1.0))
```
Ngoài ra ta có thể sử dụng thêm một số lệnh khác với topic
```bash
bw                       find                     info                     type
delay                    hz                       list
echo                     --include-hidden-topics  pub
```
## Service
Tương tự như topic, ta có thể sử dụng các lệnh đi kèm 
```bash
call                       --include-hidden-services  type
find                       list
```
Ví dụ
```bash
ros2 service list
```
```bash
#Kết quả
/clear
/kill
/reset
/spawn
/turtle1/set_pen
/turtle1/teleport_absolute
/turtle1/teleport_relative
/turtlesim/describe_parameters
/turtlesim/get_parameter_types
/turtlesim/get_parameters
/turtlesim/list_parameters
/turtlesim/set_parameters
/turtlesim/set_parameters_atomically
```
Gọi một service bạn dùng `call`
```bash
ros2 service call /spawn turtlesim/srv/Spawn
 #Phản hồi 
requester: making request: turtlesim.srv.Spawn_Request(x=0.0, y=0.0, theta=0.0, name='')

response:
turtlesim.srv.Spawn_Response(name='turtle2')
# Khi đó một con rùa mới sẽ được thêm vào màn hình
```
## Action
Tương tự gọi service
```bash
ros2 action
#Các lệnh
info       list       send_goal
```
```bash
ros2 action list -t
#Kết quả
/turtle1/rotate_absolute [turtlesim/action/RotateAbsolute]
/turtle2/rotate_absolute [turtlesim/action/RotateAbsolute]
```
Bạn có thể gửi thủ công lệnh để vận hành con rùa
```bash
#Cú pháp:  ros2 action send_goal {action} {action_type} "{name: value}"
 ros2 action send_goal /turtle2/rotate_absolute turtlesim/action/RotateAbsolute "{theta: -3}"
```
## Interfaces
```bash
ros2 interface
list      package   packages  proto     show
```
interface là một định nghĩa các kiểu giao tiếp trong topic, nó giúp chung ta biết được kiểu giao tiếp nào đang diễn ra giữa các node
```bash
#Cú pháp  ros2 interface show {communication_type}
 ros2 interface show geometry_msgs/msg/Twist
```
```bash
# Kết quả
# This expresses velocity in free space broken into its linear and angular parts.
Vector3  linear
        float64 x
        float64 y
        float64 z
Vector3  angular
        float64 x
        float64 y
        float64 z
```
Việc hiển thị này giúp ta có thể tham chiếu để kiểm soát dữ liệu hoặc là gọi nó để xử lý.  
## Parameter
```bash
ros2 param
delete    describe  dump      get       list      load      set
```
Giả sử ta muốn đổi màu cho nền của con rùa ta cần check thông tin về param mà node con rùa đang dùng
```bash
ros2 param list
/turtlesim:
  background_b
  background_g
  background_r
  qos_overrides./parameter_events.publisher.depth
  qos_overrides./parameter_events.publisher.durability
  qos_overrides./parameter_events.publisher.history
  qos_overrides./parameter_events.publisher.reliability
  use_sim_time
```
Để xem thông tin kiểu dữ liệu ta dùng lệnh
```bash
#cú pháp ros2 param get {node_name} {param_name}
ros2 param get /turtlesim background_b
# Kết quả
Integer value is: 100
```
```bash
# Ép dữ liệu
# Cú pháp ros2 param set {node_name} {param_name} {value}
ros2 param set /turtlesim  background_b 100
```
# Điều khiển con rùa
Mở terminal 2 và gõ
```bash
source install/setup.bash
ros2 run turtlesim turtle_teleop_key
#Kết quả
Reading from keyboard
---------------------------
Use arrow keys to move the turtle.
Use G|B|V|C|D|E|R|T keys to rotate to absolute orientations. 'F' to cancel a rotation.
'Q' to quit.
```
Hiện tại ta đang có hai con rùa, để điều khiển con rùa 2 thì bạn cần phải `remap` lại điều khiển vì mặc định lệnh điều khiển con rùa sẽ sử dụng cho con rùa có tên là `/turtlesim1`
```bash
ros2 run turtlesim turtle_teleop_key --ros-args -r /turtle1/cmd_vel:=/turtle2/cmd_vel
```
với bất kì con rùa nào được `spawn`, việc `remap` luôn đúng nếu topic của `cmd_vel` của con rùa đó đang được `active`
# Kết luận
Qua trên, bạn đã có thể hiểu hơn về các giao tiếp, con rùa.



