cmake_minimum_required(VERSION 3.8)
project(preliminary)

set(CMAKE_CXX_STANDARD 11)

#源文件列表
set(SOURCE_FILES src/main.cpp
        src/GPIOlib.cpp
        header/GPIOlib.h
        src/krayc.cpp)

#头文件列表
set(INC_DIR ./include)

#需要链接库的位置
link_directories(./lib)

add_executable(preliminary ${SOURCE_FILES})