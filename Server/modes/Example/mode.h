//#pragma once
//
//#ifdef _WIN32
//#ifdef LED_CONTROLLER_EXPORT
//#define LED_API __declspec(dllexport)
//#else
//#define LED_API __declspec(dllimport)
//#endif
//#else
//#define LED_API
//#endif
//
//extern "C"
//{
//	LED_API int getType();
//	LED_API void setColor(int red, int green, int blue);
//	LED_API void setSpeed(float speed);
//	LED_API void setWaveLength(int length);
//	LED_API int getColor();
//}
