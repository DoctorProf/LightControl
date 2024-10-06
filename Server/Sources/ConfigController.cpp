#include "../Headers/ConfigController.h"

void ConfigController::updateConfig()
{
	is_updated = false;
	config = json::parse(std::ifstream("config.json"));
	is_updated = true;
}
int ConfigController::ConfigController::addMode(json mode) 
{
	int mode_id = config["modes"].size();
	mode["id"] = mode_id;
	config["modes"].push_back(mode);
	std::ofstream output_file("config.json");
	output_file << config.dump(4);
	output_file.close();
	updateConfig();
	return mode_id;
}
int ConfigController::ConfigController::updateParameter(int value, std::string name_parameter) 
{
	config["info"][name_parameter] = value;

	std::ofstream output_file("config.json");
	output_file << config.dump(4);
	output_file.close();
	updateConfig();
	return value;
}
bool ConfigController::isUpdated() 
{
	return is_updated;
}
json ConfigController::getConfig()
{
	return config;
}
json ConfigController::getInfo()
{
	return config["info"];
}
json ConfigController::getModes()
{
	return config["modes"];
}