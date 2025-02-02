cmake_minimum_required(VERSION 3.22)

project(stm32)
add_library(stm32 INTERFACE)

# Enable CMake support for ASM and C languages
enable_language(C ASM)

# add_definitions(
#   USE_STDPERIPH_DRIVER
# 	STM32F411xE
#     $<$<CONFIG:Debug>:DEBUG>
# )

target_include_directories(stm32 INTERFACE
  ${CMAKE_SOURCE_DIR}/sys
  ${CMAKE_SOURCE_DIR}/core
  ${CMAKE_SOURCE_DIR}/dev/inc
  ${CMAKE_SOURCE_DIR}/src/inc
)

target_sources(stm32 INTERFACE
  ${CMAKE_SOURCE_DIR}/dev/src/misc.c
  ${CMAKE_SOURCE_DIR}/dev/src/stm32f4xx_adc.c
  ${CMAKE_SOURCE_DIR}/dev/src/stm32f4xx_can.c
  ${CMAKE_SOURCE_DIR}/dev/src/stm32f4xx_cec.c
  ${CMAKE_SOURCE_DIR}/dev/src/stm32f4xx_crc.c
  ${CMAKE_SOURCE_DIR}/dev/src/stm32f4xx_cryp.c
  ${CMAKE_SOURCE_DIR}/dev/src/stm32f4xx_cryp_aes.c
  ${CMAKE_SOURCE_DIR}/dev/src/stm32f4xx_cryp_des.c
  ${CMAKE_SOURCE_DIR}/dev/src/stm32f4xx_cryp_tdes.c
  ${CMAKE_SOURCE_DIR}/dev/src/stm32f4xx_dac.c
  ${CMAKE_SOURCE_DIR}/dev/src/stm32f4xx_dbgmcu.c
  ${CMAKE_SOURCE_DIR}/dev/src/stm32f4xx_dcmi.c
  ${CMAKE_SOURCE_DIR}/dev/src/stm32f4xx_dfsdm.c
  ${CMAKE_SOURCE_DIR}/dev/src/stm32f4xx_dma.c
  ${CMAKE_SOURCE_DIR}/dev/src/stm32f4xx_dma2d.c
  ${CMAKE_SOURCE_DIR}/dev/src/stm32f4xx_dsi.c
  ${CMAKE_SOURCE_DIR}/dev/src/stm32f4xx_exti.c
  ${CMAKE_SOURCE_DIR}/dev/src/stm32f4xx_flash.c
  ${CMAKE_SOURCE_DIR}/dev/src/stm32f4xx_flash_ramfunc.c
  ${CMAKE_SOURCE_DIR}/dev/src/stm32f4xx_fmpi2c.c
  ${CMAKE_SOURCE_DIR}/dev/src/stm32f4xx_gpio.c
  ${CMAKE_SOURCE_DIR}/dev/src/stm32f4xx_hash.c
  ${CMAKE_SOURCE_DIR}/dev/src/stm32f4xx_hash_md5.c
  ${CMAKE_SOURCE_DIR}/dev/src/stm32f4xx_hash_sha1.c
  ${CMAKE_SOURCE_DIR}/dev/src/stm32f4xx_i2c.c
  ${CMAKE_SOURCE_DIR}/dev/src/stm32f4xx_iwdg.c
  ${CMAKE_SOURCE_DIR}/dev/src/stm32f4xx_lptim.c
  ${CMAKE_SOURCE_DIR}/dev/src/stm32f4xx_ltdc.c
  ${CMAKE_SOURCE_DIR}/dev/src/stm32f4xx_pwr.c
  ${CMAKE_SOURCE_DIR}/dev/src/stm32f4xx_qspi.c
  ${CMAKE_SOURCE_DIR}/dev/src/stm32f4xx_rcc.c
  ${CMAKE_SOURCE_DIR}/dev/src/stm32f4xx_rng.c
  ${CMAKE_SOURCE_DIR}/dev/src/stm32f4xx_rtc.c
  ${CMAKE_SOURCE_DIR}/dev/src/stm32f4xx_sai.c
  ${CMAKE_SOURCE_DIR}/dev/src/stm32f4xx_sdio.c
  ${CMAKE_SOURCE_DIR}/dev/src/stm32f4xx_spdifrx.c
  ${CMAKE_SOURCE_DIR}/dev/src/stm32f4xx_spi.c
  ${CMAKE_SOURCE_DIR}/dev/src/stm32f4xx_syscfg.c
  ${CMAKE_SOURCE_DIR}/dev/src/stm32f4xx_tim.c
  ${CMAKE_SOURCE_DIR}/dev/src/stm32f4xx_usart.c
  ${CMAKE_SOURCE_DIR}/dev/src/stm32f4xx_wwdg.c
  ${CMAKE_SOURCE_DIR}/sys/delay.c
  ${CMAKE_SOURCE_DIR}/sys/system_stm32f4xx.c
  # ${CMAKE_SOURCE_DIR}/startup_stm32f411xe.s
  ${CMAKE_SOURCE_DIR}/startup_stm32f401xc.s
)

target_link_directories(stm32 INTERFACE
)

target_link_libraries(stm32 INTERFACE
)

target_compile_options(stm32 INTERFACE
  -Wno-unused-parameter
  -Wno-misleading-indentation
)

# Validate that STM32CubeMX code is compatible with C standard
if(CMAKE_C_STANDARD LESS 11)
  message(ERROR "Generated code requires C11 or higher")
endif()


