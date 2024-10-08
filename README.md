# E-M-SIM

Simulations for Electric and Magnetic Fields for 2D Schematics

## To Develop:

**Windows**:

If you have windows... just search it up

**Macos**:

```Bash
# Install brew
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install.sh)"
# Install Docker
brew install --cask docker
# Install XMing
brew install --cask XQuartz
```

**Linux**:

```Bash
# Install X11
depends on build system
# Install Docker
depends on build system
```

## To Build/Run:

```Bash
## With Nvidia:
# Ensure NVIDIA Docker runtime is installed and configured
docker build -t vulkan-image .

# Run with NVIDIA GPU support
docker run --gpus all --runtime=nvidia \
  -e DISPLAY=host.docker.internal:0 \
  -v /tmp/.X11-unix:/tmp/.X11-unix \
  vulkan-image
```

if you don't have Nvidia, I haven't personally found a solution where you could passthrough your gpu into docker, so you have to build it on your machine

## Project Goals:
