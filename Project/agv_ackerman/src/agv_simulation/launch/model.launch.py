import os

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration, Command
from launch_ros.actions import Node
from launch_ros.parameter_descriptions import ParameterValue


def generate_launch_description():
    use_sim_time = LaunchConfiguration('use_sim_time')

    pkg_path = get_package_share_directory('agv_simulation')
    # ĐƯỜNG DẪN TỚI FILE MÔ TẢ ROBOT
    xacro_file = os.path.join(pkg_path, 'description', 'agv_sim.urdf.xacro')
    # ĐƯỜNG DẪN TỚI FILE RVIZ 
    rviz_config_path = os.path.join(pkg_path, 'rviz', 'simulation.rviz')

    robot_description = ParameterValue(
        Command(['xacro ', xacro_file]),
        value_type=str
    )

    return LaunchDescription([

        DeclareLaunchArgument(
            'use_sim_time',
            default_value='false',
            description='Use simulation (Gazebo) clock if true'
        ),
        # Joint State Publisher (GUI)
        Node(
            package='joint_state_publisher_gui',
            executable='joint_state_publisher_gui',
            name='joint_state_publisher_gui',
            output='screen'
        ),
        Node(
            package='robot_state_publisher',
            executable='robot_state_publisher',
            output='screen',
            parameters=[{
                'robot_description': robot_description,
                'use_sim_time': use_sim_time
            }]
        ),
        # RViz2
        Node(
            package='rviz2',
            executable='rviz2',
            name='rviz2',
            output='screen',
            # TRUYỀN CONFIG RVIZ NGAY KHI MỞ NÓ RA
            arguments=['-d', rviz_config_path],
            parameters=[{'use_sim_time': use_sim_time}]
        )

    ])