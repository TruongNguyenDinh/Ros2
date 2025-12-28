#include <functional>
#include <memory>
#include <sstream>
#include <string>

#include "geometry_msgs/msg/transform_stamped.hpp"
#include "rclcpp/rclcpp.hpp"
#include "tf2/LinearMath/Quaternion.h"
#include "tf2_ros/transform_broadcaster.h"
#include "turtlesim/msg/pose.hpp"

class FramePublisher : public rclcpp::Node{
    public:
    FramePublisher(): Node("turtle_tf2_frame_broadcaster"){
        // Lấy tên con rùa
        turtlename_ = this->declare_parameter<std::string>("turtlename","turtle1");
        // Khởi tạo broadcaster
        /*
            Khởi tạo dùng unique đảm bảo:
            + tf2_broadcaster luôn luôn thuộc về một chủ sở hữu là: FramePublisher
            + Không cho phép tham chiếu đến tf2_broadcaster từ bất kì nguồn nào khác
            + Vòng đời rõ ràng, an toàn bộ nhớ vì nó sẽ sống chết với node này.
        */
        tf2_broadcaster_ = std::make_unique<tf2_ros::TransformBroadcaster>(*this);
        // Subcribe turtle{1|2}
        std::ostringstream stream;
        stream<<"/"<<turtlename_.c_str()<<"/pose";
        std::string topic_name = stream.str();
        // Tạo subcriber lắng nghe pose của con rùa
        subcription_ = this->create_subscription<turtlesim::msg::Pose>(
            topic_name,
            10,
            std::bind(&FramePublisher::handle_turtle_pose,this,std::placeholders:: _1 )
        );


    }

    private:
    void handle_turtle_pose(const std::shared_ptr<const turtlesim::msg::Pose> msg){
        // Tạo transform
        geometry_msgs::msg::TransformStamped t;
        //
        t.header.stamp = this->get_clock()->now();
        t.header.frame_id = "world"; // Cha
        t.child_frame_id = turtlename_.c_str(); // Con
        /*
            Vì con rùa nó chỉ nằm trên mặt phẳng 2D nên:
            + Chỉ đi được theo trục x và y ( z không thể )
            + Chỉ xoay được theo trục z
        */
        t.transform.translation.x = msg->x;
        t.transform.translation.y = msg->y;
        t.transform.translation.z = 0;
        // Chuyển góc quay từ Euler sang Quanternion
        tf2::Quaternion q;
        q.setRPY(0,0,msg->theta);
        t.transform.rotation.x = q.x();
        t.transform.rotation.y = q.y();
        t.transform.rotation.z = q.z();
        t.transform.rotation.w = q.w();

        // Gửi transform đi
        tf2_broadcaster_ ->sendTransform(t);

    }
    rclcpp::Subscription<turtlesim::msg::Pose>::SharedPtr subcription_;
    // Dùng unique_ptr vì TransformBroadcaster chỉ có một owner (node này)
    std::unique_ptr<tf2_ros::TransformBroadcaster> tf2_broadcaster_;
    std::string turtlename_;
};

int main(int argc, char **argv){
    rclcpp::init(argc,argv);
    rclcpp::spin(std::make_shared<FramePublisher>());
    rclcpp::shutdown();
    return 0;
}