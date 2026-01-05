#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "interface_practice/msg/box.hpp"

class MiniSub : public rclcpp::Node
{
 public:
  MiniSub() : Node("minisub")
  {
    // setup subscribers
    sub_ = this->create_subscription<std_msgs::msg::String>("hello_topic", 10,
      std::bind(&MiniSub::helloCb, this, std::placeholders::_1));

    box_sub_ = this->create_subscription<interface_practice::msg::Box>("box_topic", 10,
      std::bind(&MiniSub::boxCb, this, std::placeholders::_1));
  }

  void helloCb(std_msgs::msg::String::UniquePtr msg)
  {
    RCLCPP_INFO(this->get_logger(), "got %s", msg->data.c_str());
  }

  void boxCb(interface_practice::msg::Box::UniquePtr msg)
  {
    RCLCPP_INFO(this->get_logger(), "new box %.2f, %.2f, %.2f, dims %.2f, %.2f, %.2f",
      msg->centre.x, msg->centre.y, msg->centre.z, msg->length, msg->width, msg->height);
  }
 private:
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr sub_;
  rclcpp::Subscription<interface_practice::msg::Box>::SharedPtr box_sub_;
};

int main(int argc, char** argv)
{
  rclcpp::init(argc, argv);

  rclcpp::spin(std::make_shared<MiniSub>());

  rclcpp::shutdown();

  return 0;
}