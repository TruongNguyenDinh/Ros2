#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "geometry_msgs/msg/transform_stamped.hpp"
#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp" 


#include "tf2/exceptions.h"
#include "tf2_ros/transform_listener.h"
#include "tf2_ros/buffer.h"
#include "turtlesim/srv/spawn.hpp"

class FrameListenser : public rclcpp::Node{
public:
    FrameListenser(): Node("turtle_tf2_frame_listener"),
        turtle_spawn_service_ready_(false),
        turtle_spawned_(false)
    {
        // Chọn mục tiêu target
        target_frame_ = this->declare_parameter<std::string>("target_frame","turtle1");
        /*
            tf_buffer : là đối tượng sẽ lưu trữ các phép biến đổi của tf2
        */
        tf_buffer_ = std::make_unique<tf2_ros::Buffer>(this->get_clock());
        // Tạo listener
        tf_listener_ = std::make_shared<tf2_ros::TransformListener>(*tf_buffer_);
        // Tạo ra một client yêu cầu sinh ra con rùa 2
        spawner_ = this->create_client<turtlesim::srv::Spawn>("spawn");
        // Tạo ra publisher để xuất bản lệnh điều khiển con rùa 2
        publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("turtle2/cmd_vel",1);

        timer_ = this->create_wall_timer(
            std::chrono::seconds(1),
            // //Cách 1: dùng bind
            // std::bind(&FrameListenser::on_timer,this)
            // Cách 2: dùng lambda
            [this](){
                this->on_timer();
            }
        );
    }

private:
    void on_timer(){
        // Lấy tên mục tiêu
        std::string fromFrameRel = target_frame_.c_str();
        // Lấy tên đối tượng cần điều khiển
        std::string toFrameRel = "turtle2";

        if(turtle_spawn_service_ready_){
            if(turtle_spawned_){    
                geometry_msgs::msg::TransformStamped t;
                try{
                    t = tf_buffer_ ->lookupTransform(
                        toFrameRel,
                        this->get_clock()->now(),
                        fromFrameRel,
                        //tf2::TimePointZero //Ban đầu
                        this->get_clock()->now() - rclcpp::Duration(5,0), // Thử đổi sang đoạn này
                        "world",
                        std::chrono::microseconds(100)
                    );
                }
                catch(const tf2::TransformException &ex){
                    RCLCPP_INFO(this->get_logger(),
                        "could not transform %s to %s : %s",
                        fromFrameRel.c_str(),toFrameRel.c_str(),
                        ex.what()
                    );
                    return ;
                }
                
                geometry_msgs::msg::Twist msg;
                // Điều khiển góc quay

                static const double scaleRoationRate = 1.0;
                msg.angular.z = scaleRoationRate*atan2(
                    t.transform.translation.y,
                    t.transform.translation.x
                );

                double dx = t.transform.translation.x;
                double dy = t.transform.translation.y;
                static const double scaleForwardSpeed  = 0.5;
                double distance = hypot(dx, dy);
                if (distance < 0.05) {
                    msg.linear.x  = 0.0;
                    msg.angular.z = 0.0;
                }
                else {
                    msg.angular.z = 1.0 * atan2(dy, dx);
                    msg.linear.x  = scaleForwardSpeed * distance;
                }
                
                publisher_ ->publish(msg);
            }
            else{
                RCLCPP_INFO(this->get_logger(), "Successfully spawned");
                turtle_spawned_ = true;
            }
        }
        else{
            if (spawner_->service_is_ready()){
                // Khởi tạo yêu cầu sinh ra con rùa cùng với tọa độ thiết lập
                auto request = std::make_shared<turtlesim::srv::Spawn::Request>();
                request->x = 4.0;
                request->y = 3.0;
                request->theta = 0.0;
                request->name = "turtle2";

                // Gọi request
                using ServiceResponseFuture = rclcpp::Client<turtlesim::srv::Spawn>::SharedFuture;
                auto response_recieved_callback = [this](ServiceResponseFuture future){
                    auto result = future.get();
                    if(strcmp(result->name.c_str(),"turtle2")==0){
                        turtle_spawn_service_ready_ = true;
                    }
                    else{
                        RCLCPP_INFO(this->get_logger(),
                            "Service callback rasult mismatch");
                    }
                };
                auto result = spawner_->async_send_request(request,response_recieved_callback);
            }
            else{
                RCLCPP_INFO(this->get_logger(),
                    "Service is not ready");
            }
        }
    }
    bool turtle_spawn_service_ready_;
    bool turtle_spawned_ ;
    std::string target_frame_;
    std::unique_ptr<tf2_ros::Buffer> tf_buffer_;
    std::shared_ptr<tf2_ros::TransformListener> tf_listener_;
    rclcpp::Client<turtlesim::srv::Spawn>::SharedPtr spawner_;
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
};
int main(int argc, char **argv){
    rclcpp::init(argc,argv);
    rclcpp::spin(std::make_shared<FrameListenser>());
    rclcpp::shutdown();
    return 0;
}