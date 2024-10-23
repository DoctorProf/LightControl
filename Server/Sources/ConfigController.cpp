#include "../Headers/ConfigController.h"

json ConfigController::config;
json ConfigController::current_mode;
json ConfigController::current_mode_options;
int ConfigController::mode_id;
int ConfigController::brightness;
int ConfigController::state;
std::mutex ConfigController::config_mutex;
bool ConfigController::change_options = false;

void ConfigController::readConfig(std::string file_name)
{
	std::ifstream input_file(file_name);
	config = json::parse(input_file);
	input_file.close();
}
void ConfigController::saveConfig(std::string file_name)
{
	std::ofstream output_file(file_name);
	output_file << config.dump(4);
	output_file.close();
}

bool ConfigController::isChangeOptions()
{
	return change_options;
}
void ConfigController::setChangeOptions(bool state)
{
	change_options = state;
}

void ConfigController::loadSettings()
{
	mode_id = config["settings"]["mode_id"];
	brightness = config["settings"]["brightness"];
	state = config["settings"]["state"];
	for (auto& mode : config["modes"]) 
	{
		if (mode["id"] == mode_id)
		{
			std::cout << "Mode found" << std::endl;
			current_mode = mode;
			current_mode_options = current_mode["options"];
			return;
		}
	}
	std::cout << "Mode not found." << std::endl;
}
void ConfigController::updateSettings(int value, std::string parameter_name)
{
	std::lock_guard<std::mutex> lock(config_mutex);
	config["settings"][parameter_name] = value;
	ConfigController::saveConfig("config.json");
	loadSettings();
}
void ConfigController::updateOptions(char* value, std::string parameter_name)
{
	std::lock_guard<std::mutex> lock(config_mutex);
	config["modes"][mode_id]["options"][parameter_name] = value;
	ConfigController::saveConfig("config.json");
	change_options = true;
}
int ConfigController::ConfigController::addMode(json mode) 
{
	std::lock_guard<std::mutex> lock(config_mutex);
	int mode_id = config["modes"].size();
	mode["id"] = mode_id;
	config["modes"].push_back(mode);
	ConfigController::saveConfig("config.json");
	return mode_id;
}

json &ConfigController::getConfig()
{
	std::lock_guard<std::mutex> lock(config_mutex);
	return config;
}
json ConfigController::getSettings()
{
	std::lock_guard<std::mutex> lock(config_mutex);
	return config["settings"];
}
json ConfigController::getModes()
{
	std::lock_guard<std::mutex> lock(config_mutex);
	return config["modes"];
}
int ConfigController::getBrightness() 
{
	std::lock_guard<std::mutex> lock(config_mutex);
	return brightness;
}
int ConfigController::getCurrentModeId() 
{
	std::lock_guard<std::mutex> lock(config_mutex);
	return mode_id;
}
json ConfigController::getCurrentMode() 
{
	std::lock_guard<std::mutex> lock(config_mutex);
	return current_mode;
}
int ConfigController::getState() 
{
	std::lock_guard<std::mutex> lock(config_mutex);
	return state;
}
json ConfigController::getCurrentModeOptions()
{
	return current_mode_options;
}
