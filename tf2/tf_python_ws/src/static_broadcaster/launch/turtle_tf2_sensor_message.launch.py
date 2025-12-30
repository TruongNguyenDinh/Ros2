from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        DeclareLaunchArgument(
            "target_frame",
            default_value="turlte1",
            description = "Target frame name"
        ),
        Node(
            package="turtlesim",
            executable="turtlesim_node",
            name="sim"
        ),
        Node(
            package="static_broadcaster",
            executable="turtle_tf2_broadcaster",
            name="broadcaster1",
            parameters=[
                {"turtlename":"turtle1"}
            ]
        ),
        Node(
            package="static_broadcaster",
            executable="turtle_tf2_broadcaster",
            name="broadcaster1",
            parameters=[
                {"turtlename":"turtle3"}
            ]
        ),
        Node(
            package='static_broadcaster',
            executable='turtle_tf2_message_broadcaster',
            name='message_broadcaster',
        ),
    ])