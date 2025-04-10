#pragma once
#include "../validators/ValidatorApi.h"
#include "../utils/ColorUtils.h"

class Api
{
public:
	Api(crow::SimpleApp& app);
private:
	void registerRoutes(crow::SimpleApp& app);
	crow::response getSettings(crow::request req);
	crow::response setSettings(crow::request req);
	crow::response modes(crow::request req);
	crow::response getModeParams(crow::request req);
	crow::response setModeParams(crow::request req);
};