#pragma once
#include <iostream>
#include <vector>
#include <sstream>

namespace utils
{
	std::vector<int> HEXToRGB(std::string hex);
	std::vector<int> HSVToRGB(std::vector<float> hsv);
	std::vector<int> INTToRGB(int color);
}