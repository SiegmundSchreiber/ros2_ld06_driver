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
                {"frame_id"  : "laser_frame"},
            ],
        )
    ])
    