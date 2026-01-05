#include <chrono>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "interface_practice/msg/box.hpp"

using namespace std::chrono_literals;

// ros2 node subclasses from rclcpp::Node, instead of having a ros::NodeHandle
class MiniPub : public rclcpp::Node
{
 public:
  // node name is decided here
  MiniPub() : Node("minipub"), count_(0)
  {
    // setup publishers
    pub_ = this->create_publisher<std_msgs::msg::String>("hello_topic", 10);
    rect_pub_ = this->create_publisher<interface_practice::msg::Box>("box_topic", 10);

    // setup timer
    timer_ = this->create_wall_timer(200ms, std::bind(&MiniPub::TimerCb, this));
  }

  // callback for timer
  void TimerCb()
  {
    auto msg = std_msgs::msg::String();
    msg.data = "Hello, " + std::to_string(count_);
    count_++;

    // ROS_INFO is now RCLCPP_INFO, notice the get_logger thing
    RCLCPP_INFO(this->get_logger(), "Pubbing %s", msg.data.c_str());
    this->pub_->publish(msg);

    // make box message
    auto rect = interface_practice::msg::Box();
    rect.centre.x = count_/10.;
    rect.centre.y = count_/10.;
    rect.centre.z = count_/10.;
    rect.length = 1;
    rect.width = 2;
    rect.height = 3;
    this->rect_pub_->publish(rect);
  }

 private:
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr pub_;
  rclcpp::Publisher<interface_practice::msg::Box>::SharedPtr rect_pub_;
  int count_; 
};

int main(int argc, char** argv)
{
  // ros init is now rclcpp::init
  rclcpp::init(argc, argv);

  // spin has argument now
  rclcpp::spin(std::make_shared<MiniPub>());

  rclcpp::shutdown();

  return 0;
}