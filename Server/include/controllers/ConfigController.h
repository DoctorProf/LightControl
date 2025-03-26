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
	json config;
	int led_count;
	int brightness;
	float speed;
	float length_wave;
	std::string mode_name;
	int state;
	std::mutex config_mutex;
	bool is_changed;
	bool* change_handler = nullptr;
	static ConfigController* instance;

public:
	static ConfigController* getInstance();

	void readConfig();
	void saveConfig();
	void updateData();
	bool* getChangeHandler();
	void updateSettings(std::string parameter_name, int value);
	void updateSettings(std::string parameter_name, std::string value);
	void updateSettings(std::string parameter_name, float value);
	std::vector<std::string> getModesNames();
	json getSettings();
	std::string getAddressClient();
	int getLedCount();
	int getBrightness();
	float getSpeed();
	float getLengthWave();
	std::string getModeName();
	int getState();
};