cmake_minimum_required(VERSION 3.8)
project(oak_detection)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake_auto REQUIRED)
ament_auto_find_build_dependencies()

ament_auto_add_library(oak_detection_node src/oak_detection_node.cpp)

ament_export_include_directories(include)
# ament_export_libraries(chassis_driver)

# executor
add_executable(executor test/execute.cpp)
ament_target_dependencies(executor
    rclcpp
)
target_link_libraries(executor
    oak_detection_node
)

# install
# install(DIRECTORY launch config
#     DESTINATION share/${PROJECT_NAME}
# )
install(TARGETS
    executor
    DESTINATION lib/${PROJECT_NAME}
)

ament_auto_package(INSTALL_TO_SHARE)

# add_library(oak_detection_node src/oak_detection_node.cpp)
# target_compile_features(oak_detection_node PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17
# target_include_directories(oak_detection_node PUBLIC
#   $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
#   $<INSTALL_INTERFACE:include>)
# ament_target_dependencies(
#   oak_detection_node
#   "rclcpp"
#   "std_msgs"
#   "vision_msgs"
#   "geometry_msgs"
#   "sensor_msgs"
# )
#
# # Causes the visibility macros to use dllexport rather than dllimport,
# # which is appropriate when building the dll but not consuming it.
# target_compile_definitions(oak_detection_node PRIVATE "OAK_DETECTION_BUILDING_LIBRARY")
#
# install(
#   DIRECTORY include/
#   DESTINATION include
# )
# install(
#   TARGETS oak_detection_node
#   EXPORT export_${PROJECT_NAME}
#   ARCHIVE DESTINATION lib
#   LIBRARY DESTINATION lib
#   RUNTIME DESTINATION bin
# )
#
# if(BUILD_TESTING)
#   find_package(ament_lint_auto REQUIRED)
#   # the following line skips the linter which checks for copyrights
#   # comment the line when a copyright and license is added to all source files
#   set(ament_cmake_copyright_FOUND TRUE)
#   # the following line skips cpplint (only works in a git repo)
#   # comment the line when this package is in a git repo and when
#   # a copyright and license is added to all source files
#   set(ament_cmake_cpplint_FOUND TRUE)
#   ament_lint_auto_find_test_dependencies()
# endif()
#
# ament_export_include_directories(
#   include
# )
# ament_export_libraries(
#   oak_detection_node
# )
# ament_export_targets(
#   export_${PROJECT_NAME}
# )
#
# ament_package()

