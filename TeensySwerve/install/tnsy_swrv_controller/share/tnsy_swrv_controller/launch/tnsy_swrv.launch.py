import os
from launch import LaunchDescription
from launch_ros.actions import Node
from launch_ros.actions import LifecycleNode
from launch_ros.events.lifecycle import ChangeState
from ament_index_python.packages import get_package_share_directory
import launch.events as events
from launch.actions import (EmitEvent, RegisterEventHandler, LogInfo)
from launch.conditions import IfCondition
from launch.event_handlers import (OnExecutionComplete, OnProcessExit, OnProcessIO, OnProcessStart, OnShutdown)
from launch.events import Shutdown
from launch.substitutions import (EnvironmentVariable, FindExecutable, LaunchConfiguration,  LocalSubstitution, PythonExpression)
from launch_ros.event_handlers import OnStateTransition
import lifecycle_msgs.msg

# COLORS for text. Tell me if there's a better way of implementing this
RED    = '\033[31m'
GREEN  = '\033[32m'
YELLOW = '\033[33m'
BLUE   = '\033[34m'
PURPLE = '\033[35m'
CYAN   = '\033[36m'
GRAY   = '\033[37m'
BLINK  = '\033[5m'
RESET  = '\033[0m'


def generate_launch_description():
    tnsy_params = os.path.join(get_package_share_directory('tnsy_swrv_controller'), 'config', 'tnsy_swrv.yaml')
    
    joy_node = LifecycleNode(
        package= 'joy',
        executable= 'game_controller_node',
        name= 'game_controller_node',
        parameters=[tnsy_params],
        namespace='nameSpace1'
    )
    
    joy_translator_node = LifecycleNode(
        package='tnsy_swrv_controller',
        executable='joy_translator',
        name='joy_translator_node',
        namespace='nameSpace1'
    )

    micro_ros_agent = Node(
        package= 'micro_ros_agent',
        executable= 'micro_ros_agent',
        name= 'micro_ros_agent',
        output={'stdout':'screen'}, # this line will make the launch file display micro_ros_agent's standard output in the terminal but not the log
        arguments=['serial', '--dev', '/dev/ttyACM0'],
    )

    

    # Make joy_translator take the 'configure' transition
    joy_translator_configure_transition_event = EmitEvent(
        event=ChangeState(
            lifecycle_node_matcher=events.matches_action(joy_translator_node),
            transition_id=lifecycle_msgs.msg.Transition.TRANSITION_CONFIGURE
        )
    )

    # Make joy_translator take the 'activate' transition
    joy_translator_activate_transition_event = EmitEvent(
        event=ChangeState(
            lifecycle_node_matcher=events.matches_action(joy_translator_node),
            transition_id=lifecycle_msgs.msg.Transition.TRANSITION_ACTIVATE
        )
    )

    return LaunchDescription([
        joy_node,

        RegisterEventHandler(
            OnProcessStart(
                target_action=joy_node,
                on_start=[
                    LogInfo(msg = GREEN + "[joy_node] started. Starting [joy_translator_node]" + RESET),
                    joy_translator_node
                ]
            )
        ),

        RegisterEventHandler(
            OnProcessStart(
                target_action=joy_translator_node,
                on_start=[
                    LogInfo(msg = GREEN + "[joy_translator_node] started. CONFIGURING" + RESET),
                    joy_translator_configure_transition_event
                ]
            )
        ),
        RegisterEventHandler(
            OnStateTransition(
                target_lifecycle_node=joy_translator_node,
                goal_state='inactive',
                entities=[
                    LogInfo( msg = GREEN + "[joy_translator_node] INACTIVE. ACTIVATING" + RESET),
                    joy_translator_activate_transition_event,
                ],
            )
        ),
        RegisterEventHandler(
            OnStateTransition(
                target_lifecycle_node=joy_translator_node,
                goal_state='active',
                entities=[
                    LogInfo(msg = GREEN + "[joy_translator_node] ACTIVE. Starting [micro_ros_agent]" + RESET),
                    micro_ros_agent
                ]
            )
        ),
    ])
