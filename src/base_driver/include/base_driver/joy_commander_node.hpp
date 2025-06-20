#pragma once

#include <rclcpp/rclcpp.hpp>

#include "base_driver/visibility_control.h"
#include "sensor_msgs/msg/joy.hpp"
#include "std_msgs/msg/bool.hpp"

namespace base_driver
{

class JoyCommander : public rclcpp::Node
{
public:
  BASE_DRIVER_PUBLIC
  explicit JoyCommander(const rclcpp::NodeOptions & options = rclcpp::NodeOptions());

private:
  // subscriber
  rclcpp::Subscription<sensor_msgs::msg::Joy>::SharedPtr _subscrption_joy;
  // callbackはラムダ式にする

  // publisher
  rclcpp::Publisher<std_msgs::msg::Bool>::SharedPtr publisher_mode;

  rclcpp::QoS _qos = rclcpp::QoS(10);

  // const
  const uint8_t btn_ch;
  const uint32_t count_th;

  // vals
  bool sent_prev;
  bool btn_state_prev;
  uint32_t count;
};

}  // namespace base_driver
