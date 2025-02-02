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
file(GLOB_RECURSE  periphral_files ${CMAKE_SOURCE_DIR}/src/peri/*.c)
file(GLOB interrupt_files ${CMAKE_SOURCE_DIR}/src/inte/*.c)

# Add sources to executable
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user sources here
    ${CMAKE_SOURCE_DIR}/src/main.c
    ${CMAKE_SOURCE_DIR}/src/stm32f4xx_it.c
    ${CMAKE_SOURCE_DIR}/src/systeminit.c
    # ${CMAKE_SOURCE_DIR}/src/peri/i2c/i2c.c
    ${periphral_files}
    ${interrupt_files}
)

# Add include paths
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined include paths
  # ${CMAKE_SOURCE_DIR}/core
  ${CMAKE_SOURCE_DIR}/sys
  ${CMAKE_SOURCE_DIR}/dev/inc
  ${CMAKE_SOURCE_DIR}/src/inc
  ${CMAKE_SOURCE_DIR}/src/inte/inc
  ${CMAKE_SOURCE_DIR}/src/peri/inc
  ${CMAKE_SOURCE_DIR}/src/peri/dev/inc
  ${CMAKE_SOURCE_DIR}/src/peri/i2c
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

set(ST_FLASH st-flash)
set(ST_ARGS --format ihex write)

# add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
#   COMMAND ${ST_FLASH} ${ST_ARGS} ${CMAKE_BINARY_DIR}/${CMAKE_PROJECT_NAME}.hex
#   )
# 使用 add_custom_command 进行固件下载
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND openocd
    -f interface/stlink.cfg
    -f target/stm32f4x.cfg
    -c "program ${CMAKE_BINARY_DIR}/${CMAKE_PROJECT_NAME}.hex verify reset exit"
    COMMENT "Flashing STM32 with OpenOCD"
)

set(MUL_FLASH_OPTIONS 0)
if(MUL_FLASH_OPTIONS)
  # 1. 创建用于烧录固件的自定义目标
  add_custom_target(flash
    COMMAND openocd
    -f interface/stlink.cfg
    -f target/stm32f4x.cfg
    -c "program ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.hex verify reset exit"
    COMMENT "Flashing STM32 with OpenOCD"
)
  add_custom_target(serial
    COMMAND stm32flash
    -w ${CMAKE_PROJECT_NAME}.hex
    -v
    /dev/ttyACM0
    COMMENT "Flashing STM32 with Serial"
)
  # 2. 修改主目标，使其在构建完成后依赖 `flash_stm32_openocd` 目标
  add_custom_target(binary_file
    DEPENDS ${CMAKE_PROJECT_NAME}.hex
)

  # 3. 在 `flash_stm32` 目标构建后执行 `flash_stm32_openocd` 目标
  add_dependencies(binary_file flash)
  add_dependencies(binary_file serial)

endif()
