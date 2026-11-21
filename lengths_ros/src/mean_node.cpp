#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/float64_multi_array.hpp"
#include "example_interfaces/msg/float64.hpp"
#include "lengths_ros/lengths.hpp"

using InMsg = example_interfaces::msg::Float64MultiArray;
using OutMsg = example_interfaces::msg::Float64;

class MeanNode : public rclcpp::Node
{
public:
  MeanNode() : Node("mean_node")
  {
    pub_ = this->create_publisher<OutMsg>("mean_length", 10);
    sub_ = this->create_subscription<InMsg>(
      "lengths", 10, std::bind(&MeanNode::on_lengths, this, std::placeholders::_1));
    RCLCPP_INFO(this->get_logger(), "mean_node started: /lengths -> /mean_length");
  }

private:
  void on_lengths(const InMsg::SharedPtr msg)
  {
    auto mean = meanLength(msg->data);

    if (!mean.has_value())
    {
      RCLCPP_INFO(this->get_logger(), "empty input: mean is undefined, publish nothing");
      return;
    }

    OutMsg out;
    out.data = mean.value();
    pub_->publish(out);
    RCLCPP_INFO(this->get_logger(), "mean = %.3f", out.data);
  }

  rclcpp::Publisher<OutMsg>::SharedPtr pub_;
  rclcpp::Subscription<InMsg>::SharedPtr sub_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MeanNode>());
  rclcpp::shutdown();
  return 0;
}
