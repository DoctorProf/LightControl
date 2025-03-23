#pragma once
#include <iostream>
#include <mutex>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class ConfigController
{
private:
	ConfigController() = default;
	json config;
	int brightness;
	std::string mode_name;
	int state;
	std::mutex config_mutex;

	static ConfigController* instance;

public:
	static ConfigController* getInstance();

	void readConfig();
	void saveConfig();
	void updateData();
	void updateSettings(std::string parameter_name, int value);
	void updateSettings(const std::string& parameter_name, std::string value);
	json getSettings();
	std::string getAddressClient();
	int getBrightness();
	std::string getModeName();
	int getState();
};