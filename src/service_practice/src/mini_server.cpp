#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/srv/add_two_ints.hpp"
#include "interface_practice/srv/sum_array.hpp"

class MiniServer : public rclcpp::Node
{
 public:
  MiniServer() : Node("mini_server")
  {
    add_ints_service_ = this->create_service<example_interfaces::srv::AddTwoInts>("add_two_ints", 
      std::bind(&MiniServer::addSv, this, std::placeholders::_1, std::placeholders::_2));

    sum_array_service_ = this->create_service<interface_practice::srv::SumArray>("sum_array", 
      std::bind(&MiniServer::sumSv, this, std::placeholders::_1, std::placeholders::_2));

    RCLCPP_INFO(this->get_logger(), "ready");
  }

  void addSv(const std::shared_ptr<example_interfaces::srv::AddTwoInts::Request> req,
    std::shared_ptr<example_interfaces::srv::AddTwoInts::Response> res)
  {
    res->sum = req->a + req->b;
    RCLCPP_INFO(this->get_logger(), "sum: %ld + %ld =  %ld", req->a, req->b, res->sum);
  }

  void sumSv(const std::shared_ptr<interface_practice::srv::SumArray::Request> req,
    std::shared_ptr<interface_practice::srv::SumArray::Response> res)
  {
    res->out = 0;
    for (auto i : req->ins)
    {
      res->out += i;
    }
    RCLCPP_INFO(this->get_logger(), "array sum %ld", res->out);
  }

 private:
  rclcpp::Service<example_interfaces::srv::AddTwoInts>::SharedPtr add_ints_service_;
  rclcpp::Service<interface_practice::srv::SumArray>::SharedPtr sum_array_service_;

};

int main(int argc, char** argv)
{
  rclcpp::init(argc, argv);

  auto miniserve = std::make_shared<MiniServer> ();
  rclcpp::spin(miniserve);

  rclcpp::shutdown();

  return 0;
}