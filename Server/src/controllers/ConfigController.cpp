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
void ConfigController::saveModeParams()
{
	std::ofstream output_file(path_mode_params);
	output_file << mode_params.dump(4);
	output_file.close();
}
void ConfigController::updateParameter(std::string param_name)
{
	if (param_name == "brightness")
	{
		brightness = config["led"]["brightness"];
		is_changed = 1;
	}
	else if (param_name == "mode_name")
	{
		mode_name = config["led"]["mode_name"];
		path_mode_params = "modes/" + mode_name + ".json";
		mode_params = json::parse(std::ifstream(path_mode_params));
		is_changed = 2;
	}
	else if (param_name == "state")
	{
		state = config["led"]["state"];
		is_changed = 3;
	}
	else if (param_name == mode_name)
	{
		is_changed = 4;
	}
}
void ConfigController::loadData()
{
	brightness = config["led"]["brightness"];
	mode_name = config["led"]["mode_name"];
	state = config["led"]["state"];
	path_mode_params = "modes/" + mode_name + ".json";
	mode_params = json::parse(std::ifstream(path_mode_params));
	is_changed = 0;
}
int* ConfigController::getChangeHandler()
{
	if (!change_handler)
	{
		change_handler = &is_changed;
	}
	return change_handler;
}
void ConfigController::updateSettings(std::string param_name, int value)
{
	std::lock_guard<std::mutex> lock(config_mutex);
	config["led"][param_name] = value;
	saveConfig();
	updateParameter(param_name);
}
void ConfigController::updateSettings(std::string param_name, std::string value)
{
	std::lock_guard<std::mutex> lock(config_mutex);
	config["led"][param_name] = value;
	saveConfig();
	updateParameter(param_name);
}
void ConfigController::updateParamsMode(std::string param_name, std::string internal_param, int value)
{
	std::lock_guard<std::mutex> lock(config_mutex);
	mode_params[param_name][internal_param] = value;
	saveModeParams();
	updateParameter(mode_name);
}
void ConfigController::updateParamsMode(std::string param_name, std::string internal_param, std::string value)
{
	std::lock_guard<std::mutex> lock(config_mutex);
	mode_params[param_name][internal_param] = value;
	saveModeParams();
	updateParameter(mode_name);
}
void ConfigController::updateParamsMode(std::string param_name, std::string internal_param, float value)
{
	std::lock_guard<std::mutex> lock(config_mutex);
	mode_params[param_name][internal_param] = value;
	saveModeParams();
	updateParameter(mode_name);
}
std::vector<std::string> ConfigController::getModesNames()
{
	std::vector<std::string> modes_list;
	std::string modes_dir = "modes";

	if (!fs::exists(modes_dir)) {
		std::cerr << "Directory 'modes' not found!" << std::endl;
		return modes_list;
	}

	for (const auto& entry : fs::directory_iterator(modes_dir)) {
		if (entry.is_regular_file()) {
			std::string ext = entry.path().extension().string();
			std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);

			if (ext == ".dll") {
				std::string filename = entry.path().stem().string();
				modes_list.push_back(filename);
			}
		}
	}

	return modes_list;
}
json ConfigController::getSettings()
{
	std::lock_guard<std::mutex> lock(config_mutex);
	return config["led"];
}
json ConfigController::getModeParams()
{
	std::lock_guard<std::mutex> lock(config_mutex);
	return mode_params;
}
std::string ConfigController::getAddressClient()
{
	std::lock_guard<std::mutex> lock(config_mutex);
	return config["client"]["address"];
}
int ConfigController::getLedCount()
{
	std::lock_guard<std::mutex> lock(config_mutex);
	return config["led"]["led_count"];
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