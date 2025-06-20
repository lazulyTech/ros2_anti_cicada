#include "base_driver/base_driver_node.hpp"

#include <cmath>

namespace base_driver
{

BaseDriver::BaseDriver(const rclcpp::NodeOptions & options)
: rclcpp::Node("base_driver_node", "", options),
  wheel_radius(get_parameter("wheel_radius").as_double()),
  attached_direction(get_parameter("attached_direction").as_double()),
  device_canid(get_parameter("device_canid").as_int()),
  mode_manual(true)
{
  auto _subscrption_cb_mode = [this](const std_msgs::msg::Bool::SharedPtr msg) -> void {
    mode_manual = msg->data;
    if (mode_manual == true) {
      RCLCPP_INFO(this->get_logger(), "Mode: Manual");
    } else {
      RCLCPP_INFO(this->get_logger(), "Mode: Auto");
    }
  };
  _subscrption_mode =
    this->create_subscription<std_msgs::msg::Bool>("mode_manual", _qos, _subscrption_cb_mode);

  auto _subscription_cb_vel = [this](const geometry_msgs::msg::Twist::SharedPtr msg) -> void {
    if (mode_manual) {
      _subscriber_callback_vel(msg);
    }
  };
  _subscrption_vel =
    this->create_subscription<geometry_msgs::msg::Twist>("cmd_vel", _qos, _subscription_cb_vel);
  // _subscrption_vel = this->create_subscription<geometry_msgs::msg::Twist>(
  // "cmd_vel", _qos, std::bind(&BaseDriver::_subscriber_callback_vel, this, std::placeholders::_1));

  publisher_can = this->create_publisher<socketcan_interface_msg::msg::SocketcanIF>("can_tx", _qos);

  RCLCPP_INFO(this->get_logger(), "車輪半径: %f, 取付距離: %f", wheel_radius, attached_direction);
}

BaseDriver::~BaseDriver() {}

void BaseDriver::_subscriber_callback_vel(const geometry_msgs::msg::Twist::SharedPtr msg)
{
  double v = msg->linear.x;
  double omega = msg->angular.z;
  convert_diff(v, omega);
}

// cmd_vel から差動2輪の各モータのduty比に変える
void BaseDriver::convert_diff(const double v, const double omega)
{
  double velL = v - omega;
  double velR = v + omega;
  send_motorvel(velL, velR);
}

// モータのduty比をCANで送る
void BaseDriver::send_motorvel(const double velL, const double velR)
{
  auto msg_can = std::make_shared<socketcan_interface_msg::msg::SocketcanIF>();
  msg_can->eff = true;
  msg_can->canid = device_canid;
  msg_can->candlc = 2;
  msg_can->candata[0] = (uint32_t)(velL * 100 + 100);
  msg_can->candata[1] = (uint32_t)(velR * 100 + 100);

  RCLCPP_INFO(
    this->get_logger(), "L:%4d, R:%4d", msg_can->candata[0] - 100, msg_can->candata[1] - 100);

  publisher_can->publish(*msg_can);
}

}  // namespace base_driver
