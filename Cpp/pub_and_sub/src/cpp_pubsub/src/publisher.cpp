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
        timer_ = this->create_wall_timer
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