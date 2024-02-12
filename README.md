# ros2_ld06_driver

Driver for th OKDO LD06 Lidar Hat

## operating check environment

| OS           | ros2 distribution |
| ------------ | ----------------- |
| ubuntu 22.04 | humble              |

## how to use

### how to build

```sh
$ git clone https://github.com/SiegmundSchreiber/ros2_ld06_driver.git 
$ cd ros2 launch ros2_ld06_driver
$ colcon build
```

### launch node

```sh
$ ros2 launch ros2_ld06_driver ld06_launcher.py
```

### custom topic name

In `launch/ld06_launcher.py`, 

```py
from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package="ros2_ld06_driver",
            executable="lidar",
            name="lidar",
            output="screen",
            emulate_tty=True,
            parameters=[
                {"topic_name": "lidar_msg"},
                {"port_name" : "/dev/ttyUSB0"},
                {"frame_id"  : "lidar_frame"},
            ],
        )
    ])
```

You could change `topic_name`, `port_name`, `frame_id` as needed.  
Especially port_name should be set according to your environment.

