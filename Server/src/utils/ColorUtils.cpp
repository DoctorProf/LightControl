#include "../../include/utils/ColorUtils.h"
#include <cmath>

std::vector<int> utils::HEXToRGB(std::string hex)
{
	if (hex[0] == '#')
	{
		hex = hex.substr(1);
	}
	unsigned int color;
	std::stringstream ss;
	ss << std::hex << hex;
	ss >> color;

	return INTToRGB(color);
}
std::vector<int> utils::HSVToRGB(std::vector<float> hsv)
{
	float h = hsv[0];
	float s = hsv[1];
	float v = hsv[2];
	float c = v * s;
	float x = c * (1 - fabs(fmod(h / 60.f, 2) - 1));
	float m = v - c;
	std::vector<float> rgb_;
	if (h >= 0 && h < 60) rgb_ = { c, x, 0 };
	if (h >= 60 && h < 120) rgb_ = { x, c, 0 };
	if (h >= 120 && h < 180) rgb_ = { 0, c, x };
	if (h >= 180 && h < 240) rgb_ = { 0, x, c };
	if (h >= 240 && h < 300) rgb_ = { x, 0, c };
	if (h >= 300 && h <= 360) rgb_ = { c, 0, x };

	return { (int)((rgb_[0] + m) * 255), (int)((rgb_[1] + m) * 255), (int)((rgb_[2] + m) * 255) };
}
std::vector<int> utils::INTToRGB(int color)
{
	int r = (color >> 16) & 0xFF;
	int g = (color >> 8) & 0xFF;
	int b = color & 0xFF;
	return { r, g, b };
}