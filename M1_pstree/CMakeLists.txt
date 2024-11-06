

find_package(Curses REQUIRED)  # 查找 ncurses 库
include_directories(${CURSES_INCLUDE_DIRS})
include_directories(${PROJECT_SOURCE_DIR}/M1_pstree)

add_executable(pstree
        M1_pstree.cpp
        id.cpp
)

target_link_libraries(pstree ${CURSES_LIBRARIES})