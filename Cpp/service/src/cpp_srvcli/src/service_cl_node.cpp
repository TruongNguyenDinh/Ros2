#include "rclcpp/rclcpp.hpp"
#include "add_two_ints/srv/sum_two_nums.hpp"

class SrvClientNode : public rclcpp::Node{
public:
    SrvClientNode(): Node("srv_client_node")
    {
        client_ = this->create_client<add_two_ints::srv::SumTwoNums>("sum_two_nums"); // Gọi tên service
    }
    // Tạo hàm send_quest 
    rclcpp::Client<add_two_ints::srv::SumTwoNums>::SharedFuture send_request(int a, int b)
    {
        // Đợi máy chủ hoạt động
        while( !client_ ->wait_for_service(std::chrono::seconds(1))){
            RCLCPP_WARN(this->get_logger(),"Waiting for service !");
        }

        auto request = std::make_shared<add_two_ints::srv::SumTwoNums::Request>();
        request->a = a; // Gán cho request a = đầu vào a
        request->b = b; // Gán cho request b = đầu vào b
        
        return client_->async_send_request(request).share(); // Trả về responses
    } 
private:
    rclcpp::Client<add_two_ints::srv::SumTwoNums>::SharedPtr client_; // Duy trì cho client_ sống
};
int main(int argc, char **argv){
    rclcpp::init(argc,argv);

    if(argc != 3){
        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"),
        "User: ros2 run cpp srv client !");
        rclcpp::shutdown();
        return 1;
    }
    /* argv[0] : tên chương trình (tên file thực thi)
    Giả sử ros2 run pkg srv_client 5 7
    thì argv[0] : "srv_client"
    argv[1]	    : "5"
    argv[2]	    : "7"
    */
    int a = std::atoi(argv[1]);
    int b = std::atoi(argv[2]);

    auto node = std::make_shared<SrvClientNode>();
    auto future = node->send_request(a,b); // Đặt chỗ cho response
    /*
    Giống như bạn gửi yêu cầu mua cốc coffe. Bạn nhận được một cái túi ( ở đây là future lúc này nó rỗng)
    Nếu khi coffe được làm xong thì lúc này cái túi bạn đã chứa coffe, có thể có nhiều coffe trong túi (future đã chứa responses)
    Bạn lấy được coffe để sử dụng thì lúc này bạn sẽ nhận được response
     */
    if(rclcpp::spin_until_future_complete(node,future) == rclcpp::FutureReturnCode::SUCCESS){
        auto result = future.get(); // Lúc này future đã chứa response
        RCLCPP_INFO(node->get_logger(),"Server respone: %ld", result->sum);
    }
    else{
        RCLCPP_ERROR(node->get_logger(),"Failed to call service !");
    }
    rclcpp::shutdown();
    return 0;
}