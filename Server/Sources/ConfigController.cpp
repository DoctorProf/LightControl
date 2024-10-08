#include "../Headers/ConfigController.h"

json ConfigController::config = json::object();
std::mutex ConfigController::config_mutex;
void ConfigController::updateConfig()
{
	std::unique_lock<std::mutex> lock(config_mutex, std::defer_lock);
	if (lock.try_lock()) {
		config = json::parse(std::ifstream("config.json"));
		lock.unlock();
	}
}
int ConfigController::ConfigController::addMode(json mode) 
{
	std::lock_guard<std::mutex> lock(config_mutex);
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
	std::lock_guard<std::mutex> lock(config_mutex);
	config["info"][name_parameter] = value;
	std::ofstream output_file("config.json");
	output_file << config.dump(4);
	output_file.close();
	updateConfig();
	return value;
}
json ConfigController::getConfig()
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