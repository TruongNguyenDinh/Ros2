import rclpy
from rclpy.node import Node
# Type of message
from std_msgs.msg import String
# Draw
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import threading
import sys
class GraphDebugNode(Node):
    def __init__(self, topic):
        super().__init__('graph_debug_node')
        
        self.sub_ = self.create_subscription(
            String, # Msg type
            topic, # Topic name
            self.sub_callback,
            10 # queue
        )
        # Initial data to draw
        self.data = []
        self.max_len = 100
        self.fig, self.ax = plt.subplots()
        self.line, = self.ax.plot([], [], 'r-')
        self.ax.set_xlim(0, self.max_len)
        self.ax.set_ylim(0, 10)
    
    def sub_callback(self, msg):
        try:
            value = float(msg.data)
            self.data.append(value)
            if len(self.data) > self.max_len:
                self.data.pop(0)
        except ValueError:
            self.get_logger().warning(f'Cannot convert {msg.data} to float')

    def update_plot(self, frame):
        if self.data:
            self.ax.set_ylim(min(self.data)-1, max(self.data)+1)
        self.line.set_data(range(len(self.data)), self.data)
        return self.line,

    def start_plot(self):
        ani = animation.FuncAnimation(self.fig, self.update_plot, interval=100)
        plt.show()  # chạy trên main thread

def main(args=None):
    rclpy.init(args=args)
    if len(sys.argv) < 2:
        print("Usage: ros2 run package_name graph_debug_node <topic_name>")
        return
    topic = sys.argv[1]
    node = GraphDebugNode(topic)

    # Spin ROS2 node trong thread riêng
    t = threading.Thread(target=rclpy.spin, args=(node,), daemon=True)
    t.start()

    # Chạy Matplotlib GUI trên main thread
    node.start_plot()  # sẽ gọi plt.show() và giữ main thread

    # Sau khi đóng GUI, shutdown ROS2
    node.destroy_node()
    rclpy.shutdown()

if __name__ == "__main__":
    main()
