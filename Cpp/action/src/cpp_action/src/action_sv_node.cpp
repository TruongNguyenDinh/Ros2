#include <functional>
#include <memory>
#include <thread>

#include "custom_action_interfaces/action/position_robot.hpp"
#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp"
#include "rclcpp_components/register_node_macro.hpp"

namespace cpp_action{
    class ActSvNode: public rclcpp::Node
    {
        public:
        // Tạo bí danh cho tiết kiệm thời gian
        using PositionRobot = custom_action_interfaces::action::PositionRobot;
        using GoalHandlePositionRobot = rclcpp_action::ServerGoalHandle<PositionRobot>;
        /*
        Hàm khởi tạo cho class: sử dụng explicit để tránh tự ý chuyển kiểu khi truyền vào hàm khởi tạo
        */
        explicit ActSvNode (const rclcpp::NodeOptions & option = rclcpp::NodeOptions()): Node("position_robot_action_server", option)
        {
            using namespace std::placeholders;

            action_server_ = rclcpp_action::create_server<PositionRobot>(
                this, // Trỏ vào chính nó( đại diện cho chính node hiện tại)
                "positon_robot_server", // Tên action để gọi trong terminal : ros2 action send_goal /positon_robot_server ...
                std::bind(&ActSvNode::handle_goal,this,_1,_2), //Hàm lắng nghe mục tiêu
                std::bind(&ActSvNode::handle_cancel,this,_1), // Hàm khi client hủy
                std::bind(&ActSvNode::handle_accepted,this,_1) // Hàm khi đã chấp nhận từ client
            );
            RCLCPP_INFO(this->get_logger(),"Action server ready !"); // Thông báo
        }
        private:
        rclcpp_action::Server<PositionRobot>::SharedPtr action_server_;

        // Hàm lắng nghe mục tiêu
        rclcpp_action::GoalResponse handle_goal(
            const rclcpp_action::GoalUUID & uuid, //Id của goal
            std::shared_ptr<const PositionRobot::Goal> goal) // Dữ liệu mà client gửi
        {
            RCLCPP_INFO(
                this->get_logger(),
                "Recieved goal: x=%d, y=%d",
                goal->x_goal,
                goal->y_goal
            );
            (void) uuid; // Tránh cảnh báo
            return rclcpp_action::GoalResponse::ACCEPT_AND_EXECUTE; // Chấp nhận goal và thực thi ngay
        }
        // Hàm người dùng hủy hành động
        rclcpp_action::CancelResponse handle_cancel(
            const std::shared_ptr<GoalHandlePositionRobot> goal_handle)
        {
            RCLCPP_INFO(this->get_logger(),"Goal cancel request recieved");
            (void) goal_handle;
            return rclcpp_action::CancelResponse::ACCEPT; // Cho phép hủy ngay
        }
        // Hàm chấp nhận dữ liệu
        void handle_accepted(
            const std::shared_ptr<GoalHandlePositionRobot> goal_handle)
        {
            // Gọi hàm thực thi trong một luồng khác tránh bị chặn luồng hiện tại dẫn đến treo node
            std::thread{std::bind(&ActSvNode::excute, this, goal_handle)}.detach();
        }
        // Hàm thực thi
        void excute(
            const std::shared_ptr<GoalHandlePositionRobot> goal_handle)
        {
            RCLCPP_INFO(this->get_logger(), "Excuting goal ...");

            auto feedback = std::make_shared<PositionRobot::Feedback>();
            auto result = std::make_shared<PositionRobot::Result>();

            int x_current = 0;
            int y_current = 0;

            auto goal = goal_handle->get_goal();
            int x_goal = goal->x_goal;
            int y_goal = goal->y_goal;
            
            rclcpp::Rate loop_rate(1); // 1Hz   

            while(rclcpp::ok() && (x_current != x_goal || y_current != y_goal))
            {
                if(goal_handle->is_canceling()){
                    result->is_success = false;
                    goal_handle->canceled(result);
                    RCLCPP_INFO(this->get_logger(),"Goal canceled! ");
                    return;
                }
                if(x_current < x_goal) x_current++;
                else if (x_current > x_goal) x_current--;

                if(y_current < y_goal) y_current ++;
                else if (y_current > y_goal) y_current--;

                feedback->x_current = x_current;
                feedback->y_current = y_current;

                goal_handle->publish_feedback(feedback);

                RCLCPP_INFO(
                    this->get_logger(),
                    "Feedback -x:%d | -y:%d",
                    x_current,y_current
                );
                loop_rate.sleep();
            }
            result->is_success = true;
            goal_handle->succeed(result);

            RCLCPP_INFO(
                this->get_logger(),
                "Goal succeeded! "
            );
        }
    };
}
RCLCPP_COMPONENTS_REGISTER_NODE(cpp_action::ActSvNode)