#pragma once
#include <vector>
#include <array>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

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
	LED_API int getStaticColor();
	LED_API void getDynamicColor(int* output);
}