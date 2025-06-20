#include "base_driver/joy_commander_node.hpp"

namespace base_driver
{
JoyCommander::JoyCommander(const rclcpp::NodeOptions & options)
: rclcpp::Node("joy_commander_node", "", options),
  btn_ch(get_parameter("mode_button").as_int()),
  count_th(get_parameter("threshold").as_int()),
  sent_prev(true),
  btn_state_prev(0),
  count(0)
{
  auto _subscrption_cb_joy = [this](const sensor_msgs::msg::Joy::SharedPtr msg) -> void {
    bool btn = msg->buttons[btn_ch];
    if (count > 0) {
      if (btn == 0) {
        count = 0;
      } else {
        count++;
        if (count >= count_th) {
          std_msgs::msg::Bool send_msg;
          send_msg.data = !sent_prev;
          publisher_mode->publish(send_msg);
          RCLCPP_INFO(this->get_logger(), "SENT: %d", (!sent_prev));
          sent_prev = !sent_prev;
          count = 0;
        }
      }
    } else {
      if (btn == 1 && btn_state_prev == 0) {
        count++;
      }
    }
    btn_state_prev = btn;
  };

  _subscrption_joy =
    this->create_subscription<sensor_msgs::msg::Joy>("joy", _qos, _subscrption_cb_joy);

  publisher_mode = this->create_publisher<std_msgs::msg::Bool>("mode_manual", _qos);

  std_msgs::msg::Bool a;
  a.data = sent_prev;
  publisher_mode->publish(a);

  RCLCPP_INFO(this->get_logger(), "Change Button: %d", btn_ch);
}
}  // namespace base_driver
