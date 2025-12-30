from setuptools import find_packages, setup
import os
from glob import glob
package_name = 'static_broadcaster'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
        (os.path.join('share', package_name, 'launch'), glob('launch/*.launch.py')),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='ntruong1124',
    maintainer_email='truongnd1124@gmail.com',
    description='TODO: Package description',
    license='Apache-2.0',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'static_tf2_broadcaster = static_broadcaster.static_turtle_tf2_broadcaster:main',
            'turtle_tf2_broadcaster = static_broadcaster.turtle_tf2_broadcaster:main',
            'turtle_tf2_listener = static_broadcaster.turtle_tf2_listener:main',
            'fixed_frame_tf2_broadcaster = static_broadcaster.fixed_frame_tf2_broadcaster:main',
            'dynamic_frame_tf2_broadcaster = static_broadcaster.dynamic_frame_tf2_broadcaster:main',
            'turtle_tf2_message_broadcaster = static_broadcaster.turtle_tf2_message_broadcaster:main',
        ],
    },
)
