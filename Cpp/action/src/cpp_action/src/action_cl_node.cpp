#include <functional>
#include<future>
#include<memory>
#include<string>

#include "custom_action_interfaces/action/position_robot.hpp"

#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp"
#include "rclcpp_components/register_node_macro.hpp"

namespace cpp_action{
    class AtcClNode : public rclcpp::Node{
        //
        public:
        // Ngắn gọn cho loại action 
        using RobotPosition = custom_action_interfaces::action::PositionRobot;
        // Tạo đối tượng đại diện cho goal cụ thể mà client gửi
        /*
        Nó cho biết:
        + Được accept hay không ?
        + Theo dõi tiến trình ( feedback từ server)
        + Hùy goal ( trong trường hợp có gửi tín hiệu hủy từ client)
        */
        using GoalHandleRobotPosition = rclcpp_action::ClientGoalHandle<RobotPosition>;
        
        // Tạo hàm khởi tạo an toàn
        explicit AtcClNode(const rclcpp::NodeOptions & options) : Node ("action_client_node",options)
        {
            // Tạo param với số mặc định là 0
            this->declare_parameter<int>("x_goal",0);
            this->declare_parameter<int>("y_goal",0);

            this->client_ = rclcpp_action::create_client<RobotPosition>(
                this, // Trỏ vào chính nó
                "positon_robot_server" // Tên action
            );
            // Tạo callback gửi goal
            timer_ = this->create_wall_timer(
                std::chrono::seconds(1),
                [this](){
                    int x = this->get_parameter("x_goal").as_int();
                    int y = this->get_parameter("y_goal").as_int();
                    if (x == 0 && y == 0) {
                        RCLCPP_WARN(this->get_logger(), "Goal is (0,0), ignoring...");
                        return;
                    }
                    send_goal(x,y);
                }
            );
        }

        void send_goal(int x_goal,int y_goal){
            // Hủy timer đang chạy, không gọi callback nữa để tránh gửi goal liên tục
            this->timer_ -> cancel();
            if(!this->client_->wait_for_action_server(std::chrono::seconds(2))){
                RCLCPP_ERROR(this->get_logger(),"Action server not available after waiting! ");
                rclcpp::shutdown();
            }
            else{
                RCLCPP_INFO(this->get_logger(),"Sending goal...");
            }
            // Tạo goal msg
            auto goal_msg = RobotPosition::Goal();
            goal_msg.x_goal = x_goal;
            goal_msg.y_goal = y_goal;
            // Tao các lựa chọn gửi
            /* Bao gồm : 
            goal_response_callback  : Server accepted / Reject (1)
            feedback_callback       : Server gửi feedback      (2)
            result_callback         : Server kết thúc action   (3)
            */
            auto send_goal_options = rclcpp_action::Client<RobotPosition>::SendGoalOptions();
            // (1)
            send_goal_options.goal_response_callback = [this](const GoalHandleRobotPosition::SharedPtr & goal_handle)
            {
                if(!goal_handle){
                    RCLCPP_ERROR(this->get_logger(),"Goal was rejected by server! ");
                }
                else{
                    RCLCPP_INFO(this->get_logger(),"Goal accepted by server, waithing for result!");
                }
            };
            // (2)
            send_goal_options.feedback_callback = [this]
            (
                GoalHandleRobotPosition::SharedPtr,
                const std::shared_ptr<const RobotPosition::Feedback> feedback)
            {
                RCLCPP_INFO(
                    this->get_logger(),
                    "Your current position robot: x:%d, y:%d",
                    feedback->x_current,
                    feedback->y_current
                );
                
            };
            // (3)
            send_goal_options.result_callback = [this](const GoalHandleRobotPosition::WrappedResult & result)
            {
                switch (result.code){
                    case rclcpp_action::ResultCode::SUCCEEDED: // Server nhận được thì thoát switch
                        break;
                    case rclcpp_action::ResultCode::ABORTED: // Goal bị phá thì thoát luôn 
                        RCLCPP_ERROR(this->get_logger(),"Goal was aborted !");
                        return;
                    case rclcpp_action::ResultCode::CANCELED:
                        RCLCPP_ERROR(this->get_logger(),"Goal was canceled !");
                        return;
                    default:
                        RCLCPP_INFO(this->get_logger(),"Unknow result code ?");
                        return;
                }
                if(result.result->is_success){
                    RCLCPP_INFO(this->get_logger(),"Done ");
                }
                else{
                    RCLCPP_INFO(this->get_logger(),"False!");
                }
                // Hủy node khi đã nhận được result
                rclcpp::shutdown();
            };
            // Gửi bất đồng bộ:
            /*
            Trong đó:
            + gửi goal
            + nhận feedback
            + gọi callback
            */
            this->client_ ->async_send_goal(goal_msg,send_goal_options);

        }
        private:
        rclcpp_action::Client<RobotPosition>::SharedPtr client_;
        rclcpp::TimerBase::SharedPtr timer_;
    };
}
RCLCPP_COMPONENTS_REGISTER_NODE(cpp_action::AtcClNode);
// form: ros2 run cpp_action action_client_exec \ --ros-args -p x_goal:=5 -p y_goal:=3
