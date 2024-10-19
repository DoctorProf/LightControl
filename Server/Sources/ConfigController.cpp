#include "../Headers/ConfigController.h"

json ConfigController::config;
json ConfigController::current_mode;
int ConfigController::mode_id;
int ConfigController::brightness;
int ConfigController::state;
std::mutex ConfigController::config_mutex;

void ConfigController::updateParameters() 
{
	mode_id = config["info"]["mode_id"];
	current_mode = config["modes"][mode_id];
	brightness = config["info"]["brightness"];
	state = config["info"]["state"];
}
int ConfigController::ConfigController::addMode(json mode) 
{
	std::lock_guard<std::mutex> lock(config_mutex);
	int mode_id = config["modes"].size();
	mode["id"] = mode_id;
	config["modes"].push_back(mode);
	ConfigController::saveConfigFile("config.json");
	return mode_id;
}
int ConfigController::updateParameter(int value, std::string name_parameter) 
{
	std::lock_guard<std::mutex> lock(config_mutex);
	config["info"][name_parameter] = value;
	ConfigController::saveConfigFile("config.json");
	updateParameters();
	return value;
}
void ConfigController::readConfigFile(std::string file_name)
{
	std::ifstream input_file(file_name);
	config = json::parse(input_file);
	input_file.close();
}
void ConfigController::saveConfigFile(std::string file_name)
{
	std::ofstream output_file(file_name);
	output_file << config.dump(4);
	output_file.close();
}
json &ConfigController::getConfig()
{
	std::lock_guard<std::mutex> lock(config_mutex);
	return config;
}
json ConfigController::getInfo()
{
	std::lock_guard<std::mutex> lock(config_mutex);
	return config["info"];
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