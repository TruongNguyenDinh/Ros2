#include<memory>

#include "geometry_msgs/msg/transform_stamped.hpp"
#include "rclcpp/rclcpp.hpp"
#include "tf2/LinearMath/Quaternion.h"
#include "tf2_ros/static_transform_broadcaster.h"

class StaticFramePublisher : public rclcpp::Node
{
public:
    explicit StaticFramePublisher(char *transformation[])
    : Node("static_turtle_tf2_boardcaster")
    {
        // Khởi tạo biến 
        /*
            Tf2 sẽ mặc định tạo ra topic có tên là tf_static
        */
        tf_static_boardcaster_ = std::make_shared<tf2_ros::StaticTransformBroadcaster>(this);
        
        this->make_transforms(transformation);
    }
private:

    void make_transforms(char *transformation[]){
        // Tạo biến giao tiếp của geometry đặt là t
        geometry_msgs::msg::TransformStamped t;

        t.header.stamp = this->get_clock()->now();
        t.header.frame_id = "world";
        t.child_frame_id = transformation[1];

        t.transform.translation.x = atof(transformation[2]);
        t.transform.translation.y = atof(transformation[3]);
        t.transform.translation.z = atof(transformation[4]);

        // Chuyển từ Euler sang Quaternion
        // roll-pitch-yaw -> q_x q_y q_z q_w
        tf2::Quaternion q;
        q.setRPY(
            atof(transformation[5]),
            atof(transformation[6]),
            atof(transformation[7])           
        );
        t.transform.rotation.x = q.x();
        t.transform.rotation.y = q.y();
        t.transform.rotation.z = q.z();
        t.transform.rotation.w = q.w();

        tf_static_boardcaster_ ->sendTransform(t);
    }
    std::shared_ptr<tf2_ros::StaticTransformBroadcaster> tf_static_boardcaster_ ;
};
int main(int argc, char **argv){
    auto logger = rclcpp::get_logger("logger");
    // Check đầu vào 
    if(argc != 8 ){
        RCLCPP_INFO(
            logger,
            "Invalid number of parameters\nusage: "
            "$ ros2 run learning_tf2_cpp static_turtle_tf2_broadcaster "
            "child_frame_name x y z roll pitch yaw");
        return 1;
    }
    // Nếu tạo ra một transform có tên là world sẽ thoát
    if(strcmp(argv[1], "world") == 0){
        RCLCPP_INFO(logger, "Your static turtle name cannot be 'world'");
        return 1;
    }

    rclcpp::init(argc,argv);
    rclcpp::spin(std::make_shared<StaticFramePublisher>(argv));
    rclcpp::shutdown();
    return 0;
}