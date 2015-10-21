#ifndef _RGBLED_H
#define _RGBLED_H

class RGBLed{
	public:
		static const int COLOR_BLACK;
		static const int COLOR_RED;
		static const int COLOR_BLUE;
		static const int COLOR_GREEN;
		static const int COLOR_WHITE;

		RGBLed();
		void write(int color);
};

#endif// _RGBLED_H
