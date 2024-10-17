#include "../Headers/ConfigController.h"

json ConfigController::config;
//json ConfigController::current_mode;
//int ConfigController::mode_id;
//int ConfigController::brightness;
//int ConfigController::state;
std::mutex ConfigController::config_mutex;

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
//int ConfigController::getBrightness() 
//{
//	return brightness;
//}
//int ConfigController::getCurrentModeId() 
//{
//	return mode_id;
//}
//json ConfigController::getCurrentMode() 
//{
//	return current_mode;
//}
//int ConfigController::getState() 
//{
//	return state;
//}