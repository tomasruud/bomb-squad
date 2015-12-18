#ifndef COLOR_H_
#define COLOR_H_

#define RGB(R, G, B) ((((R) & 0xF8) << 8) | (((G) & 0xFC) << 3) | ((B) >> 3))

#define COLOR_BG RGB(76, 20, 87)
#define COLOR_TEXT RGB(255, 255, 255)

#define COLOR_GREEN RGB(129, 255, 111)
#define COLOR_RED RGB(248, 18, 18)
#define COLOR_GRAY RGB(24, 24, 24)

#endif
