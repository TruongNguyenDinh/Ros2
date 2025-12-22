# Publish và Subcription với CPP

> Trước khi vào bài hưỡng dẫn này, bạn hãy vui lòng xem và tạo ra một msg ở link sau: [[GitHub - TruongNguyenDinh/Ros2 at introduction](https://github.com/TruongNguyenDinh/Ros2/tree/introduction)]

## 1.Tạo pkg cpp

```bash
ros2 pkg create --build-type ament_cmake cpp_pubsub
```

Sau đó vào thư mục `src` của folder `cpp_pubsub` vừa tạo. Bạn tạo hai file 

```bash
publisher.cpp
subcriber.cpp
```

```bash
# Cấu trúc cây thư mục
├── workspcae
    ├─── build 
    ├─── install
    ├─── log
    ├─── src
        ├─── intnums
        ├─── cpp_pubsub
        ├      ├─── src
        ├          ├─── publisher.cpp
        ├          ├─── subcriber.cpp
        ├      ├─── include
        ├      ├─── CMakeLists.txt
        ├      ├─── package.xml

```

## 2. Publisher.cpp

```cpp
#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "intnums/msg/name_int_num_data.hpp"

class PublisherMsg : public rclcpp::Node{
    public:
    PublisherMsg(): Node("publisher_msg"){
        publisher_ = this->create_publisher<intnums::msg::NameIntNumData> // Loại msg được gửi là NameIntNumData
        (
            "send_int", //Tên topic
            10 // Kích thước hàng đợi
        );
        timer_ = this->create_wall_timer // Tạo thời gian
        (
            std::chrono::milliseconds(500), //Tạo timer
            std::bind(&PublisherMsg::publish_nums,this) // gọi hàm xuất bản dữ liệu
        );
    }
    private:
    void publish_nums(){
        auto msg = intnums::msg::NameIntNumData();
        msg.name = "I'm publishing !";
        msg.int_num_data.num_a = 1;
        msg.int_num_data.num_b = 2;
        RCLCPP_INFO(
            this->get_logger(),
            "name: %s | number a: %ld | number b: %ld",
            msg.name.c_str(),
            msg.int_num_data.num_a,
            msg.int_num_data.num_b
        );
        publisher_ ->publish(msg);
    }
    rclcpp::TimerBase::SharedPtr timer_; 
    rclcpp::Publisher<intnums::msg::NameIntNumData>::SharedPtr publisher_;
    // rclcpp::Publisher<type of message>::SharedPtr ptr_;
};
int main(int argc, char *argv[]){
    rclcpp::init(argc,argv);
    rclcpp::spin(std::make_shared<PublisherMsg>());
    rclcpp::shutdown();
    return 0;
}
```

Giải thích:

Thêm các thư viện cần thiết

```cpp
#include <chrono>
#include <functional>
#include <memory>
#include <string>
```

Thêm thư viện của Ros2

```cpp
#include "rclcpp/rclcpp.hpp"
```

```cpp
#include "intnums/msg/name_int_num_dat.hpp"
```

Tại đây bạn cần lưu ý là: khi biên build msg bạn tạo ra, đường dẫn tới loại msg bạn tạo đã được chỉnh sửa. Bạn phải chỉnh đường dẫn ở include mới có thể chạy được.

```bash
NameIntNumData -> name_int_num_data.hpp
```

## Subcriber.cpp

```cpp
#include <memory>

#include <rclcpp/rclcpp.hpp>
#include <intnums/msg/name_int_num_data.hpp>


class SubcriberMsg :public rclcpp::Node{
    public:
    SubcriberMsg():Node("subcriber_msg"){
        subcription_ = this->create_subscription<intnums::msg::NameIntNumData>(
            "send_int", // Topic nhận
            10,
            std::bind
            (
                &SubcriberMsg::listener_callback, // Gọi hàm call back
                this, // Gọi cho chính đối tượng này
                std::placeholders::_1 // Đại diện cho tham số thứ nhất trong callback
            )
        );
    }
    private:
    void listener_callback(const intnums::msg::NameIntNumData & msg) const{
        RCLCPP_INFO(this->get_logger(),
        "I head name: %s, with a : %ld, b: %ld",
        msg.name.c_str(),
        msg.int_num_data.num_a,
        msg.int_num_data.num_b
        );
    }
    // Tạo con trỏ subcription_ để duy trì cho node tồn tại, nếu không nó sẽ
    // không chạy được vì sẽ chết ngay khi được chạy.
    rclcpp::Subscription<intnums::msg::NameIntNumData>::SharedPtr subcription_;
};

int main(int argc,char *argv[]){
    rclcpp::init(argc,argv);
    rclcpp::spin(std::make_shared<SubcriberMsg>());
    rclcpp::shutdown();
    return 0;
}


```

## 3. Config

### 1) package.xml

Đây là file sẽ khai báo các thư viện của ros2 và các đường dẫn được tạo riêng cho mục đích bạn dùng vào đây. Các thư viện của cpp sẽ không cần phải khai báo. Tức là bạn chỉ cần khai báo các thư viện, msg,... ở mục include "..."

Tại đây mình đang `include` các đường dẫn: `rclcpp` và msg `intnums` 

```
  <!-- Đoạn thêm -->
  <depend>rclcpp</depend>
  <depend>intnums</depend>
  <!-- Kết thúc -->
```

### 2) CMakeList.txt

Sau khi khai báo các phụ thuộc vào trong `package.xml`, ta tiếp tục cần khai báo các dependency đó trong `CMakeLists.txt` để CMake biết mà link vào quá trình build mã nguồn C++.

Trước hết ta cần tìm các package ROS2 đã khai báo ở package.xml:

```cpp
find_package(rclcpp REQUIRED)
find_package(intnums REQUIRED)
```

Tiếp theo là khai báo executable cho node của bạn

Cú pháp

```cpp
add_executable(name src/file.cpp)
# name: bạn tự đặt
```

```cpp
# Theo đó ta có
add_executable(talker src/publisher.cpp)
add_executable(listener src/subcriber.cpp)
```

Khi ROS2 build node thì nó cần link node với thư viện rclcpp và msg. Ta thực hiện thông qua câu lệnh:

```cmake
ament_target_dependencies(listener rclcpp intnums)
ament_target_dependencies(talker rclcpp intnums)
```

Sau đó khai báo install binary để nó được đưa vào workspace và có thể chạy bằng `ros2 run`:

```cmake
install(TARGETS
  talker
  listener
  DESTINATION lib/${PROJECT_NAME}
)
```

## 4. Build and Run

Sau các bước trên, bạn chạy terminal, trỏ đường dẫn ở đầu ws của bạn và gõ

```bash
colcon build
source install/setup.bash
```

```bash
ntruong1124@Javis:~/ros2_ws/Cpp/pub_and_sub$ colcon build
Starting >>> intnums
Finished <<< intnums [0.60s]
Starting >>> cpp_pubsub
Finished <<< cpp_pubsub [11.0s]

Summary: 2 packages finished [12.1s]
ntruong1124@Javis:~/ros2_ws/Cpp/pub_and_sub$ source install/setup.bash
```

> Lưu ý rằng việc build file cpp sẽ lâu hơn khá nhiều so với build file python.
> 
> Nên bạn có thể chỉ định build riêng package của mình thay vì build toàn bộ.

```bash
colcon build --packages-select your_pkg
```

Sau khi hoàn thành build và source bạn sẽ chạy với lệnh

```bash
ros2 run cpp_pubsub talker
```

Mở một terminal khác và trỏ tiếp tới ws bạn đang làm việc. 

> Lưu ý là với terminal khác bạn bắt buộc phải source install/setup.bash

```bash
ros2 run cpp_pubsub listener
```

Như vậy bạn đã được tìm hiểu về pub and sub của ros2 với cpp.
