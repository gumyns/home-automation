# - Try to find Sqlite3
# Once done this will define
#
#  CMSIS_FO_FOUND - system has Sqlite3
#  CMSIS_FO_INCLUDE_DIRS - the Sqlite3 include directory
#  CMSIS_FO_LIBRARIES - Link these to use Sqlite3
#  CMSIS_FO_DEFINITIONS - Compiler switches required for using Sqlite3
#
#  Copyright (c) 2008 Andreas Schneider <mail@cynapses.org>
#
#  Redistribution and use is allowed according to the terms of the New
#  BSD license.
#  For details see the accompanying COPYING-CMAKE-SCRIPTS file.
#


if (CMSIS_FO_LIBRARIES AND CMSIS_FO_INCLUDE_DIRS)
    # in cache already
    set(CMSIS_FO_FOUND TRUE)
else (CMSIS_FO_LIBRARIES AND CMSIS_FO_INCLUDE_DIRS)
    find_path(CMSIS_FO_INCLUDE_DIR
            NAMES
            sqlite3.h
            PATHS
            ${_CMSIS_FO_INCLUDEDIR}
            /usr/include
            /usr/local/include
            /opt/local/include
            /sw/include
            ~/projects/sqlite/src
            )

    find_library(CMSIS_FO_LIBRARY
            NAMES
            sqlite3
            libsqlite3.so
            PATHS
            ${_CMSIS_FO_LIBDIR}
            /usr/lib
            /usr/local/lib
            /opt/local/lib
            /sw/lib
            ~/projects/sqlite/build
            )

    if (CMSIS_FO_LIBRARY)
        set(CMSIS_FO_FOUND TRUE)
    endif (CMSIS_FO_LIBRARY)

    set(CMSIS_FO_INCLUDE_DIRS
            ${CMSIS_FO_INCLUDE_DIR}
            )

    if (CMSIS_FO_FOUND)
        set(CMSIS_FO_LIBRARIES
                ${CMSIS_FO_LIBRARIES}
                ${CMSIS_FO_LIBRARY}
                )
    endif (CMSIS_FO_FOUND)

    if (CMSIS_FO_INCLUDE_DIRS AND CMSIS_FO_LIBRARIES)
        set(CMSIS_FO_FOUND TRUE)
    endif (CMSIS_FO_INCLUDE_DIRS AND CMSIS_FO_LIBRARIES)

    if (CMSIS_FO_FOUND)
        if (NOT CMSIS_FO_FIND_QUIETLY)
            message(STATUS "Found Sqlite3: ${CMSIS_FO_LIBRARIES}")
        endif (NOT CMSIS_FO_FIND_QUIETLY)
    else (CMSIS_FO_FOUND)
        if (CMSIS_FO_FIND_REQUIRED)
            message(FATAL_ERROR "Could not find Sqlite3")
        endif (CMSIS_FO_FIND_REQUIRED)
    endif (CMSIS_FO_FOUND)

    # show the CMSIS_FO_INCLUDE_DIRS and CMSIS_FO_LIBRARIES variables only in the advanced view
    mark_as_advanced(CMSIS_FO_INCLUDE_DIRS CMSIS_FO_LIBRARIES)

endif (CMSIS_FO_LIBRARIES AND CMSIS_FO_INCLUDE_DIRS)