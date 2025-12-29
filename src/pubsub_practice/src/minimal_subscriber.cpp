#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

class MiniSub : public rclcpp::Node
{
 public:
  MiniSub() : Node("minisub")
  {
    // setup subscriber
    sub_ = this->create_subscription<std_msgs::msg::String>("hello_topic", 10,
      std::bind(&MiniSub::helloCb, this, std::placeholders::_1));
  }

  void helloCb(std_msgs::msg::String::UniquePtr msg)
  {
    RCLCPP_INFO(this->get_logger(), "got %s", msg->data.c_str());
  }
 private:
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr sub_;
};

int main(int argc, char** argv)
{
  rclcpp::init(argc, argv);

  rclcpp::spin(std::make_shared<MiniSub>());

  rclcpp::shutdown();

  return 0;
}