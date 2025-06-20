# import os
# from ament_index_python.packages import get_package_share_directory

from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    # 起動エンティティクラスの作成
    launch_discription = LaunchDescription()

    # パラメータファイルのパス設定
    config_file_path = '/home/ubuntu/ros/ros2_anti_cicada/src/base_driver/config/params.yaml'
    # config_file_path = os.path.join(
    #     get_package_share_directory('base_driver'),
    #     'config',
    #     'params.yaml'
    # )
    # 手動制御ノードの作成
    # base_driver_node = Node(
    #     package = 'base_driver',
    #     executable = 'base_driver_node',
    #     # parameters = ['/home/ubuntu/ros/test_ws/src/joy_test/config/params.yaml'],
    #     parameters = [config_file_path],
    #     output='screen'
    # )
    execute_node = Node(
        package = 'base_driver',
        executable = 'executor',
        # parameters = ['/home/ubuntu/ros/test_ws/src/joy_test/config/params.yaml'],
        parameters = [config_file_path],
        output='screen'
    )

    # joyノードの追加
    joy_node = Node(
        package = 'joy',
        executable = 'joy_node',
        # parameters = ['/home/ubuntu/ros/test_ws/src/joy_test/config/params.yaml'],
        parameters = [config_file_path],
        output='screen'
    )
    # teleopノードの追加
    teleop_node = Node(
        package = 'teleop_twist_joy',
        executable = 'teleop_node',
        # parameters = ['/home/ubuntu/ros/test_ws/src/joy_test/config/params.yaml'],
        parameters = [config_file_path],
        output='screen'
    )

    # 起動の追加
    # launch_discription.add_entity(base_driver_node)
    launch_discription.add_entity(execute_node)
    launch_discription.add_entity(joy_node)
    launch_discription.add_action(teleop_node)

    return launch_discription

