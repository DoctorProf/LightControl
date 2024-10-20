#pragma once
#include <iostream>
#include <mutex>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class ConfigController 
{
public:
	static void updateParameters();
	static int addMode(json mode);
	static int updateParameter(int value, std::string name_parameter);

	static void readConfigFile(std::string file_name);
	static void saveConfigFile(std::string file_name);
	static json &getConfig();
	static json getInfo();
	static json getModes();
	static int getBrightness();
	static int getCurrentModeId();
	static json getCurrentMode();
	static int getState();
	static json getCurrentModeOptions();
private:
	static json config;
	static int mode_id;
	static int brightness;
	static int state;
	static json current_mode;
	static json current_mode_options;
	static std::mutex config_mutex;
};