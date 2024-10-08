#ifndef HELLO_H
#define HELLO_H

#include <vulkan/vulkan.h>
#include <vulkan/vulkan_core.h>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vector>

#define WIDTH 800
#define HEIGHT 600

class HelloTriangleApplication {
public:
    void run() {
      initWindow();
      initVulkan();
      mainLoop();
      cleanup();
    }

private:
  void initWindow() {
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); // Tells it not to create an OpenGL context
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE); // Disables window resizing
    window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr); // nullptr1 allows yu to pick a monitor to show it on, nullptr2 is related to OpenGL
  }

  void createInstance() {
    VkApplicationInfo appInfo = {
      VK_STRUCTURE_TYPE_APPLICATION_INFO, // sType
      nullptr, // pNext
      "Hello Triangle", // pApplicationName
      VK_MAKE_VERSION(1, 0, 0), // applicationVersion
      "No Engine", // pEngineName
      VK_MAKE_VERSION(1, 0, 0), // engineVersion
      VK_API_VERSION_1_0 // apiVersion
    };

    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    std::vector<const char*> requiredExtensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

#if defined(__APPLE__)
    // Add the VK_KHR_portability_enumeration extension for macOS (MoltenVK)
    requiredExtensions.emplace_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);
#endif

    VkInstanceCreateInfo createInfo {
      VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO, // sType
      nullptr, // pNext
      0, // flags
      &appInfo, // pApplicationInfo
      0, // enabledLayerCount
      nullptr, // ppEnabledLayerNames
      static_cast<uint32_t>(requiredExtensions.size()), // enabledExtensionCount
      requiredExtensions.data()               // ppEnabledExtensionNames
    };

#if defined(__APPLE__)
    // Add the VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR flag for macOS (MoltenVK)
    createInfo.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
#endif

    
    VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);
    if (result != VK_SUCCESS) {
      throw std::runtime_error("Failed to create Vulkan instance! Error code: " + std::to_string(result));
    }

    // Enumerate available extensions
    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

    std::vector<VkExtensionProperties> extensions(extensionCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

    std::cout << "available extensions:\n";
    // Print supported extensions
    for (const auto& extension : extensions) {
        std::cout << '\t' << extension.extensionName << '\n';
    }
    std::cout << '\n';
    for (uint32_t i = 0; i < glfwExtensionCount; ++i) {
        std::cout << "Extension " << i + 1 << ": " << glfwExtensions[i] << std::endl;
    }
  }

  void initVulkan() {
    createInstance();

  }

  void mainLoop() {
    while (!glfwWindowShouldClose(window)) {
      glfwPollEvents();
    }
  }

  void cleanup() {
    vkDestroyInstance(instance, nullptr);
    glfwDestroyWindow(window);
    glfwTerminate();
  }

  GLFWwindow* window;
  VkInstance instance;
};

#endif // HELLO_H
