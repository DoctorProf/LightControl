#pragma once
#include <iostream>
#include <mutex>
#include <fstream>
#include <filesystem>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
namespace fs = std::filesystem;

class ConfigController
{
private:
	ConfigController() = default;

	static ConfigController* instance;

	json config;
	std::string subnet_prefix;
	int server_port;
	int led_count;
	int brightness;
	std::string mode_name;
	int state;
	json mode_params;
	std::string path_mode_params;

	int is_changed;
	int* change_handler = nullptr;

	std::mutex config_mutex;

public:
	static ConfigController* getInstance();

	void readConfig();
	void saveConfig();
	void saveModeParams();
	void updateParameter(std::string param_name);
	void loadData();
	int* getChangeHandler();

	json getSettings();
	json getModeParams();

	void updateSettings(std::string param_name, int value);
	void updateSettings(std::string param_name, std::string value);

	void updateParamsMode(std::string param_name, std::string internal_param, int value);
	void updateParamsMode(std::string param_name, std::string internal_param, std::string value);
	void updateParamsMode(std::string param_name, std::string internal_param, float value);

	std::vector<std::string> getModesNames();

	std::string getSubnetPrefix();
	int getServerPort();
	int getLedCount();
	int getBrightness();
	std::string getModeName();
	int getState();
};