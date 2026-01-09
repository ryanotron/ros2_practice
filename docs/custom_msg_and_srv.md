## About custom interfaces

- interface in its own package, good idea
- `ros2 pkg create --build-type ament_cmake <pkg_name>`
  - only ament_cmake is admissible here

- `srv` and `msg` directories work the same as in ros1
- builtin types and array reference: https://docs.ros.org/en/jazzy/Concepts/Basic/About-Interfaces.html

- CMakeLists.txt gets a new mantra for building interfaces:
  ```
  find_package(rosidl_default_generators REQUIRED)
  rosidl_generate_interfaces(${PROJECT_NAME})()
  ```

- package.xml gets a new mantra too:
  ```
  <buildtool_depend>rosidl_default_generators</buildtool_depend>
  <exec_depend>rosidl_default_runtime</exec_depend>
  <member_of_group>rosidl_interface_packages</member_of_group>
  ```