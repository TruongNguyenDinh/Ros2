#include <chrono>
#include <functional>
#include <string>

#include "rclcpp/rclcpp.hpp"

class ParamNode : public rclcpp::Node{
public:
    ParamNode() : Node("param_node"){
        /*
        Tạo một param có tên là : my_param
        Giá trị mặc định là : world
        Thêm một mô tả: This parameter is mine
         */
        auto param_desc = rcl_interfaces::msg::ParameterDescriptor{}; // Tạo mô tả cho param
        param_desc.description = "This parameter is mine";
        this->declare_parameter("my_param","world",param_desc);
        timer_ = this->create_wall_timer(
            std::chrono::seconds(1),
            std::bind(&ParamNode::timer_callback,
            this)
       );
    }
private:
    void timer_callback(){
        std::string my_param = this->get_parameter("my_param").as_string();
        RCLCPP_INFO(this->get_logger(),"HELLO %s ", my_param.c_str());

        std::vector<rclcpp::Parameter> all_new_parameters {rclcpp::Parameter{"my_param","world"}};
        this->set_parameters(all_new_parameters);
    }
    rclcpp::TimerBase::SharedPtr timer_;
};
int main(int argc, char ** argv){
    rclcpp::init(argc,argv);

    rclcpp::spin(std::make_shared<ParamNode>());

    rclcpp::shutdown();

    return 0;
}