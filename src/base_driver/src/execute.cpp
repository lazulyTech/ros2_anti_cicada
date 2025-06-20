#include <rclcpp/rclcpp.hpp>

#include "base_driver/base_driver_node.hpp"
#include "base_driver/joy_commander_node.hpp"
#include "socketcan_interface/socketcan_interface_node.hpp"

int main(int argc, char * argv[])
{
  setvbuf(stdout, NULL, _IONBF, BUFSIZ);
  rclcpp::init(argc, argv);
  rclcpp::executors::MultiThreadedExecutor exec;

  rclcpp::NodeOptions nodes_option;
  nodes_option.allow_undeclared_parameters(true);
  nodes_option.automatically_declare_parameters_from_overrides(true);

  auto socketcan_node = std::make_shared<socketcan_interface::SocketcanInterface>(nodes_option);
  auto joy_commander_node = std::make_shared<base_driver::JoyCommander>(nodes_option);
  auto base_drive_node = std::make_shared<base_driver::BaseDriver>(nodes_option);

  exec.add_node(socketcan_node);
  exec.add_node(joy_commander_node);
  exec.add_node(base_drive_node);

  exec.spin();

  rclcpp::shutdown();
  return 0;
}
