cmake_minimum_required(VERSION 3.6.2)

set(LIBRARY_NAME SystemMonitor)

project(gumyns.smart.home.plugin.hub.${LIBRARY_NAME})

set(CMAKE_AUTOMOC ON)

# setup compiled binaries dirs
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

# setup boost libraries
set(BOOST_ROOT ../../../libs/boost)
set(BOOST_LIBRARYDIR ../../../libs/boost/lib)

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
add_library(${LIBRARY_NAME} SHARED ${LIBRARY_SOURCES})
add_executable(main test/main.cpp)

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
target_link_libraries(${LIBRARY_NAME} ${LIBS} dl ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(main ${LIBS} dl ${CMAKE_THREAD_LIBS_INIT})

