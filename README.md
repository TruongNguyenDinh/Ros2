# Ros2 - Tutorial

### Ros version: ros2 - humble (LTS: long term support)

### Ubuntu version : Ubuntu 22.04 (obligatory)

## 🚀 Cài đặt ROS2 Humble

1. Chuẩn bị

Cập nhật hệ thống và các gói cần thiết

```bash
sudo apt update && sudo apt upgrade -y
sudo apt install -y locales curl gnupg lsb-release

```

Cấu hình locale UTF-8

```bash
sudo locale-gen en_US en_US.UTF-8
sudo update-locale LC_ALL=en_US.UTF-8 LANG=en_US.UTF-8
export LANG=en_US.UTF-8

```

2. Thêm kho ROS2 vào apt

Thêm key:

```bash
sudo curl -sSL https://raw.githubusercontent.com/ros/rosdistro/master/ros.key -o /usr/share/keyrings/ros-archive-keyring.gpg

```

Thêm repo

```bash
echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/ros-archive-keyring.gpg] http://packages.ros.org/ros2/ubuntu $(lsb_release -cs) main" | sudo tee /etc/apt/sources.list.d/ros2.list > /dev/null

```

3. Cài đặt `ROS2 Humble`

Cập nhật lại và cài:

```bash
sudo apt update
sudo apt install -y ros-humble-desktop

```

4. Thiết lập môi trường
   
   Sau khi cài xong ROS2, cần `source` để hoạt động, lưu ý nếu mở nhiều terminal thì cần `source` cho từng terminal

```bash
source /opt/ros/humble/setup.bash

```

Để nhan chóng hơn thì làm cho nó vào `.bashrc`. thì mỗi lần mở terminal ta sẽ không cần gõ câu lệnh trên.

```bash
echo "source /opt/ros/humble/setup.bash" >> ~/.bashrc

```

5. Kiểm tra

Mở terminal và gõ

```bash
ros2 run demo_nodes_cpp talker
```

Mở terminal khác và gõ

```bash
ros2 run demo_nodes_cpp listener
```

## ⚙️ Cài đặt Colcon

`Colcon` là một công cụ cần thiết để build `workspace` của ta.

1. Cài colcon 

```bash
sudo apt update
sudo apt install -y python3-colcon-common-extensions
```

2. Kiểm tra cài đặt

```bash
colcon version-check
```

```bash
ntruong1124@Javis:~$ colcon version-check
colcon-argcomplete 0.3.3: up-to-date
colcon-bash 0.5.0: up-to-date
colcon-cd 0.2.1: local version is newer than latest release (0.1.1)
colcon-cmake 0.2.29: up-to-date
colcon-core 0.20.0: up-to-date
colcon-defaults 0.2.9: up-to-date
...
```

Thành công !