#include <chrono>
#include <cstdlib> // atoll
#include <iostream>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/srv/add_two_ints.hpp"

using namespace std::chrono_literals; // time units

class MiniClient : rclcpp::Node
{
 public:
  MiniClient() : Node("mini_client"), ok_ (false)
  {
    // create client
    sum_client_ = this->create_client<example_interfaces::srv::AddTwoInts>("add_two_ints");

    // wait for server
    RCLCPP_INFO(this->get_logger(), "waiting for service add_two_ints");
    auto killed = false;
    while (!sum_client_->wait_for_service(100ms))
    {
      if (!rclcpp::ok())
      {
        RCLCPP_ERROR(this->get_logger(), "killed while waiting for server. Bye");
        killed = true;
        break;
      }
    }
    if (!killed)
    {
      ok_ = true;
      RCLCPP_INFO(this->get_logger(), "ready");
    }
  }

  void callServer(long a, long b)
  {
    auto req = std::make_shared<example_interfaces::srv::AddTwoInts::Request> ();
    req->a = a;
    req->b = b;

    // res is a FutureAndRequestId
    auto resfut = sum_client_->async_send_request(req);

    // wait for the future to be valid
    // we gotta do the spin pattern, 
    // just doing resfut->future.get() will result in lockup
    auto status = rclcpp::spin_until_future_complete(this->get_node_base_interface(), resfut);
    if (status != rclcpp::FutureReturnCode::SUCCESS)
      RCLCPP_ERROR(this->get_logger(), "service call error");
    else
      RCLCPP_INFO(this->get_logger(), "sum %ld + %ld = %ld", a, b, resfut.get()->sum);
  }

  bool ok() { return ok_; }
 
 private:
  rclcpp::Client<example_interfaces::srv::AddTwoInts>::SharedPtr sum_client_;
  bool ok_;
};

int main(int argc, char** argv)
{
  if (argc < 3)
  {
    std::cout << "need two arguments" << std::endl;
    return 1;
  }
  
  rclcpp::init(argc, argv);

  auto miniclient = std::make_shared<MiniClient> ();
  if (!miniclient->ok())
    return 1;
  
  auto a = atoll(argv[1]);
  auto b = atoll(argv[2]);

  miniclient->callServer(a, b);

  rclcpp::shutdown();

  return 0;
}