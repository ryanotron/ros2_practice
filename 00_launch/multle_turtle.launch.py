# turtlesim multisim.launch.py, but broken down for easier comprehension
# original function is like so:
# def generate_launch_description():
#     return LaunchDescription([
#         launch_ros.actions.Node(
#             namespace='turtlesim1', package='turtlesim',
#             executable='turtlesim_node', output='screen'),
#         launch_ros.actions.Node(
#             namespace='turtlesim2', package='turtlesim',
#             executable='turtlesim_node', output='screen'),
#     ])

from launch import LaunchDescription
import launch_ros.actions

def make_nodes():
    # first turtlesim node
    # notice the params are similar to usual <node> tag in ros1
    sim1 = launch_ros.actions.Node(
        namespace='sim1', 
        package='turtlesim',
        executable='turtlesim_node',
        output='screen'
    )

    # second turtlesim node,
    # we push it down to a different namespace
    sim2 = launch_ros.actions.Node(
        namespace='sim2', 
        package='turtlesim',
        executable='turtlesim_node',
        output='screen'
    )

    # nodes away
    return (sim1, sim2)

# this is what a python launchfile must have,
# it must return a LaunchDescription containing a list of nodes
# along the way to that point, all of python is available
def generate_launch_description():
    nodes = make_nodes()
    return LaunchDescription(nodes)