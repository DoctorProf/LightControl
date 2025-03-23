//#include "mode.h"
//#include <cmath>
//
//static int type = 0;
//static int r = 255, g = 0, b = 0;
//static float speed = 0.0f;
//static int wave_length = 0;
//
//extern "C" {
//	LED_API int getType()
//	{
//		return type ? 1 : 0;
//	}
//
//	LED_API void setColor(int red, int green, int blue)
//	{
//		r = (red < 0) ? 0 : (red > 255) ? 255 : red;
//		g = (green < 0) ? 0 : (green > 255) ? 255 : green;
//		b = (blue < 0) ? 0 : (blue > 255) ? 255 : blue;
//	}
//
//	LED_API void setSpeed(float new_speed)
//	{
//		speed = (new_speed < 0.0f) ? 0.0f : (new_speed > 1.0f) ? 1.0f : new_speed;
//	}
//
//	LED_API void setWaveLength(int length)
//	{
//		wave_length = (length < 1) ? 1 : length;
//	}
//
//	LED_API int getColor()
//	{
//		return (r << 16) | (g << 8) | b;
//	}
//}