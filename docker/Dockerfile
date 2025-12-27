FROM ubuntu:noble

WORKDIR /workspace

# setup repo
RUN apt-get update \
    && apt-get install -y software-properties-common \
    && add-apt-repository universe \
    && apt-get install -y locales \
    && locale-gen en_GB.UTF-8

# setup locale
ENV LANG=en_GB.UTF-8
ENV LANGUAGE=en_GB:en
ENV LC_ALL=en_GB.UTF-8

# configure ros repo
RUN apt-get update \
    && apt-get install -y curl \
    && export ROS_APT_SOURCE_VERSION=$(curl -s https://api.github.com/repos/ros-infrastructure/ros-apt-source/releases/latest | grep -F "tag_name" | awk -F\" '{print $4}') \
    && curl -L -o /tmp/ros2-apt-source.deb "https://github.com/ros-infrastructure/ros-apt-source/releases/download/${ROS_APT_SOURCE_VERSION}/ros2-apt-source_${ROS_APT_SOURCE_VERSION}.$(. /etc/os-release && echo ${UBUNTU_CODENAME:-${VERSION_CODENAME}})_all.deb" \
    && dpkg -i /tmp/ros2-apt-source.deb \
    && rm /tmp/ros2-apt-source.deb

# dev tools, ros install
RUN apt-get update \
    && apt-get install -y ros-dev-tools \
    && apt-get upgrade -y \
    && apt-get install -y ros-jazzy-desktop \
    && apt-get install -y vim tmux\
    && rm -rf /var/lib/apt/lists/*

# auto setup
RUN echo "source /opt/ros/jazzy/setup.bash" >> ~/.bashrc

CMD ["/bin/bash"]