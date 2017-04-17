cmake_minimum_required(VERSION 3.6.2)

set(PLUGIN_TYPE device)
set(PLUGIN_NAME test.device)
set(PLUGIN_ID 0xFFFF)

project(gumyns.smart.home.plugin.${PLUGIN_TYPE}.${PLUGIN_NAME})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
        ${PROJECT_SOURCE_DIR}/../../../cmake/
        ${PROJECT_SOURCE_DIR}/../../cmake/
        )
include(Compiler)
include(Boost)
include(DescriptionGenerator)

# setup compiled binaries dirs
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

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

#find boost
add_definitions(-DBOOST_ALL_DYN_LINK)
set(Boost_USE_MULTITHREADED ON)
find_package(Boost 1.63.0 COMPONENTS		
	filesystem       	
	system
	thread
	REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})
set(LIBS ${LIBS} ${Boost_LIBRARIES})

# pthreads
find_package(Threads REQUIRED)

# linker
target_link_libraries(.${PLUGIN_TYPE}.${PLUGIN_NAME} ${LIBS} dl ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(${PLUGIN_TYPE}.${PLUGIN_NAME}.main ${LIBS} dl ${CMAKE_THREAD_LIBS_INIT})

