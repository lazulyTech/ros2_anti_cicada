cmake_minimum_required(VERSION 3.8)
project(base_driver)

# set(CMAKE_EXPORT_COMPILE_COMMANDS enable)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake_auto REQUIRED)
ament_auto_find_build_dependencies()

ament_auto_add_library(base_driver_node src/base_driver_node.cpp)
ament_auto_add_library(joy_commander_node src/joy_commander_node.cpp)

ament_export_include_directories(include)
# ament_export_libraries(chassis_driver)

# executor
add_executable(executor src/execute.cpp)
ament_target_dependencies(executor
    rclcpp
    socketcan_interface
    oak_detection
)
target_link_libraries(executor
    base_driver_node
    joy_commander_node
)

# install
install(DIRECTORY launch config
    DESTINATION share/${PROJECT_NAME}
)
install(TARGETS
    executor
    DESTINATION lib/${PROJECT_NAME}
)

ament_auto_package(INSTALL_TO_SHARE)

