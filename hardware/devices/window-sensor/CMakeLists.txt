cmake_minimum_required(VERSION 3.6.2)
# enable C, C++ and assembler for this project
project(arm.device.window-sensor C CXX ASM)
# show toolchain
message(STATUS "Toolchain: ${CMAKE_TOOLCHAIN_FILE}")
# add modules dir
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/../../cmake/Modules)
# find required packages
find_package(CMSIS REQUIRED)
find_package(HAL REQUIRED)
# includes
include_directories(
    ${CMSIS_INCLUDE_DIRS}
    ${HAL_INCLUDE_DIRS}
    Inc
)
# find sources
file(GLOB SOURCES Src/*.c)
file(GLOB SOURCES_CXX Src/*.cpp)
# add I2C address to gcc if specified
if (I2C_ADDRESS)
    add_definitions("-DI2C_ADDRESS=${I2C_ADDRESS}")
endif (I2C_ADDRESS)
# create elf file
add_executable(${PROJECT_NAME} ${SOURCES} ${SOURCES_CXX} ${HAL_SOURCES} startup_stm32f030x6.s)
# add linker script
set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "\"-T${PROJECT_SOURCE_DIR}/STM32F030F4Px_FLASH.ld\"")
# external commands TODO move it to some global file
set(GENERATE_HEX_COMMAND ${CMAKE_OBJCOPY} -Oihex ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.elf ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.hex)
set(WRITE_SIZE_COMMAND ${GCC_ARM_DIRECTORY}arm-none-eabi-size ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.elf --format=berkeley)
set(STRIP_COMMAND ${GCC_ARM_DIRECTORY}arm-none-eabi-strip ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.elf)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${STRIP_COMMAND} && ${GENERATE_HEX_COMMAND} && ${WRITE_SIZE_COMMAND} >> sizes.txt && ${WRITE_SIZE_COMMAND}
        COMMENT "Building ${PROJECT_NAME}.hex and here's size in [B]:")

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMENT "KK THX BB")