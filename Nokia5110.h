#ifndef Nokia5110_H
#define Nokia5110_H

#include "RPiGPIO.h"
#include "RPiSPI.h"

extern void Nokia5110_Initialize(const char *spidev, int reset_pin, int dc_pin);
extern void Nokia5110_Clear(void);
extern void Nokia5110_Flush(void);
extern void Nokia5110_RPi(void);
extern void Nokia5110_DrawString(int x, int y, const char *str);
extern void Nokia5110_DrawLine(int x1, int y1, int x2, int y2, int color);
extern void Nokia5110_FillRect(int x1, int y1, int x2, int y2, int color);
extern void Nokia5110_DrawRect(int x1, int y1, int x2, int y2, int color);
extern void Nokia5110_FillCircle(int x1, int y1, int x2, int y2, int color);
extern void Nokia5110_DrawCircle(int x1, int y1, int x2, int y2, int color);

#endif