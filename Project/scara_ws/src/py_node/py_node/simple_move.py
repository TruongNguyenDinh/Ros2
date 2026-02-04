import rclpy
from rclpy.node import Node
from trajectory_msgs.msg import JointTrajectory, JointTrajectoryPoint

class ScaraCommander(Node):
    def __init__(self):
        super().__init__('scara_commander')

        self.publisher = self.create_publisher(
            JointTrajectory,
            '/scara_arm_controller/joint_trajectory',
            10
        )

        self.timer = self.create_timer(1.0, self.send_trajectory)

    def send_trajectory(self):
        traj = JointTrajectory()
        traj.joint_names = ['joint_1', 'joint_3', 'joint_6']

        point = JointTrajectoryPoint()
        point.positions = [0.5, -0.3, 0.2]   # rad / m tùy joint
        point.time_from_start.sec = 2

        traj.points.append(point)

        self.publisher.publish(traj)
        self.get_logger().info('Trajectory sent')
        self.timer.cancel()  # gửi 1 lần thôi

def main():
    rclpy.init()
    node = ScaraCommander()
    rclpy.spin(node)
    rclpy.shutdown()

if __name__ == '__main__':
    main()
