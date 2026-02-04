import rclpy
from rclpy.node import Node
from rclpy.action import ActionServer
import time
import math
from sensor_msgs.msg import JointState

from trajectory_msgs.msg import JointTrajectory, JointTrajectoryPoint
# path to action 
from action_interfaces.action import PathToGoal

class Excutor(Node):
    def __init__(self):
        super.__init__('excutor')
        
        # hardcore param a1 a2
        self.a1 = 1
        self.a2 = 1
        self.d0 = 1.75
        self.theta2_prev = 0.0
        self.joint_state_ready = False

        # Init action server
        self.action_server_ = ActionServer(
            self,
            PathToGoal,
            'getposes',
            self.execute_callback  
        )

        #Init msg 
        self.joint_state_sub = self.create_subscription(
            JointState,
            '/joint_states',
            self.joint_state_cb,
            10
        )
        # Init publisher
        self.publisher = self.create_publisher(
            JointTrajectory,
            '/scara_arm_controller/joint_trajectory',
            10
        )
        
    # Lấy vị trí theta2 hiện tại
    def joint_state_cb(self, msg):
        if 'joint3' not in msg.name:
            return

        idx = msg.name.index('joint3')
        self.theta2_prev = msg.position[idx]
        self.joint_state_ready = True

    def ik_func(self, path_x, path_y, path_z):
        path = []

        theta2_prev = self.theta2_prev

        for i in range(len(path_x)):
            x = path_x[i]
            y = path_y[i]

            c2 = (x*x + y*y - self.a1*self.a1 - self.a2*self.a2) / (2*self.a1*self.a2)
            c2 = max(-1.0, min(1.0, c2))

            t2a =  math.acos(c2)
            t2b = -math.acos(c2)

            theta2 = t2a if abs(t2a - theta2_prev) < abs(t2b - theta2_prev) else t2b
            theta2_prev = theta2

            theta1 = math.atan2(y, x) - math.atan2(
                self.a2*math.sin(theta2),
                self.a1 + self.a2*math.cos(theta2)
            )

            d2 = self.d0 - path_z[i]

            path.append((theta1, theta2, d2))

        self.theta2_prev = theta2_prev
        return path

    def execute_callback(self, goal_handle):
        #Init Feedback and Result
        feedback_msg = PathToGoal.Feedback()
        result = PathToGoal.Result()

        self.get_logger().info("Executing goal...")

        if not self.joint_state_ready:
            self.get_logger().warn("No joint state!")
            goal_handle.abort()
            result.is_success = False
            return result

        path_x = goal_handle.request.path_x
        path_y = goal_handle.request.path_y
        path_z = goal_handle.request.path_z

        ik_path = self.ik_func(path_x, path_y, path_z)

        traj = JointTrajectory()
        traj.joint_names = ['joint_1', 'joint_3', 'joint_6']

        total = len(ik_path)
        time_from_start = 0.0
        for i,p in enumerate(ik_path):
            point = JointTrajectoryPoint()
            point.positions = [p[0], p[1], p[2]]
            point.time_from_start.sec = int(time_from_start)
            point.time_from_start.nanosec = int((time_from_start % 1) * 1e9)
            time_from_start += 0.1
            traj.points.append(point)
            # Feedback
            feedback_msg.progress = float(i + 1) / total
            feedback_msg.current_joint = [p[0], p[1], p[2]]
            goal_handle.publish_feedback(feedback_msg)

        self.publisher.publish(traj)
        self.get_logger().info("Trajectory published")

        goal_handle.succeed()
        
        result.is_success = True
        return result
