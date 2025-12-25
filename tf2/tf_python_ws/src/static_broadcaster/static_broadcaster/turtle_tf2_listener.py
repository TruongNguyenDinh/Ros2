# Copyright 2021 Open Source Robotics Foundation, Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# Đoạn mã nguồn được viết với kiểu giao tiếp service kết hợp giao tiếp qua topic
import math

from geometry_msgs.msg import Twist

import rclpy
from rclpy.node import Node

from tf2_ros import TransformException
from tf2_ros.buffer import Buffer
# Các đoạn mã nguồn trước là gửi đi phép biển đổi
from tf2_ros.transform_listener import TransformListener # Lắng nghe biến đổi

from turtlesim.srv import Spawn # Loại service


class FrameListener(Node):

    def __init__(self):
        super().__init__('turtle_tf2_frame_listener')

        # Declare and acquire `target_frame` parameter
        # Tạo ra param có tên là target_fram với giá trị khởi tạo là turtle1
        self.target_frame = self.declare_parameter(
            'target_frame', 'turtle1').get_parameter_value().string_value

        self.tf_buffer = Buffer() # Bộ nhớ lưu chữ các transform (TF)
        self.tf_listener = TransformListener(self.tf_buffer, self)

        # Create a client to spawn a turtle
        # Tạo client yêu cầu sinh ra con rùa
        self.spawner = self.create_client(Spawn, 'spawn')
        # Boolean values to store the information
        # if the service for spawning turtle is available
        # Đặt cờ hiệu để biết nếu service sinh con rùa đã sẵn sang chạy
        self.turtle_spawning_service_ready = False
        # if the turtle was successfully spawned
        # Cờ hiệu để biết con rùa đã sinh ra chưa ?
        self.turtle_spawned = False

        # Create turtle2 velocity publisher
        self.publisher = self.create_publisher(Twist, 'turtle2/cmd_vel', 1)

        # Call on_timer function every second
        self.timer = self.create_timer(1.0, self.on_timer)

    def on_timer(self):
        # Store frame names in variables that will be used to
        # compute transformations
        from_frame_rel = self.target_frame # Frame cần theo (mục tiêu)
        to_frame_rel = 'turtle2' # Frame rùa đang ở

        if self.turtle_spawning_service_ready: # Kiểm tra service đã sẵn sàng chưa ? 
            if self.turtle_spawned: # Kiểm tra con rùa 2 đã được tạo chưa ? 
                # Look up for the transformation between target_frame and turtle2 frames
                # and send velocity commands for turtle2 to reach target_frame
                try:
                    t = self.tf_buffer.lookup_transform(
                        to_frame_rel,
                        from_frame_rel,
                        rclpy.time.Time())
                    # Lấy transform của turtle1 ->target_frame (ở đây là lấy vector)
                # Nếu chưa có transfrom thì log lỗi và thoát hàm on_timer  
                except TransformException as ex:
                    self.get_logger().info(
                        f'Could not transform {to_frame_rel} to {from_frame_rel}: {ex}')
                    return
                # Quá trình điều khiển con rùa

                msg = Twist() # Tạo lệnh điều khiển vận tốc
                scale_rotation_rate = 1.0 # Hệ số khuyếch đại ( tốc độ phản ứng góc khi target thay đổi hướng đi)
                msg.angular.z = scale_rotation_rate * math.atan2(
                    t.transform.translation.y,
                    t.transform.translation.x
                # Góc cân quay là atan2(y,x), đảm bảo con rùa sẽ luôn hướng về target    
                )
                # Vận tốc tối đa
                scale_forward_speed = 0.5
                msg.linear.x = scale_forward_speed * math.sqrt(
                    t.transform.translation.x ** 2 +
                    t.transform.translation.y ** 2
                #Công thức: distance = sqrt(x^2 +y^2)
                )
                # Xuất bản thông cho tới /turtl2/cmd_vel để điều khiển
                self.publisher.publish(msg)
            # Kiểm tra service nếu chưa spawn 
            else:
                if self.result.done():
                    self.get_logger().info(
                        f'Successfully spawned {self.result.result().name}')
                    self.turtle_spawned = True
                else:
                    self.get_logger().info('Spawn is not finished')
        # Nếu CHƯA gửi request spawn
        else:
            if self.spawner.service_is_ready():
                # Initialize request with turtle name and coordinates
                # Note that x, y and theta are defined as floats in turtlesim/srv/Spawn
                request = Spawn.Request()
                request.name = 'turtle2'
                request.x = 4.0 # Tọa độ x ngay khi được Spawn
                request.y = 2.0 # Tọa độ y ngay khi được Spawn
                request.theta = 0.0 # Góc hướng

                # Call request
                self.result = self.spawner.call_async(request)
                self.turtle_spawning_service_ready = True
            else:
                # Check if the service is ready
                self.get_logger().info('Service is not ready')


def main():
    rclpy.init()
    node = FrameListener()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass

    rclpy.shutdown()
