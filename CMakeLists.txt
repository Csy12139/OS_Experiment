cmake_minimum_required(VERSION 3.20)
project(OS_Experiment)

set(CMAKE_CXX_STANDARD 14)

find_package(Curses REQUIRED)  # 查找 ncurses 库
include_directories(${CURSES_INCLUDE_DIRS})

add_executable(OS_Experiment
        M1_pstree/M1_pstree.cpp
        M1_pstree/id.cpp
        M1_pstree/id.h
        M1_pstree/screen.cpp
        M1_pstree/screen.h
)
target_link_libraries(OS_Experiment ${CURSES_LIBRARIES})