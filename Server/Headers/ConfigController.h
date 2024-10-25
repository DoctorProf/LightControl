#pragma once
#include <iostream>
#include <mutex>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class ConfigController 
{
public:
	static void readIp();
	static void readModes();
	static void readSettings();

	static void saveModes();
	static void saveSettings();

	static bool updateCurrentData();

	static bool isChange();
	static void setIsChange(bool state);

	static void updateSettings(std::string parameter_name, int value);
	static void updateModeOptions(std::string parameter_name, char* value);

	static int addMode(json mode);
	static void deleteMode();

	static json getModes();
	static json getSettings();
	static int getPortServer();
	static std::string getIpClient();
	static int getBrightness();
	static int getCurrentModeId();
	static int getState();
	static int getCountModes();
	static json getCurrentMode();
	static json getCurrentModeOptions();
private:
	static json ip;
	static json modes;
	static json settings;
	static int brightness;
	static int mode_id;
	static int state;
	static json current_mode;
	static json current_mode_options;
	static int count_modes;
	static bool is_change;
	static std::mutex config_mutex;
};