#pragma once
#include <httplib.h>
class Client
{
public:
	Client(std::string base_url);
	void setLedColors(std::vector<int> colors);
	bool setStripColor(int r, int g, int b);
private:
	httplib::Client client;
};