import rclpy
import numpy as np
import math
from rclpy.node import Node
from trajectory_msgs.msg import JointTrajectory, JointTrajectoryPoint

class ScaraDrawsALine(Node):
    def __init__(self):
        super().__init__('scara_draws_a_line')

        self.publisher_ = self.create_publisher(
            JointTrajectory,
            '/scara_arm_controller/joint_trajectory',
            10
        )

        # ==== ĐIỂM A & B (bạn có thể đổi thành input sau) ====
        self.A = np.array([0.3, 0.1, 0.05])
        self.B = np.array([0.2, 0.3, 0.05])

        self.publish_trajectory()
    def scara_ik(self,t1,t2,d3):
        pass
    def publish_trajectory(self):
        traj = JointTrajectory()
        traj.joint_names = [
            'joint1',
            'joint2',
            'joint3'
        ]

        num_points = 50
        duration = 5.0  # giây

        for i in range(num_points + 1):
            alpha = i / num_points
            p = (1 - alpha) * self.A + alpha * self.B

            theta1, theta2, d3 = self.scara_ik(p[0], p[1], p[2])

            point = JointTrajectoryPoint()
            point.positions = [theta1, theta2, d3]
            point.time_from_start.sec = int(alpha * duration)
            point.time_from_start.nanosec = int(
                (alpha * duration % 1) * 1e9
            )

            traj.points.append(point)

        self.publisher_.publish(traj)
        self.get_logger().info('Trajectory published!')

def main(args=None):
    rclpy.init(args=args)
    node = ScaraDrawsALine()
    rclpy.spin_once(node, timeout_sec=1)
    node.destroy_node()
    rclpy.shutdown()
