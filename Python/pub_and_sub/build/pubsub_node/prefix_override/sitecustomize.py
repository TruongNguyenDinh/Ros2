import sys
if sys.prefix == '/usr':
    sys.real_prefix = sys.prefix
    sys.prefix = sys.exec_prefix = '/home/ntruong1124/ros2_ws/Python/pub_and_sub/install/pubsub_node'
