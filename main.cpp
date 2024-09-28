#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include <iostream>

int main() {
  glfwInit();

  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  GLFWwindow* window = glfwCreateWindow(800, 600, "Vulkan window", nullptr, nullptr);

  uint32_t extensionCount = 0;
  vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
  std::cout << extensionCount << " extensions supported\n";

  // Initialize matrix and vector
  glm::mat4 matrix(1.0f);  // Initialize with an identity matrix
  glm::vec4 vec(1.0f, 0.0f, 0.0f, 0.0f);  // Initialize vector with specific values
  auto test = matrix * vec;
  std::cout << "Result:" << test.x << std::endl;

  while(!glfwWindowShouldClose(window)) {
      glfwPollEvents();
  }

  // Window Cleanup
  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}
