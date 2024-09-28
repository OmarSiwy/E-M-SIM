cmake_minimum_required(VERSION 3.24)

project(E-M-SIM VERSION 1.0.0 LANGUAGES CXX)

# Compiler Settings
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -Wpedantic -Wshadow -Wformat=2 -fdiagnostics-color=always")
set(OPTIMIZE_SPEED_FLAGS "-O3")
set(OPTIMIZE_SIZE_FLAGS "-Os")
if(NOT DEFINED TARGET_OPTIMIZE OR TARGET_OPTIMIZE STREQUAL "speed")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OPTIMIZE_SPEED_FLAGS}")
elseif(TARGET_OPTIMIZE STREQUAL "size")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OPTIMIZE_SIZE_FLAGS}")
endif()

# Project Setup:
include_directories(${CMAKE_SOURCE_DIR}/inc)
file(GLOB_RECURSE SRC_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp ${CMAKE_SOURCE_DIR}/src/*.cc)
set(MAIN_FILE ${CMAKE_SOURCE_DIR}/main.cpp)
add_executable(${PROJECT_NAME} ${SRC_FILES} ${MAIN_FILE})

# Linker Settings
if(NOT DEFINED TARGET_OPTIMIZE OR TARGET_OPTIMIZE STREQUAL "speed")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s")
endif()

# Packages
## Vulkan
find_package(Vulkan REQUIRED)
target_link_libraries(${PROJECT_NAME} Vulkan::Vulkan)
## GLFW
find_package(glfw3 REQUIRED)
target_link_libraries(${PROJECT_NAME} glfw)
## GLM
find_package(glm REQUIRED)
target_link_libraries(${PROJECT_NAME} glm::glm)
