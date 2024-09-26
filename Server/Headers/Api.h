#pragma once
#include <iostream>
#include <nlohmann/json.hpp>
#include <crow/app.h>

using json = nlohmann::json;

class Api 
{
public:
	Api(crow::SimpleApp& app);
private:
	void registerRoutes(crow::SimpleApp& app);

	crow::response getInfo(crow::request req);
	crow::response getModes(crow::request req);
	crow::response setBrightness(crow::request req);
};