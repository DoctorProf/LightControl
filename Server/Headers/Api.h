#pragma once
#include "Validator.h"
#include "Parser.h"

class Api 
{
public:
	Api(crow::SimpleApp& app);
private:
	void registerRoutes(crow::SimpleApp& app);
	crow::response settings(crow::request req);
	crow::response modes(crow::request req);
	crow::response mode(crow::request req);
};