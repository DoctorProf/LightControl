#pragma once
#include "Validator.h"

class Api 
{
public:
	Api(crow::SimpleApp& app);
private:
	void registerRoutes(crow::SimpleApp& app);

	crow::response setState(crow::request req);
	crow::response getInfo(crow::request req);
	crow::response getModes(crow::request req);
	crow::response setBrightness(crow::request req);
	crow::response selectMode(crow::request req);
	crow::response addMode(crow::request req);

	crow::response setLedColors(crow::request req);
};