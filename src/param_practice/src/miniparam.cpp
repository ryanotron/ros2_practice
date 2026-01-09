#include <chrono>
#include <rclcpp/rclcpp.hpp>

using namespace std::chrono_literals;

class MiniParam : public rclcpp::Node
{
 public:
  MiniParam() : Node("mini_param")
  {
    // declare params
    this->declare_parameter("increment", 1);

    // start timer
    timer_ = this->create_wall_timer(500ms, std::bind(&MiniParam::timerCb, this));
  }

  void timerCb()
  {
    // read increment
    increment_ = this->get_parameter("increment").as_int();

    // increment counter
    count_ += increment_;
    RCLCPP_INFO(this->get_logger(), "count is now %d, with incr %d", count_, increment_);

    // reset counter at 100
    // and reset increment too, as practice example
    if (count_ >= 100)
    {
      count_ = 0;
      
      // setting parameter is done with a vector of parameters,
      // prep the vector here, even though we want to only change one
      std::vector<rclcpp::Parameter> new_params;
      rclcpp::Parameter new_param ("increment", 1);
      new_params.push_back(new_param);

      // set params with the vector here
      this->set_parameters(new_params);
    }
  }
 private:
  rclcpp::TimerBase::SharedPtr timer_;

  int count_ = 0;
  int increment_;
};

int main(int argc, char** argv)
{
  rclcpp::init(argc, argv);
  
  auto mini_param = std::make_shared<MiniParam> ();
  rclcpp::spin(mini_param);

  rclcpp::shutdown();
  return 0;
}