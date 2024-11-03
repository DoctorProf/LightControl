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
	json ip;
	json modes;
	json settings;
	int brightness;
	int mode_id;
	int state;
	json current_mode;
	int count_modes;
	bool is_change;
	std::mutex config_mutex;

	static ConfigController* instance;

public:
	static ConfigController* getInstance();

	void readIp();
	void readModes();
	void readSettings();

	void saveModes();
	void saveSettings();

	bool updateCurrentData();

	bool isChange();
	void setIsChange(bool state);

	void updateSettings(std::string parameter_name, int value);
	void updateModeOptions(std::string parameter_name, char* value);

	int addMode(json mode);
	void deleteMode();

	json getModes();
	json getSettings();
	int getPortServer();
	std::string getIpClient();
	int getBrightness();
	int getModeId();
	int getState();
	int getCountModes();
	json getCurrentMode();
};