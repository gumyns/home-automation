cmake_minimum_required(VERSION 3.6.2)

project(blinky)

set(CMAKE_TOOLCHAIN_FILE ${PROJECT_SOURCE_DIR}/../../toolchain/STM32F0.cmake)

include_directories(
    ../../cmsis
    ../../lib
)
###########################################################################

file(GLOB APP_SOURCES src/*.cpp)

add_definitions(-DSTM32F030)
add_executable(${PROJECT_NAME}.elf ${APP_SOURCES} ${LINKER_SCRIPT})

target_link_libraries(${PROJECT_NAME}.elf -nostartfiles)

set(HEX_FILE ${PROJECT_SOURCE_DIR}/build/${PROJECT_NAME}.hex)
set(BIN_FILE ${PROJECT_SOURCE_DIR}/build/${PROJECT_NAME}.bin)

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -O ihex ${PROJECT_NAME}.elf ${PROJECT_NAME}.hex
        COMMENT "Building ${HEX_FILE} \nBuilding ${BIN_FILE}")