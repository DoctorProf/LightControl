#include "rainbow.h"
#include <cmath>
#include <algorithm>
#include <cstring>
#include <iostream>

static int type_mode = 0;
static std::vector<int> dynamic_color;
static int led_count;

static int r = 255;
static int g = 0;
static int b = 0;

static float speed = 0.f;
static float wave_lenght = 0.f;

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
	LED_API void setParameters(const char* params)
	{
		auto params_json = json::parse(params);
		speed = params_json["speed"]["value"];
		wave_lenght = params_json["wave_lenght"]["value"];
	}
	LED_API int getStaticColor()
	{
		return (r << 16) | (g << 8) | b;
	}
	LED_API void getDynamicColor(int* output)
	{
		static int counter = 0;
		counter += speed;
		for (int i = 0; i < led_count; ++i)
		{
			auto color = HSVToRGB((float)fmod(360.f * (i * wave_lenght / led_count) + counter, 360), 1, 1);
			dynamic_color[i * 3] = color.at(0);
			dynamic_color[i * 3 + 1] = color.at(1);
			dynamic_color[i * 3 + 2] = color.at(2);
		}
		memcpy(output, dynamic_color.data(), dynamic_color.size() * sizeof(int));
	}
}