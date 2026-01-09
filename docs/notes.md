## Setup notes

- The thing with `source /opt/ros/jazzy/setup.bash` is the same as with ROS1
- `ROS_DOMAIN_ID` is new. It's dds id, safe range is 0-101, 215-232. See [more](https://docs.ros.org/en/jazzy/Concepts/Intermediate/About-Domain-ID.html)
- `sudo rosdep init` and `rosdep update` are still necessary

## Basic commands

- what used to be ros* are now ros2 *, e.g. `ros2 node list`, `ros2 topic list`, `ros2 topic echo`
- `roscore` is no more
- run a node `ros2 run <pkg> <exec>`
    - equivalent to the old `rosrun`
- remapping `ros2 run <pkg> <exec> --ros-args --remap <x>`
    - topic: `ros2 run <pkg> <exec> --ros-args --remap old/topic:=new/topic`
    - node name: `ros2 run <pkg> <exec> --ros-args --remap __node:=new_node_name` 
- rviz gets a 2: rviz2
- `roscd` is now `colcon_cd`, some setup required. `echo "export _colcon_cd_root=/opt/ros/jazzy/" >> ~/.bashrc`. [More](https://docs.ros.org/en/jazzy/Tutorials/Beginner-Client-Libraries/Colcon-Tutorial.html#setup-colcon-cd)

## Inspection commands

- inspect executables in a package: `ros2 pkg executables <pkgname>`
- `rosmsg show` is different. It's now `ros2 interface show msg/type`
    - `ros2 interface show srv/blah` for the equivalent for `rossrv show`

## Launch

- launch files can be python now. XML is still possible. See simple example [here](../00_launch/multle_turtle.launch.py)

## Build

- use `colcon build --symlink-install`. This replaces `catkin_make`
    - cmake arguments can be appended: `colcon build --cmake-args -DCMAKE_BUILD_TYPE=Release`
    - specific package: `colcon build --packages-select <blah>`
- sourcing workspace is `source ws/install/setup.bash`; no more devel
    - `local_setup.bash` exists, this just sources the workspace, without underlay; `setup.bash` is with underlay

## Others

- `rqt` has service caller. Shows all the request fields too. Pretty convenient, compared to `ros2 service call blah`