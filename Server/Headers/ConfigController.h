#pragma once
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class ConfigController {

public:
	static void updateConfig();
	static int addMode(json mode);
	static int updateParameter(int value, std::string name_parameter);

	static bool isUpdated();
	static json getConfig();
	static json getInfo();
	static json getModes();
private:
	static json config;
	static bool is_updated;
};