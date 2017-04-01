#
#  Copyright (c) 2010 Carlos Junior <address@hidden>
#
# - Try to find libmicrohttpd
# Once done this will define
#
#  ZeroMQ_FOUND - system has libmicrohttpd
#  ZeroMQ_INCLUDE_DIRS - the libmicrohttpd include directory
#  ZeroMQ_LIBRARIES - Link these to use libmicrohttpd
#  ZeroMQ_DEFINITIONS - Compiler switches required for using libmicrohttpd
#
#  Redistribution and use is allowed according to the terms of the GPLv3 license
#  For details see the accompanying LICENSE file.
#

if (ZeroMQ_LIBRARIES AND ZeroMQ_INCLUDE_DIRS)
    # in cache already
    set(ZeroMQ_FOUND TRUE)
else (ZeroMQ_LIBRARIES AND ZeroMQ_INCLUDE_DIRS)
    set(ZeroMQ_DEFINITIONS "")

    find_path(ZeroMQ_INCLUDE_DIR
            NAMES
            zmq.h
            zmq_utils.h
            PATHS
            ../libs/zeromq/include/
            )

    if (ZeroMQ_INCLUDE_DIR)
        message("-- Found ZeroMQ includes in: ${ZeroMQ_INCLUDE_DIR}")
    else (ZeroMQ_INCLUDE_DIR)
        message("Ice include not found :(")
    endif (ZeroMQ_INCLUDE_DIR)

    find_library(ZeroMQ_LIBRARY
            NAMES
            libzmq.so
            PATHS
            /usr/lib
            ../libs/zeromq
            )

    if (ZeroMQ_LIBRARY)
        message("-- Found ZeroMQ in: ${ZeroMQ_LIBRARY}")
    else (ZeroMQ_LIBRARY)
        message("ZeroMQ not found :(")
    endif (ZeroMQ_LIBRARY)

    if (ZeroMQ_LIBRARY)
        set(ZeroMQ_FOUND TRUE)
    endif (ZeroMQ_LIBRARY)

    set(ZeroMQ_INCLUDE_DIRS
            ${ZeroMQ_INCLUDE_DIR}
            )

    if (ZeroMQ_FOUND)
        set(ZeroMQ_LIBRARIES
                ${ZeroMQ_LIBRARIES}
                ${ZeroMQ_LIBRARY}
                )
    endif (ZeroMQ_FOUND)

    if (ZeroMQ_INCLUDE_DIRS AND ZeroMQ_LIBRARIES)
        set(ZeroMQ_FOUND TRUE)
    endif (ZeroMQ_INCLUDE_DIRS AND ZeroMQ_LIBRARIES)

    if (ZeroMQ_FIND_REQUIRED AND NOT ZeroMQ_FOUND)
        message(FATAL_ERROR "Could not find LibZeroMQ")
    endif (ZeroMQ_FIND_REQUIRED AND NOT ZeroMQ_FOUND)

    # show the ZeroMQ_INCLUDE_DIRS and ZeroMQ_LIBRARIES variables only in the advanced view
    mark_as_advanced(ZeroMQ_INCLUDE_DIRS ZeroMQ_LIBRARIES)

endif (ZeroMQ_LIBRARIES AND ZeroMQ_INCLUDE_DIRS)