from launch import LaunchDescription
from launch.actions import Shutdown
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
from os import popen
from os.path import join as ojoin

def generate_launch_description():
    cfg = ojoin(
        get_package_share_directory("sh_find_server"),
        "config",
        "params.yaml"
    )
    desc = LaunchDescription()
    desc.add_action(Node(
        package="sh_find_server",
        executable="find_server",
        namespace="/smart_home",
        parameters=[
            cfg,
            {"find/server_host": popen("hostname -I | awk '{print $1}'").read().strip()}
        ],
        on_exit=Shutdown(),
    ))
    return desc
