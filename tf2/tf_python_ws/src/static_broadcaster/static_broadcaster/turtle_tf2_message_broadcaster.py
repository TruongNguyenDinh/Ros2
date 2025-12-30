from geometry_msgs.msg import PointStamped
from geometry_msgs.msg import Twist

import rclpy
from rclpy.node import Node

from turtlesim.msg import Pose
from turtlesim.srv import Spawn

class PointPublisher(Node):
    def __init__ (self):
        super().__init__("turtle_tf2_message_broadcaster")

        # Tạo client để sinh ra con rùa
        self.spawner_ = self.create_client(Spawn,'spawn')
        # Tạo ra cờ hiệu để biết srv và con rùa được tạo chưa ?
        self.turtle_spawning_service_ready_ = False
        self.turtle_spawned_ = False
        # Nếu topic của turtle3 được subcribed
        self.turtle_pose_cansubcribe_ = False
        # Gọi hàm on_timer
        self.timer = self.create_timer(1.0,self.on_timer)
    
    def on_timer(self):
        if self.turtle_spawning_service_ready_:
            if self.turtle_spawned_:
                self.turtle_pose_cansubcribe_ = True
            else:
                if self.result.done():
                    self.get_logger().info(
                        f'Successfully spawned {self.result.result().name}'
                    )
                    self.turtle_spawned_= True
                else:
                    self.get_logger().info("Spawn is not finished")
        else:
            if self.spawner_.service_is_ready():
                # Tạo request để spawn con rùa trong hệ tọa độ
                request = Spawn.Request()
                request.name = "turtle3"
                request.x = 4.0
                request.y = 2.0
                request.theta = 0.0
                # Gọi request
                self.result = self.spawner_.call_async(request)
                self.turtle_spawning_service_ready_ = True
            else:
                # Trường hợp service ko hoạt động
                self.get_logger().info("Service is not ready")
        if  self.turtle_pose_cansubcribe_:
            self.vel_pub = self.create_publisher(Twist,'turtle3/cmd_vel',10)
            self.sub = self.create_subscription(Pose,"turtle3/pose",self.handle_turtle_pose,10)
            self.pub = self.create_publisher(PointStamped,'turtle3/turtle_point_stamped',10)

    def handle_turtle_pose(self,msg):
        vel_msg = Twist()
        vel_msg.linear.x = 1.0
        vel_msg.angular.z = 1.0
        self.vel_pub.publish(vel_msg)

        ps =PointStamped()
        ps.header.stamp = self.get_clock().now().to_msg()
        ps.header.frame_id = "world"
        ps.point.x = msg.x
        ps.point.y = msg.y
        ps.point.z = 0.0
        self.pub.publish(ps)

def main(args = None):
    rclpy.init(args=args)
    node = PointPublisher()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    rclpy.shutdown
# Đoạn mã trên có mục tiêu giả lập cảm biến gửi dữ liệu đi
# Nó đã thực hiện các vấn đề sau
# + Nó tạo ra con rùa có tên là "turtle3" với tọa độ thiết lập sẵn
# + Điều khiển con rùa chạy thông qua topic cmd_vel
# + Phát đi dữ liệu về vị trí của con rùa so với world ( Mô phỏng dữ liệu từ cảm biển gửi đi) thông qua PointStamped
# PointStamped bao gồm:
# + Thời gian gửi
# + Tọa độ lấy làm mốc
# + Vị trí của con rùa theo thời gian lấy mẫu

# Giải thích:
# Cơ bản các cảm biến khi gửi dữ liệu đi thì sẽ luôn gửi kèm theo thời gian gửi
# Chính vì thế node này có công dụng là mô phỏng cảm biến gửi dữ liệu thôi