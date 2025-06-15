#include "../../include/network/Client.h"

Client::Client()
{
	bool run = true;
	while (run)
	{
		std::string ip = findESP();
		if (!ip.empty())
		{
			client = std::make_unique<httplib::Client>(ip.c_str(), 80);
			client->set_keep_alive(true);
			run = false;
		}
	}
}
void Client::setLedColors(std::vector<int>& colors)
{
	std::string body(colors.begin(), colors.end());
	auto res = client->Post("/setLedColors", body, "application/octet-stream");
}
bool Client::setStripColor(int r, int g, int b)
{
	std::string url = "/setStripColor?r=" + std::to_string(r) + "&g=" + std::to_string(g) + "&b=" + std::to_string(b);
	auto res = client->Get(url.c_str());
	if (res)
	{
		return true;
	}
	else
	{
		return false;
	}
}
std::string Client::findESP()
{
	std::string submet_prefix = ConfigController::getInstance()->getSubnetPrefix();
	for (int i = 1; i < 255; ++i)
	{
		std::string ip = submet_prefix + std::to_string(i);
		std::cout << "Check IP: " << ip << std::endl;
		if (checkESP(ip))
		{
			std::cout << "ESP finded to address: " << ip << std::endl;
			return ip;
		}
	}
	return "";
}
bool Client::checkESP(std::string& ip)
{
	httplib::Client temp(ip, 80);
	temp.set_connection_timeout(std::chrono::milliseconds(200));
	if (auto res = temp.Get("/ping"))
	{
		return res->status == 200 && res->body == "esp_ok";
	}
	return false;
}