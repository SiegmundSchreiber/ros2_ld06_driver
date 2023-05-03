# sdk_ld06_raspberry_ros_wrapper_for_ros2

[sdk_ld06_raspberry_ros](https://github.com/LetsOKdo/sdk_ld06_raspberry_ros)をROS2用に魔改造したものです


## how to use

### how to build

```sh
$ git clone https://github.com/naga-karupi/sdk_ld06_raspberry_ros_wrapper_for_ros2.git
$ cd sdk_ld06_raspberry_ros_wrapper_for_ros2
$ colcon build
```

### launch node

```sh
$ ros2 launch sdk_ld06_raspberry_ros_wrapper_for_ros2 ld06_launcher.py
```

### custom topic name

In `launch/ld06_launcher.py`, 

```py
from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package="sdk_ld06_raspberry_ros_wrapper_for_ros2",
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

