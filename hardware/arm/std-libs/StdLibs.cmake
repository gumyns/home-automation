include_directories(
        ${CMAKE_CURRENT_LIST_DIR}/include
        ${CMAKE_CURRENT_LIST_DIR}/include/cmsis
        ${CMAKE_CURRENT_LIST_DIR}/include/stm32f0xx
        ${CMAKE_CURRENT_LIST_DIR}/include/cmsis/device
)

file(GLOB CMSIS
        ${CMAKE_CURRENT_LIST_DIR}/src/cmsis/*.c
)
file(GLOB CORTEXM
        ${CMAKE_CURRENT_LIST_DIR}/src/cortexm/*.c
)
file(GLOB DIAG
        ${CMAKE_CURRENT_LIST_DIR}/src/diag/*.c
)
file(GLOB NEWLIB
        ${CMAKE_CURRENT_LIST_DIR}/src/newlib/*.c
        ${CMAKE_CURRENT_LIST_DIR}/src/newlib/*.cpp
)
file(GLOB HAL
        ${CMAKE_CURRENT_LIST_DIR}/src/stm32f0xx/*.c
)

set(ARM_LIBRARY_SOURCES ${CMSIS} ${CORTEXM} ${DIAG} ${NEWLIB} ${HAL})