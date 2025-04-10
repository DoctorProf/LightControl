#include "white.h"
#include <cmath>
#include <algorithm>
#include <cstring>

static int type_mode = 1;

static int led_count;
static std::vector<int> dynamic_color;

std::array<int, 3> HSVToRGB(float h_value, float s_value, float v_value)
{
	float h = h_value;
	float s = s_value;
	float v = v_value;
	float c = v * s;
	float x = c * (1 - std::abs(fmod(h / 60.f, 2) - 1));
	float m = v - c;
	float r;
	float g;
	float b;
	if (h >= 0 && h < 60)
	{
		r = c;
		g = x;
		b = 0;
	}
	if (h >= 60 && h < 120)
	{
		r = x;
		g = c;
		b = 0;
	}
	if (h >= 120 && h < 180)
	{
		r = 0;
		g = c;
		b = x;
	}
	if (h >= 180 && h < 240)
	{
		r = 0;
		g = x;
		b = c;
	}
	if (h >= 240 && h < 300)
	{
		r = x;
		g = 0;
		b = c;
	}
	if (h >= 300 && h <= 360)
	{
		r = c;
		g = 0;
		b = x;
	}
	return { (int)((r + m) * 255) , (int)((g + m) * 255), (int)((b + m) * 255) };
}
extern "C"
{
	LED_API void setLedCount(int count)
	{
		led_count = count;
		dynamic_color.resize(led_count * 3);
	}
	LED_API int getTypeMode()
	{
		return std::clamp(type_mode, 0, 1);
	}

	LED_API void setStaticColor(int red, int green, int blue)
	{
		static_color[0] = std::clamp(red, 0, 255);
		static_color[1] = std::clamp(green, 0, 255);
		static_color[2] = std::clamp(blue, 0, 255);
	}

	LED_API void setSpeed(float new_speed)
	{
		speed = std::clamp(new_speed, 0.f, (float)led_count);
	}
	LED_API int getStaticColor()
	{
		return (r << 16) | (g << 8) | b;
	}
	LED_API void updateParameters(json parameters)
	{
		r = parameters["color"][0];
		g = parameters["color"][1];
		b = parameters["color"][2];
		speed = parameters["speed"];
	}
	LED_API void getDynamicColor(int* output)
	{
		memcpy(output, dynamic_color.data(), dynamic_color.size() * sizeof(int));
	}
}