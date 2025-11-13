cmake_minimum_required(VERSION 3.16)

project(vulkan-engine VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Library source files
set(VE_SOURCES
    vulkanApp.cpp
    spirvHelpers.cpp
)

set(VE_HEADERS
    vulkanApp.h
    error.h
    templateHelper.h
)

# Create static library
add_library(ve STATIC ${VE_SOURCES} ${VE_HEADERS})

# Find Vulkan
find_package(Vulkan REQUIRED)

# Include directories
target_include_directories(ve
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        ${Vulkan_INCLUDE_DIRS}
)

# Link libraries (dependencies must be provided by parent project)
target_link_libraries(ve
    PUBLIC
        ${Vulkan_LIBRARIES}
        glfw
    PRIVATE
        spirv-reflect-static
        glslang
        glslang-default-resource-limits
)

# Compiler definitions
target_compile_definitions(ve
    PUBLIC
        GLFW_INCLUDE_VULKAN
)
