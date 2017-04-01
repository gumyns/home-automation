cmake_minimum_required(VERSION 3.6.2)

project(gumyns.smart.home)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_AUTOMOC ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

# setup compiled binaries dirs
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# setup boost libraries
set(BOOST_ROOT ../libs/boost)
set(BOOST_LIBRARYDIR ../libs/boost/lib)

file(GLOB CONFIG_MODULE src/config/*.cpp)

file(GLOB STORAGE_MODULE src/database/*.cpp)

file(GLOB HARDWARE_MODULE src/hardware/*.cpp src/hardware/model/*.h)

file(GLOB OPENHAB_MODULE src/openhab/*.cpp src/openhab/model/*.h)

set(SOURCE_FILES
    ${CONFIG_MODULE}
	${STORAGE_MODULE}
    ${HARDWARE_MODULE}
	${OPENHAB_MODULE}
    src/Application.cpp
)

#file(GLOB LOGGER_SRC
#	src/utils/*.h
#)

include_directories(
	../plugins/include
	../libs/include
    src/
)


# executables
add_executable(SmartHomeServer ${SOURCE_FILES} src/main.cpp)

#find boost
#add_definitions(-DBOOST_ALL_DYN_LINK)
set(Boost_USE_MULTITHREADED ON)
find_package(Boost 1.63.0 COMPONENTS
		filesystem
       	system
		thread
        REQUIRED)
       

include_directories(${Boost_INCLUDE_DIRS})
set(LIBS ${LIBS} ${Boost_LIBRARIES})

find_package(ZeroMQ REQUIRED)
include_directories(${ZeroMQ_INCLUDE_DIRS})
set(LIBS ${LIBS} ${ZeroMQ_LIBRARIES})

find_package(SQLite3 REQUIRED)
include_directories(${SQLITE3_INCLUDE_DIR})
set(LIBS ${LIBS} ${SQLITE3_LIBRARY})

# pthreads
find_package(Threads REQUIRED)

# linker
target_link_libraries(SmartHomeServer ${LIBS} dl ${CMAKE_THREAD_LIBS_INIT})
