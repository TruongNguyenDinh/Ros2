from launch import LaunchDescription
from launch.actions import TimerAction, IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from ament_index_python.packages import get_package_share_directory
import os

def generate_launch_description():

    gazebo = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(
                get_package_share_directory('my_robot'),
                'launch',
                'gazebo.launch.py'
            )
        )
    )

    slam = TimerAction(
        period=6.0, 
        actions=[
            IncludeLaunchDescription(
                PythonLaunchDescriptionSource(
                    os.path.join(
                        get_package_share_directory('slam_toolbox'),
                        'launch',
                        'online_async_launch.py'
                    )
                ),
                launch_arguments={'use_sim_time': 'true'}.items()
            )
        ]
    )

    return LaunchDescription([gazebo, slam])
