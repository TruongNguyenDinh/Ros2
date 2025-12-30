#include <chrono>
#include <memory>
#include <string>

#include "geometry_msgs/msg/point_stamped.hpp"
#include "message_filters/subscriber.h"
#include "rclcpp/rclcpp.hpp"
#include "tf2_ros/buffer.h"
#include "tf2_ros/create_timer_ros.h"
#include "tf2_ros/message_filter.h"
#include "tf2_ros/transform_listener.h"
#ifdef TF2_CPP_HEADERS
  #include "tf2_geometry_msgs/tf2_geometry_msgs.hpp"
#else
  #include "tf2_geometry_msgs/tf2_geometry_msgs.h"
#endif

using namespace std::chrono_literals;

class PoseDrawer : public rclcpp::Node
{
public:
  PoseDrawer()
  : Node("turtle_tf2_pose_drawer")
  {
    // Tạo ra param target_frame: với giá trị lấy mặc định là turlte1
    target_frame_ = this->declare_parameter<std::string>("target_frame", "turtle1");

    std::chrono::duration<int> buffer_timeout(1);
    // Tạo buffer để lưu trữ các transform ( truyền get_clock() ) để lưu trữ thêm thời gian
    tf2_buffer_ = std::make_shared<tf2_ros::Buffer>(this->get_clock());

    /*
    Lý do chọn timer_interface là:
    + MessageFilter cần chờ transform
    + Muốn chờ nó thì cần timer
    + Vì Ros2 không tự cấp timer cho tf2 nên ta sẽ gắn thủ công
    */
    auto timer_interface = std::make_shared<tf2_ros::CreateTimerROS>(
      this->get_node_base_interface(),
      this->get_node_timers_interface()
    );
    tf2_buffer_->setCreateTimerInterface(timer_interface);
    /*
    Lắng nghe /tf và lắng nghe /tf_static và đẩy transform vào trong buffer
    */
    tf2_listener_ =
      std::make_shared<tf2_ros::TransformListener>(*tf2_buffer_);

    /*
    Đây là một subscriber đặc biệt của message_filter không phải của rclcpp
    Không gọi callback trực tiếp nó chỉ nghe message và đưa sang cho MessageFilter
    */
    point_sub_.subscribe(this, "/turtle3/turtle_point_stamped");

    tf2_filter_ = std::make_shared<tf2_ros::MessageFilter<geometry_msgs::msg::PointStamped>>(
      point_sub_, // Nguồn message
      *tf2_buffer_, // Nơi kiểm tra transform
      target_frame_, // frame đích 
      100, // Kích thước hàng đợi
      this->get_node_logging_interface(), // Cho Ros2 ghi log
      this->get_node_clock_interface(), // Cho Ros2 ghi clock
    buffer_timeout // Chờ tối đa transform trong 1 giây
    );
    // Register a callback with tf2_ros::MessageFilter to be called when transforms are available
    // Đăng kí callback với tf2_ros::MessageFilter, Nó chỉ được gọi khi transform khả dụng
    tf2_filter_->registerCallback(&PoseDrawer::msgCallback, this);
  }

private:
 // hàm này chỉ được gọi khi tf2 đảm bảo transform đã tồn tại
  void msgCallback(const geometry_msgs::msg::PointStamped::SharedPtr point_ptr)
  {
    geometry_msgs::msg::PointStamped point_out;
    try {
      tf2_buffer_->transform(
        *point_ptr,
        point_out,
        target_frame_
        /*
        Hàm này có mục tiêu là:
        - Chuyển point trong frame world -> point trong frame turtle1
        */
    );
      RCLCPP_INFO(
        this->get_logger(), "Point of turtle3 in frame of turtle1: x:%f y:%f z:%f\n",
        point_out.point.x,
        point_out.point.y,
        point_out.point.z);
    } catch (const tf2::TransformException & ex) {
      RCLCPP_WARN(
        // Print exception which was caught
        this->get_logger(), "Failure %s\n", ex.what());
    }
  }

  std::string target_frame_;
  std::shared_ptr<tf2_ros::Buffer> tf2_buffer_;
  std::shared_ptr<tf2_ros::TransformListener> tf2_listener_;
  message_filters::Subscriber<geometry_msgs::msg::PointStamped> point_sub_;
  std::shared_ptr<tf2_ros::MessageFilter<geometry_msgs::msg::PointStamped>> tf2_filter_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<PoseDrawer>());
  rclcpp::shutdown();
  return 0;
}
/*
Luồng dữ liệu như sau:
turtle3/pose
    ↓
PointPublisher
    ↓   (PointStamped, frame=world)
----------------------------------
PoseDrawer
    ↓
message_filters::Subscriber
    ↓
MessageFilter
    ↓ (đợi tf world → turtle1 đúng thời gian)
msgCallback
    ↓
tf2_buffer.transform()
    ↓
tọa độ turtle3 trong frame turtle1
-> MessageFiler có mục đích là quyết định khi nào dữ liệu được chuyển đi
*/