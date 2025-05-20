#pragma once
#include <iostream>
#include <string>
#include <httplib.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class Server
{
public:
	Server() = default;
	Server(std::string base_url, int port);

	json getSettings();
	void setSettings(std::string parameter_name, float value);
	void setSettings(std::string parameter_name, std::string value);

	json getModes();

	json getModeParams();
	void setModeParams(std::string parameter_name, std::string internal_param, float parameter);
	void setModeParams(std::string parameter_name, std::string internal_param, std::string parameter);

private:
	httplib::Client server;
};