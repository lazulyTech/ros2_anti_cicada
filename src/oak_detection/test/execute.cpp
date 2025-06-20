#include <rclcpp/rclcpp.hpp>

#include "oak_detection/oak_detection_node.hpp"

int main(int argc, char * argv[])
{
  setvbuf(stdout, NULL, _IONBF, BUFSIZ);
  rclcpp::init(argc, argv);
  // rclcpp::executors::MultiThreadedExecutor exec;

  rclcpp::NodeOptions nodes_option;
  nodes_option.allow_undeclared_parameters(true);
  nodes_option.automatically_declare_parameters_from_overrides(true);

  auto oak_detection_node = std::make_shared<oak_detection::OakDetection>(nodes_option);
  rclcpp::spin(oak_detection_node);
  rclcpp::shutdown();

  return 0;
}
