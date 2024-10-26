#include "../Headers/Parser.h"

std::vector<int> parser::hexToRGB(std::string hex)
{
	if (hex[0] == '#')
	{
		hex = hex.substr(1);
	}
	unsigned int color;
	std::stringstream ss;
	ss << std::hex << hex;
	ss >> color;

	int r = (color >> 16) & 0xFF;
	int g = (color >> 8) & 0xFF;
	int b = color & 0xFF;
	return { r, g, b };
}