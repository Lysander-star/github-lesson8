#include <chrono>
#include <memory>
#include <vector>

#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/float64_multi_array.hpp"

using namespace std::chrono_literals;
using Msg = example_interfaces::msg::Float64MultiArray;

class LengthPub : public rclcpp::Node
{
public:
  LengthPub() : Node("length_pub")
  {
    pub_ = this->create_publisher<Msg>("lengths", 10);
    timer_ = this->create_wall_timer(1s, std::bind(&LengthPub::tick, this));
    RCLCPP_INFO(this->get_logger(), "length_pub started -> /lengths");
  }

private:
  void tick()
  {
    const std::vector<std::vector<double>> datasets = {
      {1.0, 2.0, 3.0, 4.0},
      {2.0, 4.0, 6.0},
      {},
      {5.0, 5.0, 5.0, 5.0, 5.0}
    };

    Msg msg;
    msg.data = datasets[i_ % datasets.size()];
    RCLCPP_INFO(this->get_logger(), "send set %zu, size = %zu", i_, msg.data.size());
    pub_->publish(msg);
    ++i_;
  }

  rclcpp::Publisher<Msg>::SharedPtr pub_;
  rclcpp::TimerBase::SharedPtr timer_;
  size_t i_ = 0;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<LengthPub>());
  rclcpp::shutdown();
  return 0;
}
