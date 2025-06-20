#ifndef OAK_DETECTION__OAK_DETECTION_NODE_HPP_
#define OAK_DETECTION__OAK_DETECTION_NODE_HPP_

#include <rclcpp/rclcpp.hpp>
#include <string>

#include "geometry_msgs/msg/twist.hpp"
#include "oak_detection/visibility_control.h"
#include "vision_msgs/msg/detection2_d.hpp"
#include "vision_msgs/msg/detection2_d_array.hpp"

namespace oak_detection
{

class OakDetection : public rclcpp::Node
{
public:
  OAK_DETECTION_PUBLIC
  explicit OakDetection(const rclcpp::NodeOptions & option = rclcpp::NodeOptions());

private:
  // subscriber
  rclcpp::Subscription<vision_msgs::msg::Detection2DArray>::SharedPtr _subscription_vision;
  void direction_obj(int id, const vision_msgs::msg::Detection2DArray::SharedPtr);

  // publisher
  rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_vel;

  // const
  const int id_detect;
  const rclcpp::QoS _qos = rclcpp::QoS(10);
  const int height = 300;
  const int width = 300;
  const double gain_p = 0.01;
};

}  // namespace oak_detection

#endif  // OAK_DETECTION__OAK_DETECTION_NODE_HPP_
