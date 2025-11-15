import rclpy
from rclpy.node import Node
'''
ros2 node yêu cầu một luồng chạy để spin => blocking
tkinter cũng cần một luồng để chạy loop => blocking
như vậy ta cần phải dùng đa luồng để tkinter và ros2 node không chặn lẫn nhau
'''
import threading # đa luồng
import tkinter as tk # thư viện gui
import random
# Gọi service
from cmake_service.srv import GoalPos
# 
turtle_node = None

# ================== ROS2 Node ==================
class TurtleGridNode(Node):
    def __init__(self):
        # Tạo node name
        super().__init__("turtle_grid_node")
        self.get_logger().info("TurtleGridNode khởi tạo xong!")
        # Khởi tạo client service
        self.cli = self.create_client(
            GoalPos, # Loại service
            'goal_pos', #Đặt tên service
        )
        # Kiểm tra kết nối 
        # -nếu server mà nó đang lắng nghe chưa hoạt động thì chờ và ghi log 
        # -nếu server hoạt động thì sẽ thực hiện việc đẩy request
        if not self.cli.wait_for_service(timeout_sec=1.0):
            self.get_logger().info("Waiting server...")
        # Tạo đối tượng để gửi yêu cầu
        self.req = GoalPos.Request()
    def send_request(self,goalx,goaly):
        self.req.goal_x = goalx
        self.req.goal_y = goaly
    
        #Gửi request đi
        return self.cli.call_async(self.req)
    

# ================== Tkinter GUI ==================
rows = cols = 10
cell_width = cell_height = 40
grid = [[0 for _ in range(cols)] for _ in range(rows)]

def draw_grid(r, c):
    global rows, cols, cell_width, cell_height, grid
    rows, cols = r, c
    if len(grid) != rows or len(grid[0]) != cols:
        grid[:] = [[0 for _ in range(cols)] for _ in range(rows)]
    canvas.delete("all")
    canvas_width = canvas.winfo_width()
    canvas_height = canvas.winfo_height()
    # Tính toán lại kích thước dài, rộng cho cell
    cell_width = canvas_width / cols
    cell_height = canvas_height / rows

    for i in range(rows):
        for j in range(cols):
            x1 = j * cell_width
            y1 = i * cell_height
            x2 = x1 + cell_width
            y2 = y1 + cell_height

            if grid[i][j] == 1:
                fill_color = "blue"
            elif grid[i][j] == 2:
                fill_color = "red"
            else:
                fill_color = "white"

            canvas.create_rectangle(x1, y1, x2, y2, fill=fill_color, outline="black")
# Tạo đích
def on_left_click(event):
    global last_goal_x,last_goal_y
    col = int(event.x // cell_width)
    row = int(event.y // cell_height)

    if row >= rows or col >= cols:
        return

    # đánh dấu là đích
    grid[row][col] = 2  
    draw_grid(rows, cols)

    # tính tọa độ tâm của ô
    center_x = col * cell_width + cell_width / 2
    center_y = row * cell_height + cell_height / 2
    last_goal_x = center_x
    last_goal_y = center_y
    print("Click ô:", row, col)
    print("Tâm X =", center_x, " | Tâm Y =", center_y)
#Tạo tường thủ công
def on_right_click(event):
    col = int(event.x // cell_width)
    row = int(event.y // cell_height)
    if row >= rows or col >= cols:
        return
    grid[row][col] = 0 if grid[row][col] == 1 else 1
    draw_grid(rows, cols)
# Tạo tường ngẫu nhiên
def generate_walls(prob=0.2):
    for i in range(rows):
        for j in range(cols):
            if grid[i][j] == 0:
                grid[i][j] = 1 if random.random() < prob else 0
    draw_grid(rows, cols)
# Hiển thị menu
def show_menu(event):
    menu.post(event.x_root, event.y_root)

def on_canvas_resize(event):
    draw_grid(rows, cols)

#Gửi đích
def send_goal():
    if last_goal_x is None or last_goal_y is None:
        print("Chưa chọn ô để gửi goal!")
        return

    print("Gửi goal:", last_goal_x, last_goal_y)
    turtle_node.send_request(last_goal_x, last_goal_y)


# ================== GUI Thread ==================
def gui_thread():
    global root, canvas, menu
    root = tk.Tk()
    root.title("Grid Selector")
    root.attributes('-fullscreen', True)  # chiếm toàn màn hình

    # Bên trái
    left_frame = tk.Frame(root, width=200, bg="#ddd")
    left_frame.pack(side=tk.LEFT, fill=tk.Y)
    left_frame.pack_propagate(False)
    # Nút chọn lưới
    btn = tk.Button(left_frame, text="Chọn kích thước lưới", font=("Arial", 14))
    btn.pack(pady=10)
    btn.bind("<Button-1>", show_menu)
    # Nút tạo tường
    btn_wall = tk.Button(left_frame, text="Tạo tường ngẫu nhiên", font=("Arial", 14), command=lambda: generate_walls(0.2))
    btn_wall.pack(pady=10)
    # Nút gửi goal
    btn_goal = tk.Button(left_frame,text="Send Goal",font=("Arial",14),command=lambda : send_goal())
    btn_goal.pack(pady=10)

    menu = tk.Menu(root, tearoff=0, font=("Arial", 14))
    menu.add_command(label="10 x 10", command=lambda: draw_grid(10, 10))
    menu.add_command(label="20 x 20", command=lambda: draw_grid(20, 20))
    menu.add_command(label="50 x 50", command=lambda: draw_grid(50, 50))

    # Bên phải
    canvas_frame = tk.Frame(root, bg="white")
    canvas_frame.pack(side=tk.LEFT, fill=tk.BOTH, expand=True)

    canvas = tk.Canvas(canvas_frame, bg="white")
    canvas.pack(fill=tk.BOTH, expand=True)
    canvas.bind("<Button-1>", on_left_click)
    canvas.bind("<Button-3>", on_right_click)
    canvas.bind("<Configure>", on_canvas_resize)

    root.update()
    draw_grid(10, 10)
    root.mainloop()

# ================== Main ==================
def main(args=None):
    global turtle_node

    rclpy.init(args=args)

    turtle_node = TurtleGridNode()   # <--- node duy nhất

    # Chạy GUI trên thread riêng
    t = threading.Thread(target=gui_thread, daemon=True)
    t.start()

    try:
        rclpy.spin(turtle_node)
    except KeyboardInterrupt:
        pass

    turtle_node.destroy_node()
    rclpy.shutdown()


if __name__ == "__main__":
    main()
