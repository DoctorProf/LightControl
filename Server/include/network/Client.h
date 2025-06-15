#pragma once
#include <httplib.h>
#include "../controllers/ConfigController.h"
class Client
{
public:
	Client();
	void setLedColors(std::vector<int>& colors);
	bool setStripColor(int r, int g, int b);
	std::string findESP();
	bool checkESP(std::string& ip);
private:
	std::unique_ptr<httplib::Client> client;
};