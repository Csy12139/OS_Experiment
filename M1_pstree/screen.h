#ifndef GLUTTONOUS_SNAKE_SCREEN_H
#define GLUTTONOUS_SNAKE_SCREEN_H

#include <ncurses.h>
#include <string>

struct ScreenCursor {
    int height;
    int length;
};

// 在指定位置(height,length)写入str
void Screen_Write(struct ScreenCursor SCursor, const char *str);

// 获取当前光标位置
struct ScreenCursor GetCursor();

#endif //GLUTTONOUS_SNAKE_SCREEN_H
