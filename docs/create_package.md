## About creating ros2 packages

- basic:
    - `ros2 pkg create --build-type ament_cmake <pkg_name>`
    - `ros2 pkg create --build-type ament_python <pkg_name>`

- options
    - `--license` specify license
    - `--node-name <blah>` make basic executable
    - `--dependencies <blah>` populate dependencies, usually rclcpp goes here