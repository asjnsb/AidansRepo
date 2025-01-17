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

def generate_launch_description():
    joy_params = os.path.join(get_package_share_directory('tnsy_swrv_controller'), 'config', 'joystick.yaml')
    
    joy_node = LifecycleNode(
        package= 'joy',
        executable= 'game_controller_node',
        name= 'game_controller_node',
        parameters=[joy_params],
        namespace='nameSpace1'
    )
    
    joy_translator_node = LifecycleNode(
        package='tnsy_swrv_controller',
        executable='joy_translator',
        name='joy_translator_node',
        namespace='nameSpace1'
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
        joy_translator_node,

        RegisterEventHandler(
            OnProcessStart(
                target_action=joy_translator_node,
                on_start=[
                    joy_translator_configure_transition_event
                ]
            )
        ),
        RegisterEventHandler(
            OnStateTransition(
                target_lifecycle_node=joy_translator_node,
                goal_state='inactive',
                entities=[
                    LogInfo( msg = "'joy_translator_node' reached the 'INACTIVE' state"),
                    # you could put "joy_node" here in order to only launch that node when joy_translator_node reaches the inactive state
                    joy_translator_activate_transition_event,
                ],
            )
        ),
        RegisterEventHandler(
            OnStateTransition(
                target_lifecycle_node=joy_translator_node,
                goal_state='active',
                entities=[
                    LogInfo(msg = "'joy_translator_node' reached the 'ACTIVE' state")
                ]
            )
        ),
    ])
