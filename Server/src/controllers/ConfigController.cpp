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
	speed = config["led"]["speed"];
	length_wave = config["led"]["length_wave"];
	state = config["led"]["state"];
	mode_name = config["led"]["mode_name"];
	led_count = config["led"]["led_count"];
	is_changed = true;
}
bool* ConfigController::getChangeHandler()
{
	if (!change_handler)
	{
		change_handler = &is_changed;
	}
	return change_handler;
}

void ConfigController::updateSettings(std::string parameter_name, int value)
{
	std::lock_guard<std::mutex> lock(config_mutex);
	config["led"][parameter_name] = value;
	saveConfig();
	updateData();
}
void ConfigController::updateSettings(std::string parameter_name, std::string value)
{
	std::lock_guard<std::mutex> lock(config_mutex);
	config["led"][parameter_name] = value;
	saveConfig();
	updateData();
}
void ConfigController::updateSettings(std::string parameter_name, float value)
{
	std::lock_guard<std::mutex> lock(config_mutex);
	config["led"][parameter_name] = value;
	saveConfig();
	updateData();
}
std::vector<std::string> ConfigController::getModesNames()
{
	std::vector<std::string> modes_list;
	std::string modes_dir = "modes";

	if (!fs::exists(modes_dir))
	{
		std::cerr << "Directory 'modes' not found!" << std::endl;
		return modes_list;
	}

	for (auto& entry : fs::directory_iterator(modes_dir))
	{
		if (entry.is_regular_file())
		{
			std::string filename = entry.path().stem().string();
			modes_list.push_back(filename);
		}
	}
	return modes_list;
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
int ConfigController::getLedCount()
{
	std::lock_guard<std::mutex> lock(config_mutex);
	return led_count;
}
int ConfigController::getBrightness()
{
	std::lock_guard<std::mutex> lock(config_mutex);
	return brightness;
}
float ConfigController::getSpeed()
{
	std::lock_guard<std::mutex> lock(config_mutex);
	return speed;
}
float ConfigController::getLengthWave()
{
	std::lock_guard<std::mutex> lock(config_mutex);
	return length_wave;
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