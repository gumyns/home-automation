cmake_minimum_required(VERSION 3.6.2)

project(arm.window.sensor C CXX ASM)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/../../cmake/Modules)

find_package(CMSIS REQUIRED)
find_package(HAL REQUIRED)

file(GLOB SOURCES Src/*.c)

set(SOURCE_FILES
        ${SOURCES}
        ${HAL_SOURCES}
)

include_directories(
        ${CMSIS_INCLUDE_DIRS}
        ${HAL_INCLUDE_DIRS}
        Inc
)
###########################################################################
add_executable(${PROJECT_NAME} ${SOURCE_FILES} startup_stm32f030x6.s)
set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "\"-T${PROJECT_SOURCE_DIR}/STM32F030F4Px_FLASH.ld\"" )
#set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "\"-T${PROJECT_SOURCE_DIR}/sections.ld\"" )

target_link_libraries(${PROJECT_NAME})

set(GENERATE_HEX_COMMAND ${CMAKE_OBJCOPY} -Oihex ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.elf ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.hex)
set(WRITE_SIZE_COMMAND ${GCC_ARM_DIRECTORY}arm-none-eabi-size ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.elf --format=berkeley)
set(STRIP_COMMAND ${GCC_ARM_DIRECTORY}arm-none-eabi-strip ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.elf)

#MESSAGE(STATUS ${STRIP_COMMAND})

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${STRIP_COMMAND} && ${GENERATE_HEX_COMMAND} && ${WRITE_SIZE_COMMAND} >> sizes.txt && ${WRITE_SIZE_COMMAND}
        COMMENT "Building ${PROJECT_NAME}.hex and here's size in [B]:")

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMENT "KK THX BB")

message(STATUS ${SOURCE_FILES})