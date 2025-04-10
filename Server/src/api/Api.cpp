#include "../../include/api/Api.h"

Api::Api(crow::SimpleApp& app)
{
	registerRoutes(app);
}
void Api::registerRoutes(crow::SimpleApp& app)
{
	CROW_ROUTE(app, "/getSettings")
		.methods(crow::HTTPMethod::Get)
		([this](crow::request req) {
		return getSettings(req);
			});
	CROW_ROUTE(app, "/setSettings")
		.methods(crow::HTTPMethod::Get)
		([this](crow::request req) {
		return setSettings(req);
			});
	CROW_ROUTE(app, "/modes")
		.methods(crow::HTTPMethod::Get)
		([this](crow::request req) {
		return modes(req);
			});
	CROW_ROUTE(app, "/getModeParams")
		.methods(crow::HTTPMethod::Get)
		([this](crow::request req) {
		return getModeParams(req);
			});
	CROW_ROUTE(app, "/setModeParams")
		.methods(crow::HTTPMethod::Get)
		([this](crow::request req) {
		return setModeParams(req);
			});
}
crow::response Api::getSettings(crow::request req)
{
	return crow::response(ConfigController::getInstance()->getSettings().dump());
}
crow::response Api::setSettings(crow::request req)
{
	json response;
	std::vector<std::string> keys = req.url_params.keys();
	if (keys.size() != 1)
	{
		response["status"] = "Error";
		response["description"] = "More/less than one parameter";
		return crow::response(response.dump());
	}
	auto key = keys[0];
	auto parameter = req.url_params.get(key);
	return crow::response(validator_api::setSettingsParameter(key, parameter).dump());
}
crow::response Api::modes(crow::request req)
{
	json modes;
	modes["modes"] = ConfigController::getInstance()->getModesNames();
	return crow::response(modes.dump());
}
crow::response Api::getModeParams(crow::request req)
{
	return crow::response(ConfigController::getInstance()->getModeParams().dump());
}
crow::response Api::setModeParams(crow::request req)
{
	json response;
	std::vector<std::string> keys = req.url_params.keys();
	if (keys.size() != 2)
	{
		response["status"] = "Error";
		response["description"] = "More/less than two parameter";
		return crow::response(response.dump());
	}
	auto parameter_name = req.url_params.get(keys[0]);
	auto internal_param = keys[1];
	auto value = req.url_params.get(internal_param);
	return crow::response(validator_api::setModeParameter(parameter_name, internal_param, value).dump());
}