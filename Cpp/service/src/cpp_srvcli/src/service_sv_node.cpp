#include "rclcpp/rclcpp.hpp"
#include "add_two_ints/srv/sum_two_nums.hpp"

#include <memory>

class SrvServerNode : public rclcpp::Node {
public:

    SrvServerNode() : Node("srv_server_node")
    {
        // Tạo máy chủ dịch vụ
        server_ = this->create_service<add_two_ints::srv::SumTwoNums>(
            "sum_two_nums", //Tên máy chủ của dịch vụ
            std::bind(
            &SrvServerNode::callbackSum, // Gọi callback để lắng nghe client
            this, // Trỏ chính đối tượng này
            std::placeholders::_1, // Đại diện cho tham số 1 (là request)
            std::placeholders::_2 // Đại diện cho tham số 2 (là response)
            )
        );

        RCLCPP_INFO(this->get_logger(), "Server is ready.");
    }

private:

    // callback when service request received
    void callbackSum(
        const std::shared_ptr<add_two_ints::srv::SumTwoNums::Request> request, // Tham số của request
        std::shared_ptr<add_two_ints::srv::SumTwoNums::Response> response // Tham số của response
    ){
        response->sum = request->a + request->b; // Lấy sum = a + b

        RCLCPP_INFO(
            this->get_logger(),
            "Incoming request: %ld + %ld = %ld",
            request->a, request->b, response->sum
        );
    }

    rclcpp::Service<add_two_ints::srv::SumTwoNums>::SharedPtr server_;
};


int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);

    auto node = std::make_shared<SrvServerNode>();

    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
