#pragma once
#include <vector>
#include <array>

#ifdef _WIN32
#ifdef LED_CONTROLLER_EXPORT
#define LED_API __declspec(dllexport)
#else
#define LED_API __declspec(dllimport)
#endif
#else
#define LED_API
#endif

extern "C"
{
	LED_API void setLedCount(int count);
	LED_API int getTypeMode();
	LED_API void setStaticColor(int red, int green, int blue);
	LED_API void setSpeed(float new_speed);
	LED_API void setWaveLength(float new_wave_length);
	LED_API int getStaticColor();
	LED_API void getDynamicColor(int* output);
}