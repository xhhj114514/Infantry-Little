cmake_minimum_required(VERSION 3.10)  # 降低到更常见的版本

set(MODNAME LED)
project(${MODNAME})

# 创建 INTERFACE 库
add_library(${MODNAME} INTERFACE)

# 自动收集当前目录下的所有源文件
file(GLOB SOURCES 
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.c"  # 如果有C文件也包含
)

# 将找到的源文件添加到库中
target_sources(${MODNAME} INTERFACE
    ${SOURCES}
)

# 设置包含目录为当前目录
target_include_directories(${MODNAME} INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# 可选：打印找到的文件，方便调试
message(STATUS "LED module sources: ${SOURCES}")
message(STATUS "LED module include directory: ${CMAKE_CURRENT_SOURCE_DIR}")
