cmake_minimum_required(VERSION 3.6.2)

project(arm.window.sensor)

set(CMAKE_TOOLCHAIN_FILE ${PROJECT_SOURCE_DIR}/../../toolchain/STM32F0.cmake)

file(GLOB CMSIS system/src/cmsis/*.c)
file(GLOB CORTEXM system/src/cortexm/*.c)
file(GLOB DIAG system/src/diag/*.c)
file(GLOB NEWLIB
        system/src/newlib/*.c
        system/src/newlib/*.cpp)
file(GLOB HAL system/src/stm32f0-stdperiph/*.c)

set(ARM_LIBRARY_SOURCES
        ${CMSIS}
        ${CORTEXM}
        ${DIAG}
        ${NEWLIB}
        ${HAL}
        )


include_directories(
        ../../lib
        include
        system/include
        system/include/cmsis
        system/include/stm32f0-stdperiph
        system/src/stm32f0-stdperiph
)
###########################################################################

file(GLOB_RECURSE SOURCE_FILES src/*.cpp)

add_definitions(-DSTM32F030)
add_definitions(-DUSE_STDPERIPH_DRIVER)
add_definitions(-DHSE_VALUE=48000000)


add_executable(${PROJECT_NAME} ${ARM_LIBRARY_SOURCES} ${SOURCE_FILES})
set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "\"-T${PROJECT_SOURCE_DIR}/ldscripts/sections.ld\"" )

target_link_libraries(${PROJECT_NAME})

set(GENERATE_HEX_COMMAND ${CMAKE_OBJCOPY} -Oihex ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.elf ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.hex)
set(WRITE_SIZE_COMMAND ${GCC_ARM_DIRECTORY}arm-none-eabi-size ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.elf --format=berkeley)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${GENERATE_HEX_COMMAND} && ${WRITE_SIZE_COMMAND} >> sizes.txt && ${WRITE_SIZE_COMMAND}
        COMMENT "Building ${PROJECT_NAME}.hex and here's size in [B]:")

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMENT "KK THX BB")