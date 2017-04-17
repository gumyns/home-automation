include(Compiler)
include(Boost)
include(DescriptionGenerator)

# setup compiled binaries dirs
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/plugins/${PLUGIN_TYPE})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/plugins/${PLUGIN_TYPE})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/test)

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