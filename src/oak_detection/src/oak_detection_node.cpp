#include "oak_detection/oak_detection_node.hpp"

namespace oak_detection
{

OakDetection::OakDetection(const rclcpp::NodeOptions & option)
: rclcpp::Node("oak_detection_node", "", option),
  id_detect(get_parameter("detection_id").as_int()),
  height(get_parameter("height").as_int()),
  width(get_parameter("width").as_int()),
  gain_p(get_parameter("gain_p").as_double())
{
  auto _subscription_cb_vision = [this](vision_msgs::msg::Detection2DArray::SharedPtr msg) -> void {
    // direction_obj(id_detect, msg);

    int cnt_detect = 0;

    for (int i = 0; i < (int)msg->detections.size(); i++) {
      if (msg->detections.at(i).id == std::to_string(id_detect)) {
        cnt_detect++;
        auto bb = std::make_shared<vision_msgs::msg::BoundingBox2D>(msg->detections.at(i).bbox);

        double anglar_increment = (width / 2.0f - bb->center.position.x) * gain_p;

        auto twist = std::make_shared<geometry_msgs::msg::Twist>();
        twist->linear.x = 0.0;
        twist->linear.y = 0.0;
        twist->linear.z = 0.0;
        twist->angular.x = 0.0;
        twist->angular.y = 0.0;
        twist->angular.z = anglar_increment;
        publisher_vel->publish(*twist);
        RCLCPP_INFO(get_logger(), "angular: %f", anglar_increment);
      }
    }

    if (cnt_detect == 0) {
      auto twist = std::make_shared<geometry_msgs::msg::Twist>();
      twist->linear.x = 0.0;
      twist->linear.y = 0.0;
      twist->linear.z = 0.0;
      twist->angular.x = 0.0;
      twist->angular.y = 0.0;
      twist->angular.z = 0.0;
      publisher_vel->publish(*twist);
      RCLCPP_INFO(get_logger(), "angular: 0 (no detection)");
    }
  };
  _subscription_vision = this->create_subscription<vision_msgs::msg::Detection2DArray>(
    "color/mobilenet_detections", _qos, _subscription_cb_vision);

  publisher_vel = this->create_publisher<geometry_msgs::msg::Twist>("oak_d/cmd_vel", _qos);

  RCLCPP_INFO(get_logger(), "detection_id: %d, P gain: %f", id_detect, gain_p);
}

void OakDetection::direction_obj(int id, const vision_msgs::msg::Detection2DArray::SharedPtr msg)
{
  for (int i = 0; i < (int)msg->detections.size(); i++) {
    if (msg->detections.at(i).id == std::to_string(id)) {
      auto bb = std::make_shared<vision_msgs::msg::BoundingBox2D>(msg->detections.at(i).bbox);

      double anglar_increment = (width / 2.0f - bb->center.position.x) * 0.01;

      auto twist = std::make_shared<geometry_msgs::msg::Twist>();
      twist->linear.x = 0.0;
      twist->linear.y = 0.0;
      twist->linear.z = 0.0;
      twist->angular.x = 0.0;
      twist->angular.y = 0.0;
      twist->angular.z = anglar_increment;
      publisher_vel->publish(*twist);
    }
  }
}

}  // namespace oak_detection
