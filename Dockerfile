FROM archlinux:latest

ARG DEBIAN_FRONTEND=noninteractive
ENV NVIDIA_DRIVER_CAPABILITIES=all
ENV NVIDIA_VISIBLE_DEVICES=all

# Install necessary packages
RUN pacman -Syu --noconfirm \
  base-devel \
  cmake \
  python-pip \
  libglvnd \
  pciutils \
  vulkan-tools \
  mesa-utils \
  vulkan-radeon \
  vulkan-intel \
  vulkan-icd-loader \
  nvidia-utils \
  && rm -rf /var/lib/pacman/sync/*

RUN pip3 install conan --break-system-packages

WORKDIR /usr/src/app
COPY conanfile.txt .

# Install Conan dependencies and build
RUN conan profile detect
RUN rm -rf build && mkdir build && conan install . --output-folder=build --build=missing -c tools.system.package_manager:mode=install

COPY src/ ./src/
COPY inc/ ./inc/
COPY main.cpp ./
COPY CMakeLists.txt ./

RUN cd build && cmake .. -DCMAKE_TOOLCHAIN_FILE=build/Release/generators/conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release -DTARGET_OPTIMIZE=speed \
  && cmake --build . \
  && mv compile_commands.json ../ && cd ..

CMD ["vulkaninfo"]
