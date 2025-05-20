#include "../../include/network/Client.h"

Client::Client(std::string base_url) : client(base_url)
{
	client.set_connection_timeout(5);
	client.set_keep_alive(true);
}
void Client::setLedColors(std::vector<int> colors)
{
	std::string color_data(colors.begin(), colors.end());
	auto res = client.Post("/setLedColors", color_data, "text/plain");
}
bool Client::setStripColor(int r, int g, int b)
{
	std::string url = "/setStripColor?r=" + std::to_string(r) + "&g=" + std::to_string(g) + "&b=" + std::to_string(b);
	auto res = client.Get(url.c_str());
	if (res)
	{
		return true;
	}
	else
	{
		return false;
	}
}