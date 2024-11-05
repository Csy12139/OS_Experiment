#include "screen.h"
#include <cstdio>
#include <ncurses.h>
#include <string>


void Screen_Write(struct ScreenCursor SCursor, const char *str) {
    move(SCursor.height, SCursor.length); // 移动光标到指定位置
    printw("%s", str); // 打印消息
    refresh(); // 刷新屏幕以显示内容
}

struct ScreenCursor GetCursor() {
    struct ScreenCursor SCursor;
    getyx(stdscr, SCursor.height, SCursor.length);
    return SCursor;
}
