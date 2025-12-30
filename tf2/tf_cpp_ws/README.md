# Using time (C++)
> Chú ý: Để đọc bài viết này, bạn trước hết nên đọc toàn bộ hưỡng dẫn về tf2 bên python, và các mã c++ để có thể hiểu được phần này. Thanks

Trước đó ta có đoạn mã sau trong file: `turtle_tf2_listener.cpp`
```cpp
t = tf_buffer_->lookupTransform(
   toFrameRel,
   fromFrameRel,
   tf2::TimePointZero // tf2::TimePoint()
);
```
Như bạn thấy thì có tham số truyền vào đó là:`tf2::TimePointZero`, nó được hiểu là bạn đã chỉ định bộ định thời là 0s. Tức là phép biến đổi 'mới nhất hiện có' trong bộ đệm `buffer`.

Bây giờ thử sửa thành `this->get_clock()->now()`
```cpp
t = tf_buffer_ ->lookupTransform(
    toFrameRel,
    fromFrameRel,
    //tf2::TimePointZero //Ban đầu
    this->get_clock()->now() // Thử đổi sang đoạn này
);
```
Lúc này sẽ có một vấn đề xảy ra
```bash
[turtle_tf2_listener-4] [INFO] [1766990742.999066347] [listener]: Successfully spawned
[turtle_tf2_listener-4] [INFO] [1766990743.919695315] [listener]: could not transform turtle1 to turtle2 : Lookup would require extrapolation into the future.  Requested time 1766990743.916591 but the latest data is at time 1766990743.910498, when looking up transform from frame [turtle1] to frame [turtle2]
```
**Giải thích**:
- Mỗi một `listener` có một `buffer` lưu trữ các phép biển đổi từ `broadcast` từ tf2 là khác nhau.
- Khi một `broadcaster` gửi tín hiệu đi một phép `transform`, nó sẽ cần một khoảng thời gian nhỏ trước khi phép `transform` đó được đưa vào `buffer` để lưu trữ. 

-> Khi ta yêu cầu phép biển đổi  tại `frame hiện tại ` thì gần như là chưa có phép biển đổi được lưu vì nó phải trễ một khoảng thời gian nhỏ để lưu nên sẽ có thông báo là: `Lookup would require extrapolation into the future.` 

- Hướng giải quyết: Ta sẽ thêm một chút `delay` vào để đảm bảo nó đợi đủ thời gian để phép biển đổi `transfrom` đã được lưu tại thời điểm lấy mẫu.

```cpp
t = tf_buffer_ ->lookupTransform(
    toFrameRel,
    fromFrameRel,
    //tf2::TimePointZero //Ban đầu
    this->get_clock()->now(), // Thử đổi sang đoạn này
    std::chrono::milliseconds(100) // Thêm một chút delay
);
```
Sau đó thực hiện `build` và `source` và chạy lại chương trình:
```bash
ros2 launch learning_tf2_cpp turtle_tf2_demo.launch.py
```
Bạn sẽ thấy được chương trình lại hoạt động bình thường
> Lưu ý: hàm `lookupTransform` sẽ thực hiện chặn **blocking** cho đến khi có thể thực hiện phép biến đổi `transform` giữa hai con rùa trở nên khả dụng. Nếu phép biến đổi `transform` chưa khả dụng thì sẽ đẩy ra `exception`
# Traveling in time (C++)
`Traveling in time`: là cho con rùa `turtle2` sẽ đi theo `carrot` sau một khoảng thời gian được thiết lập. Hay đơn giản là nó sẽ đi đến vị trí của `carrot` tại `n giây trước `

Tiếp tục sử dụng lại mã nguồn phía trên
```cpp
t = tf_buffer_ ->lookupTransform(
    toFrameRel,
    fromFrameRel,
    //tf2::TimePointZero //Ban đầu
    this->get_clock()->now(), // Thử đổi sang đoạn này
    std::chrono::milliseconds(100) // Thêm một chút delay
);
```
Ta sửa thời gian từ `now` thành một thời gian của quá khứ

$$t_{past} = t_{now} - t{duration}$$
```cpp
t = tf_buffer_ ->lookupTransform(
    toFrameRel,
    fromFrameRel,
    //tf2::TimePointZero //Ban đầu
    this->get_clock()->now(), // Thử đổi sang đoạn này
    std::chrono::milliseconds(100) // Thêm một chút delay
);
```
Tiếp đó bước quan trọng là `build ` và `source`
Chạy lệnh sau và kiểm tra kết quả:
```bash
ros2 launch learning_tf2_cpp turtle_tf2_fixed_frame_demo.launch.py
```
Đợi một khoảng thời gian bạn sẽ nhận thấy một vấn đề là con rùa 2 sẽ chạy loạn lên thay vì như tưởng tượng của chúng là ta nó sẽ phải chạy đến vị trí của củ carrot cách đây 5 giây. Lý do cho đó là:

**Lý do:** Mặc dù vị trí của củ `carrot` là không đổi trong trường hợp bạn không thực hiện di chuyển con rùa một nhưng vấn đề thực sự nằm ở `turtle2`. Nhưng với đoạn mã trên bạn đang thực hiện hỏi là: ví trí của củ `carrot` cách đây 5 giây so với vị trí của `turtle2` cách đây 5s. Điều này thực sự là nguyên nhân dẫn đến lý do con rùa di chuyển lung tung vì vị trí con rùa cách đây 5s là thay đổi nên khiến cho mỗi lần thực hiện phép tính toán `transform` sẽ luôn thay đổi một cách sai mục đích.

