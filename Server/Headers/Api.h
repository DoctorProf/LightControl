#pragma once
#include "Validator.h"
#include "Parser.h"

class Api 
{
public:
	Api(crow::SimpleApp& app);
private:
	void registerRoutes(crow::SimpleApp& app);
	crow::response getSettings(crow::request req);
	crow::response setSettings(crow::request req);
	crow::response modes(crow::request req);
	crow::response modeGet(crow::request req);
	crow::response modePost(crow::request req);
	crow::response modeDelete(crow::request req);
};