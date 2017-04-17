cmake_minimum_required(VERSION 3.6.2)

set(PLUGIN_TYPE hub)
set(PLUGIN_NAME system.monitor)
set(PLUGIN_ID 0x0001)

project(gumyns.smart.home.plugin.${PLUGIN_TYPE}.${PLUGIN_NAME})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
        ${PROJECT_SOURCE_DIR}/../../../cmake/
        ${PROJECT_SOURCE_DIR}/../../cmake/
        )
include(CommonStuff)

file(GLOB LIBRARY_SOURCES
	src/*.cpp
	src/*.h
)

set(TEST_FILES
	LIBRARY_SOURCES
    test/main.cpp
)

include_directories(
	../../../libs/include
	../../include
	src/
	test/
)

# executables
add_library(.${PLUGIN_TYPE}.${PLUGIN_NAME} SHARED ${LIBRARY_SOURCES})
add_executable(${PLUGIN_TYPE}.${PLUGIN_NAME}.main test/main.cpp)

# linker
target_link_libraries(.${PLUGIN_TYPE}.${PLUGIN_NAME} ${LIBS} dl ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(${PLUGIN_TYPE}.${PLUGIN_NAME}.main ${LIBS} dl ${CMAKE_THREAD_LIBS_INIT})

