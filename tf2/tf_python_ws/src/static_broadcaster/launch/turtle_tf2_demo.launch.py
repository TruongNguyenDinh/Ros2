from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration

from launch_ros.actions import Node


def generate_launch_description():
    return LaunchDescription([
        # Chạy node turtlesim (môi trường mô phỏng con rùa)
        Node(
            package='turtlesim',
            executable='turtlesim_node',
            name='sim'
        ),
        # Xuất bản transform (vị trí + hướng quay) của turtle1 lên TF tree
        Node(
            package='static_broadcaster',
            executable='turtle_tf2_broadcaster',
            name='broadcaster1',
            parameters=[
                {'turtlename': 'turtle1'}
            ]
        ),
        # Khai báo frame mục tiêu để turtle2 bám theo (mặc định là turtle1)
        DeclareLaunchArgument(
            'target_frame', default_value='turtle1',
            description='Target frame name.'
        ),
        # Chuẩn bị broadcaster cho turtle2
        # Transform sẽ chỉ có ý nghĩa sau khi turtle2 được spawn
        Node(
            package='static_broadcaster',
            executable='turtle_tf2_broadcaster',
            name='broadcaster2',
            parameters=[
                {'turtlename': 'turtle2'}
            ]
        ),
        # Node listener:
        # - Gọi service để spawn turtle2
        # - Lắng nghe transform giữa turtle2 và target_frame
        # - Tính toán vận tốc để turtle2 di chuyển bám theo target
        Node(
            package='static_broadcaster',
            executable='turtle_tf2_listener',
            name='listener',
            parameters=[
                {'target_frame': LaunchConfiguration('target_frame')}
            ]
        ),
    ])