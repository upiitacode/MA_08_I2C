#ifndef _RGBLED_H
#define _RGBLED_H

#define RGB_COLOR_RED (0x1<<1)
#define RGB_COLOR_GREEN (0x1<<3)
#define RGB_COLOR_BLUE (0x1<<2)
#define RGB_COLOR_WHITE (RGB_COLOR_RED | RGB_COLOR_GREEN | RGB_COLOR_BLUE)
#define RGB_COLOR_BLACK (0x00)

class RGBLed{
	public:
		RGBLed();
		void write(int color);
};

#endif// _RGBLED_H
