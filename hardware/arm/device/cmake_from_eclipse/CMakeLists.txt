cmake_minimum_required(VERSION 3.6.2)

project(proj)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/../../std-libs/)

include(StdLibs)

file(GLOB SOURCE_FILES src/*.c src/*.cpp)

include_directories(include)

add_executable(${PROJECT_NAME} ${ARM_LIBRARY_SOURCES} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME})

set(RENAME_ELF_COMMAND mv ${PROJECT_BINARY_DIR}/${CMAKE_PROJECT_NAME}.elf ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.elf)
set(GENERATE_HEX_COMMAND ${CMAKE_OBJCOPY} -Oihex ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.elf ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.hex)
set(WRITE_SIZE_COMMAND ${GCC_ARM_DIRECTORY}arm-none-eabi-size ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.elf --format=berkeley)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${RENAME_ELF_COMMAND} && usleep 100000 && ${GENERATE_HEX_COMMAND} && ${WRITE_SIZE_COMMAND} >> sizes.txt && ${WRITE_SIZE_COMMAND}
        COMMENT "Building ${PROJECT_NAME}.hex and here's size in [B]:")

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMENT "KK THX BB")