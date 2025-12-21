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

    rclcpp::Subscription<intnums::msg::NameIntNumData>::SharedPtr subcription_;
};

int main(int argc,char *argv[]){
    rclcpp::init(argc,argv);
    rclcpp::spin(std::make_shared<SubcriberMsg>());
    rclcpp::shutdown();
    return 0;
}
