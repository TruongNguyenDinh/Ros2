from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch.substitutions import PathJoinSubstitution
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare


def generate_launch_description():
    return LaunchDescription([
        IncludeLaunchDescription(
            PathJoinSubstitution([
                FindPackageShare('static_broadcaster'), 'launch', 'turtle_tf2_demo.launch.py']),
            launch_arguments={'target_frame': 'carrot1'}.items(), 
            # Đổi target tức là 
            #con rùa 2 sẽ bám theo củ carot thay vì con rùa 1
        ),
        Node(
            package='static_broadcaster',
            executable='dynamic_frame_tf2_broadcaster',
            name='dynamic_broadcaster',
        ),
    ])