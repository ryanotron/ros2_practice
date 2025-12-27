## Setup notes

- The thing with `source /opt/ros/jazzy/setup.bash` is the same as with ROS1
- `ROS_DOMAIN_ID` is new. It's dds id, safe range is 0-101, 215-232. See [more](https://docs.ros.org/en/jazzy/Concepts/Intermediate/About-Domain-ID.html)

## Basic commands

- what used to be ros* are now ros2 *, e.g. `ros2 node list`, `ros2 topic list`
- `roscore` is no more
- run a node `ros2 run <pkg> <exec>`
    - equivalent to the old `rosrun`
- remapping `ros2 run <pkg> <exec> --ros-args --remap <x>`
    - topic: `ros2 run <pkg> <exec> --ros-args --remap old/topic:=new/topic`
    - node name: `ros2 run <pkg> <exec> --ros-args --remap __node:=new_node_name` 
- rviz gets a 2: rviz2

## Inspection commands

- inspect executables in a package: `ros2 pkg executables <pkgname>`
- `rosmsg show` is different. It's now `ros2 interface show msg/type`

## Launch

- launch files can be python now. XML is still possible. See simple example [here](../00_launch/multle_turtle.launch.py)

## Others

- `rqt` has service caller. Shows all the request fields too. Pretty convenient, compared to `ros2 service call blah`