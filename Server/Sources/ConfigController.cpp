#include "../Headers/ConfigController.h"

json ConfigController::ip;
json ConfigController::modes;
json ConfigController::settings;
int ConfigController::brightness;
int ConfigController::mode_id;
int ConfigController::state;
json ConfigController::current_mode;
json ConfigController::current_mode_options;
int ConfigController::count_modes;
bool ConfigController::is_change;
std::mutex ConfigController::config_mutex;

void ConfigController::readIp()
{
	std::ifstream input_file("Config/ip.json");
	ip = json::parse(input_file);
	input_file.close();
}
void ConfigController::readModes() 
{
	std::ifstream input_file("Config/modes.json");
	modes = json::parse(input_file);
	input_file.close();
}
void ConfigController::readSettings() 
{
	std::ifstream input_file("Config/settings.json");
	settings = json::parse(input_file);
	input_file.close();
}
void ConfigController::saveModes() 
{
	std::ofstream output_file("Config/modes.json");
	output_file << modes.dump(4);
	output_file.close();
}
void ConfigController::saveSettings()
{
	std::ofstream output_file("Config/settings.json");
	output_file << settings.dump(4);
	output_file.close();
}
bool ConfigController::updateCurrentData()
{
	is_change = true;
	brightness = settings["brightness"];
	mode_id = settings["mode_id"];
	state = settings["state"];
	count_modes = modes.size();
	for (auto& mode : modes)
	{
		if (mode["id"] == mode_id)
		{
			std::cout << "Mode found" << std::endl;
			current_mode = mode;
			current_mode_options = current_mode["options"];
			return true;
		}
	}
	std::cout << "Mode not found." << std::endl;
	return false;
}
bool ConfigController::isChange()
{
	return is_change;
}
void ConfigController::setIsChange(bool state)
{
	is_change = state;
}

void ConfigController::updateSettings(std::string parameter_name, int value)
{
	std::lock_guard<std::mutex> lock(config_mutex);
	settings[parameter_name] = value;
	saveSettings();
	updateCurrentData();
}
void ConfigController::updateModeOptions(std::string parameter_name, char* value)
{
	std::lock_guard<std::mutex> lock(config_mutex);
	modes[mode_id]["options"][parameter_name] = value;
	saveModes();
	updateCurrentData();
}
int ConfigController::addMode(json mode) 
{
	std::lock_guard<std::mutex> lock(config_mutex);
	int mode_id = count_modes;
	mode["id"] = mode_id;
	modes.push_back(mode);
	saveModes();
	updateCurrentData();
	return mode_id;
}
void ConfigController::deleteMode()
{
	std::lock_guard<std::mutex> lock(config_mutex);
	modes.erase(mode_id);
	count_modes--;
	for (int i = mode_id; i < count_modes; ++i) 
	{
		int id = modes[i]["id"];
		modes[i]["id"] = id - 1;
	}
	if (mode_id >= count_modes) 
	{
		int mode_id = settings["mode_id"];
		settings["mode_id"] = mode_id - 1;
	}
	saveModes();
	saveSettings();
	updateCurrentData();
}

json ConfigController::getSettings()
{
	std::lock_guard<std::mutex> lock(config_mutex);
	return settings;
}
json ConfigController::getModes()
{
	std::lock_guard<std::mutex> lock(config_mutex);
	return modes;
}
int ConfigController::getPortServer()
{
	std::lock_guard<std::mutex> lock(config_mutex);
	return ip["server_port"];
}
std::string ConfigController::getIpClient()
{
	std::lock_guard<std::mutex> lock(config_mutex);
	return ip["client_ip"];
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
int ConfigController::getCountModes() 
{
	std::lock_guard<std::mutex> lock(config_mutex);
	return count_modes;
}
json ConfigController::getCurrentModeOptions()
{
	return current_mode_options;
}
