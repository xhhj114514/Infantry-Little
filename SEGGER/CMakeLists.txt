# SEGGER/CMakeLists.txt
cmake_minimum_required(VERSION 3.22)

add_library(SEGGER_RTT INTERFACE)

target_include_directories(SEGGER_RTT
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/RTT
        ${CMAKE_CURRENT_SOURCE_DIR}/Config
)

target_sources(SEGGER_RTT
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/RTT/SEGGER_RTT.c
        ${CMAKE_CURRENT_SOURCE_DIR}/RTT/SEGGER_RTT_printf.c
        ${CMAKE_CURRENT_SOURCE_DIR}/RTT/SEGGER_RTT_ASM_ARMv7M.s
)