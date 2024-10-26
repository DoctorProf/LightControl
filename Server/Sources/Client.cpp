#include "../Headers/Client.h"

Client::Client(std::string base_url) : client(base_url)
{
}
bool Client::setLedColors(std::vector<int> colors)
{
	std::string color(colors.begin(), colors.end());
	httplib::Result res = client.Post("/setLedColors", color, "application/octet-stream");
	if (res)
	{
		std::cout << "Successful request" << std::endl;
		return true;
	}
	else
	{
		std::cout << "Failed request" << std::endl;
		return false;
	}
}
bool Client::setStripColor(int r, int g, int b)
{
	std::string url = "/setStripColor?r=" + std::to_string(r) + "&g=" + std::to_string(g) + "&b=" + std::to_string(b);
	auto res = client.Get(url.c_str());
	if (res)
	{
		std::cout << "Successful request" << std::endl;
		return true;
	}
	else
	{
		std::cout << "Failed request" << std::endl;
		return false;
	}
}