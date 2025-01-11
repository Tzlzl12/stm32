cmake_minimum_required(VERSION 3.22)

#
# This file is generated only once,
# and is not re-generated if converter is called multiple times.
#
# User is free to modify the file as much as necessary
#

# Setup compiler settings
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)


# Define the build type
# set(CMAKE_BUILD_TYPE "Release")

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug")
endif()

# Set the project name
set(CMAKE_PROJECT_NAME dominos)
set(CMAKE_COLOR_DIAGNOSTICS on)
# Include toolchain file
include("init/gcc-arm-none-eabi.cmake")

# Enable compile command to ease indexing with e.g. clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

project(${CMAKE_PROJECT_NAME})
# Enable CMake support for ASM and C languages
enable_language(C ASM CXX)


# Core project settings
message("Build type: " ${CMAKE_BUILD_TYPE})

# Create an executable object type
add_executable(${CMAKE_PROJECT_NAME})

# Add STM32CubeMX generated sources
add_subdirectory(init)

# Link directories setup
target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined library search paths
)

# Add sources to executable
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user sources here
    ${CMAKE_SOURCE_DIR}/src/main.c
)

# Add include paths
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined include paths
  # ${CMAKE_SOURCE_DIR}/core
  ${CMAKE_SOURCE_DIR}/sys
  ${CMAKE_SOURCE_DIR}/dev/inc
  ${CMAKE_SOURCE_DIR}/src/inc
  ${CMAKE_SOURCE_DIR}/src/peri/inc
  /usr/arm-none-eabi/include
)

# Add project symbols (macros)
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined symbols
  USE_STDPERIPH_DRIVER
 STM32F411xE
)

# Add linked libraries
target_link_libraries(${CMAKE_PROJECT_NAME}
    stm32
    # Add user defined libraries
)

add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex ${ELF_FILE} ${HEX_FILE}  # 使用 objcopy 转换为 HEX 格式
    COMMENT "Converting ELF to HEX"  # 显示转换的提示信息
)
