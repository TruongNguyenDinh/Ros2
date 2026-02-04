import os

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, RegisterEventHandler
from launch.substitutions import LaunchConfiguration, Command
from launch.event_handlers import OnProcessStart
from launch_ros.actions import Node
from launch_ros.parameter_descriptions import ParameterValue


def generate_launch_description():
    use_sim_time = LaunchConfiguration('use_sim_time')

    pkg_path = get_package_share_directory('scara_robot')
    xacro_file = os.path.join(pkg_path, 'description', 'scara.urdf.xacro')
    # file mô tả robot
    robot_description = ParameterValue(
        Command(['xacro ', xacro_file]),
        value_type=str
    )
    # file control
    control_node = Node(
        package="controller_manager",
        executable="ros2_control_node",
        parameters=[
            {"robot_description": robot_description},
            os.path.join(pkg_path, "config", "controllers.yaml")
        ],
        output="screen",
    )
    # broadcaster cho các khớp 
    joint_state_broadcaster_spawner = Node(
        package="controller_manager",
        executable="spawner",
        arguments=["joint_state_broadcaster"],
    )
    # controller cho robot
    scara_arm_controller_spawner = Node(
        package="controller_manager",
        executable="spawner",
        arguments=["scara_arm_controller"],
    )

    return LaunchDescription([

        DeclareLaunchArgument(
            'use_sim_time',
            default_value='false',
            description='Use simulation (Gazebo) clock if true'
        ),  
        # Tắt node này đi khi điều khiển để tránh xung đột điều khiển
        #   khiến cho tay máy bị nhảy vị trí.
        # Node(
        #     package='joint_state_publisher_gui',
        #     executable='joint_state_publisher_gui',
        #     parameters=[{'use_sim_time': use_sim_time}]
        # ),
        # Xuất bản trạng thái của robot
        Node(
            package='robot_state_publisher',
            executable='robot_state_publisher',
            parameters=[{
                'robot_description': robot_description,
                'use_sim_time': use_sim_time
            }]
        ),
        # Node control
        control_node,
        # Sinh ra boardcaster và controller cho robot từ control_node
        RegisterEventHandler(
            OnProcessStart(
                target_action=control_node,
                on_start=[
                    joint_state_broadcaster_spawner,
                    scara_arm_controller_spawner,
                ],
            )
        ),
        # Khởi động rviz2
        Node(
            package='rviz2',
            executable='rviz2',
            name='rviz2'
        ),
    ])
