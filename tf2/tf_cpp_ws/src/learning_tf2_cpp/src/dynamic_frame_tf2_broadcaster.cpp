#include <memory>
#include <chrono>

#include "geometry_msgs/msg/transform_stamped.hpp"
#include "rclcpp/rclcpp.hpp"
#include "tf2_ros/transform_broadcaster.h"
#include "tf2/LinearMath/Quaternion.h"

#define PI 3.14

class DynamicFrameBroadcaster : public rclcpp::Node{
    public:
    DynamicFrameBroadcaster() : Node ("dynamic_frame_tf2_broadcaster"){
        tf_broadcaster_ = std::make_shared<tf2_ros::TransformBroadcaster>(this);
        timer_= this->create_wall_timer(
            std::chrono::seconds(1),
            [this](){
                this->broadcast_timer_callback();
            }
        );
    }

    private:
    void broadcast_timer_callback(){
        geometry_msgs::msg::TransformStamped t;
        
        t.header.stamp = this->get_clock()->now();
        t.header.frame_id = "turtle1";
        t.child_frame_id = "carrot1";

        double x = this->get_clock()->now().seconds()* PI;
        t.transform.translation.x = 5 * sin(x);
        t.transform.translation.y = 5 * cos(x);
        t.transform.translation.z = 0;
        tf2::Quaternion q; q.setRPY(0.0,0.0,0.0);
        t.transform.rotation.x = q.x();
        t.transform.rotation.y = q.y();
        t.transform.rotation.z = q.z();
        t.transform.rotation.w = q.w();

        tf_broadcaster_ ->sendTransform(t);
    }
    std::shared_ptr<tf2_ros::TransformBroadcaster> tf_broadcaster_;
    rclcpp::TimerBase::SharedPtr timer_;
};
int main(int argc, char ** argv){
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<DynamicFrameBroadcaster>());
    rclcpp::shutdown();
    return 0;
}