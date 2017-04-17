cmake_minimum_required(VERSION 3.6.2)

project(gumyns.smart.home.hardware.arm.device)

FILE(GLOB dirs RELATIVE ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/*)
foreach(dir ${dirs})
    if(IS_DIRECTORY ${PROJECT_SOURCE_DIR}/${dir})
        add_subdirectory(${dir})
    endif()
endforeach()