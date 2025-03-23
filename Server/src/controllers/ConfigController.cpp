#include "../../include/controllers/ConfigController.h"

ConfigController* ConfigController::instance = nullptr;

ConfigController* ConfigController::getInstance()
{
	if (!instance)
	{
		instance = new ConfigController();
	}
	return instance;
}
void ConfigController::readConfig()
{
	std::ifstream input_file("config.json");
	config = json::parse(input_file);
	input_file.close();
}
void ConfigController::saveConfig()
{
	std::ofstream output_file("config.json");
	output_file << config.dump(4);
	output_file.close();
}
void ConfigController::updateData()
{
	brightness = config["led"]["brightness"];
	state = config["led"]["state"];
	mode_name = config["led"]["mode_name"];
}
void ConfigController::updateSettings(std::string parameter_name, int value)
{
	std::lock_guard<std::mutex> lock(config_mutex);
	config["led"][parameter_name] = value;
	saveConfig();
	updateData();
}
void ConfigController::updateSettings(const std::string& parameter_name, std::string value)
{
	std::lock_guard<std::mutex> lock(config_mutex);
	config["led"][parameter_name] = value;
	saveConfig();
	updateData();
}
json ConfigController::getSettings()
{
	std::lock_guard<std::mutex> lock(config_mutex);
	return config["led"];
}
std::string ConfigController::getAddressClient()
{
	std::lock_guard<std::mutex> lock(config_mutex);
	return config["client"]["address"];
}
int ConfigController::getBrightness()
{
	std::lock_guard<std::mutex> lock(config_mutex);
	return brightness;
}
std::string ConfigController::getModeName()
{
	std::lock_guard<std::mutex> lock(config_mutex);
	return mode_name;
}
int ConfigController::getState()
{
	std::lock_guard<std::mutex> lock(config_mutex);
	return state;
}