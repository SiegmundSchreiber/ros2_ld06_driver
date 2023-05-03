#include <rclcpp/rclcpp.hpp>
#include <string>
#include <cstdio>
#include <cstring>
#include <chrono>
#include <functional>

#include "cmd_interface_linux.h"
#include "lipkg.h"

using namespace std::chrono_literals;

std::shared_ptr<LiPkg> lidar;

class wrapper_ld06: public rclcpp::Node {
  std::string topic_name;
  std::string port_name;
  std::string frame_id;

  rclcpp::Publisher<sensor_msgs::msg::LaserScan>::SharedPtr lidar_pub;
  rclcpp::TimerBase::SharedPtr lidar_rate;

  CmdInterfaceLinux cmd_port;

  void timer_callback() {
    if (lidar->IsFrameReady()) {
      lidar_pub->publish(lidar->GetLaserScan()); // Fixed Frame:  lidar_frame
      lidar->ResetFrameReady();
    }
  }

public:

  std::function<void(const char*, size_t)> f = 
  [](const char *byte, size_t len) {
    if (lidar->Parse((uint8_t *)byte, len)) {
      lidar->AssemblePacket();
    }
  };

  wrapper_ld06() : Node("ldLiDAR_LD06"){
    this->declare_parameter("topic_name", "");
    this->declare_parameter("port_name" , "");
    this->declare_parameter("frame_id", "");

    topic_name = this->get_parameter("topic_name").as_string();
    port_name  = this->get_parameter("port_name") .as_string();
    frame_id   = this->get_parameter("frame_id")  .as_string();
    
    if (port_name.empty()) {
      RCLCPP_ERROR(this->get_logger(), "[ldrobot] Can't find LiDAR LD06");
      exit(EXIT_FAILURE);
    }else {
      RCLCPP_INFO(this->get_logger(), "[ldrobot] FOUND LiDAR_LD06");
    }

    lidar_pub = this->create_publisher<sensor_msgs::msg::LaserScan>(topic_name, 10);
    lidar_rate = this->create_wall_timer(100ms, std::bind(&wrapper_ld06::timer_callback, this));

    lidar = std::make_shared<LiPkg>(frame_id);
    cmd_port.SetReadCallback(f);

    if(cmd_port.Open(port_name)) {
      RCLCPP_INFO(this->get_logger(), "[ldrobot] LiDAR_LD06 started successfully ");
    }else {
      RCLCPP_INFO(this->get_logger(), "[ldrobot] LiDAR_LD06 started failed ");
    }
  }
};

int main(int argc, char ** argv) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<wrapper_ld06>());
  rclcpp::shutdown();

  return 0;
}