Vậy để trả lời được câu hỏi: Ví trí của củ `carrot` cách đây 5s so với vị trí hiện tại của con rùa `turtle2` như nào ? Ta cần thay đổi (thêm) một tham số để lấy thời gian khác nhau trong `buffer`.
```cpp
t = tf_buffer_ ->lookupTransform(
    toFrameRel,
    this->get_clock()->now(), // Lấy thời điểm con rùa hiện tại
    fromFrameRel,
    this->get_clock()->now() - rclcpp::Duration(5,0), // Lấy thời điểm target_frame trước đó 5s
    "world", // Frame tĩnh không thay đổi theo thời gian
    std::chrono::microseconds(100) // Đợi để phép biến đổi được lưu trong buffer để phép lấy now() không bị expection
);
```
> Lưu ý rằng là: để con rùa 2 bám theo củ `carrot` thì bạn nhớ sửa target_frame ở file `turtle_tf2_demo.launch.py` sang `carrot` nhé. Không sửa thì nó sẽ theo `turtle1`.
# Checking the timestamp
Như ví dụ trên:
```cpp
t = tf_buffer_ ->lookupTransform(
    toFrameRel,
    fromFrameRel,
    //tf2::TimePointZero //Ban đầu
    this->get_clock()->now(), // Thử đổi sang đoạn này
    std::chrono::milliseconds(100) // Thêm một chút delay
);
```
Chúng ta không thể cứ đoán bừa thời gian như này được, vì có thể `delay` của chúng ta quá lớn. Chính vì thế `ROS2` cung cấp cho chúng ta một cách để check xem thời gian để lưu một lần biến đổi vào `buffer` mất bao lâu.

Bạn mở terimal và chạy
```bash
ros2 launch learning_tf2_cpp turtle_tf2_demo.launch.py
```
Tại terminal khác chạy lệnh sau:
```bash
ros2 run tf2_ros tf2_monitor turtle2 turtle1
```
Kết quả trả về ta có được:
```bash
RESULTS: for turtle2 to turtle1
Chain is: turtle1
Net delay     avg = 0.00159247: max = 0.015728

Frames:
Frame: turtle1, published by <no authority available>, Average Delay: 0.000533181, Max Delay: 0.000793457

All Broadcasters:
Node: <no authority available> 125.247 Hz, Average Delay: 0.000518684 Max Delay: 0.00109553
```
Tại kết quả trả về bạn có thể thấy `max delay` $\approx$ 0.015s
Khi đó bạn có thể sửa thành
```cpp
t = tf_buffer_->lookupTransform(
    toFrameRel,
    fromFrameRel,
    this->now() - rclcpp::Duration::from_seconds(0.1)
);
```
# Message Filter
Tại phần ví dụ trên ta có thể thấy là việc `subscriber` thông thường sẽ luôn gọi `function callback` bất kể khi nào nó nhận được `msg` nên sẽ sảy ra hiện tượng chưa có `transform` mà đã gọi callback dẫn đến cảnh báo của ROS2 xuất hiện
```bash
could not transform turtle1 to turtle2 :
Lookup would require extrapolation into the future
```
Nguyên nhân là do **message có timestamp**, nhưng **tf2 chưa có transform tương ứng tại thời điểm đó.**
Lúc này message filter chính là giải pháp giúp các bạn tránh hiện tượng trên.

**Message Filter** là cơ chế giúp **kiểm soát thời điểm callback được gọi**, dựa trên **sự tồn tại của transform trong tf2 tại đúng timestamp của message.**

- `message_filters::Subscriber` là một subscriber đặc biệt, **không gọi callback trực tiếp** khi nhận được message.
- Thay vào đó, message sẽ được chuyển cho **tf2_ros::MessageFilter.**
- `MessageFilter` sẽ **giữ message lại** và chỉ cho phép callback được gọi khi **tf2 đã có transform phù hợp với timestamp của message.**

**Tóm lại,**` Message Filter` nên được sử dụng khi **xử lý dữ liệu cảm biến,** vì các **message này luôn đi kèm mốc thời gian,** và việc **đồng bộ message với transform là cần thiết để đảm bảo tính chính xác và ổn định của hệ thống.**

Ví dụ:

**Robot** gắn cảm biến `LiDAR` nó gửi dữ liệu về qua topic
- `sensor_msgs/LaserScan`
- hoặc `sensor_msgs/PointCloud2`
```bash
Frame: laser
Timestamp: 10.25s
Dữ liệu: khoảng cách các tia
```
**tf2 cung cấp chuỗi transform**
```bash
map → odom → base_link → laser
# Quy trình này bắt buộc phải đồng bộ thời gian với nhau,
# Lệch một quy trình thì tính toán sẽ bị lỗi vị trí,..  
```
Giả sử tại thời điểm nhận tín hiệu từ `LiDAR` tại **timestamped** 10.25s. Nhưng `transform` từ `map -> odom` tại 10.25s **chưa publish kịp**. Nếu gọi callback ngay thì sẽ bị báo :
```bash
Lookup would require extrapolation
```
Vậy lúc này, ta cùng `message filter` sẽ giúp chúng ta:
- LaserScan được giữ lại
- Chờ transform map -> laser đúng thời gian
- Callback sẽ được gọi chạy an toàn
> Lưu ý: LiDAR không cung cấp vị trí cho robot của bạn, nó chỉ gửi đi dữ liệu trong frame của nó, tf2 mới là công cụ giúp robot của bạn xác định vị trí của nó và transform sang map để so với map.
