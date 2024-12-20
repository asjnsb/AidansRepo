import os
from launch import LaunchDescription
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory

from launch.actions import (DeclareLaunchArgument, EmitEvent, ExecuteProcess, LogInfo, RegisterEventHandler, TimerAction)
from launch.conditions import IfCondition
from launch.event_handlers import (OnExecutionComplete, OnProcessExit, OnProcessIO, OnProcessStart, OnShutdown)
from launch.events import Shutdown
from launch.substitutions import (EnvironmentVariable, FindExecutable, LaunchConfiguration,  LocalSubstitution, PythonExpression)

def generate_launch_description():
    joy_params = os.path.join(get_package_share_directory('tnsy_swrv_controller'), 'config', 'joystick.yaml')
    
    joy_node = Node(
        package= 'joy',
        executable= 'game_controller_node',
        parameters=[joy_params],
    )
    
    joy_translator = Node(
        package='tnsy_swrv_controller',
        executable='joy_translator',
        name='joy_translator_node'
    )

    return LaunchDescription([
        joy_node,
        joy_translator,
        
        RegisterEventHandler(
            OnProcessExit(
                target_action=joy_translator,
                on_exit=[
                    LogInfo(msg=(EnvironmentVariable(name='USER'), ' used Ctrl-C')),
                    EmitEvent(event=Shutdown(reason='Ctrl-C'))
                ]
            )
        ),
        RegisterEventHandler(
            OnShutdown(
                on_shutdown=[LogInfo(
                    msg=['Launch was asked to shutdown: ',
                         LocalSubstitution('event.reason')]
                )]
            )
        ),
    ])
