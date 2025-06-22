#ifndef BASE_DRIVER__BASE_DRIVER_NODE_HPP_
#define BASE_DRIVER__BASE_DRIVER_NODE_HPP_

#include <rclcpp/rclcpp.hpp>

#include "base_driver/visibility_control.h"
#include "geometry_msgs/msg/twist.hpp"
#include "socketcan_interface_msg/msg/socketcan_if.hpp"
#include "std_msgs/msg/bool.hpp"
#include "std_msgs/msg/empty.hpp"

namespace base_driver
{

class BaseDriver : public rclcpp::Node
{
public:
  BASE_DRIVER_PUBLIC
  explicit BaseDriver(const rclcpp::NodeOptions & options = rclcpp::NodeOptions());

  virtual ~BaseDriver();

private:
  // subscriber
  rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr _subscrption_vel;
  void _subscriber_callback_vel(const geometry_msgs::msg::Twist::SharedPtr msg);

  rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr _subscrption_oak;
  void _subscriber_callback_oak(const geometry_msgs::msg::Twist::SharedPtr msg);

  rclcpp::Subscription<std_msgs::msg::Bool>::SharedPtr _subscrption_mode;

  // publisher
  void convert_diff(const double v, const double omega);
  void send_motorvel(const double velL, const double velR);
  rclcpp::Publisher<socketcan_interface_msg::msg::SocketcanIF>::SharedPtr publisher_can;

  rclcpp::QoS _qos = rclcpp::QoS(10);

  // const
  const double wheel_radius;
  const double attached_direction;
  const uint32_t device_canid;

  // vals
  bool mode_manual;
};

}  // namespace base_driver

#endif  // BASE_DRIVER__BASE_DRIVER_NODE_HPP_
