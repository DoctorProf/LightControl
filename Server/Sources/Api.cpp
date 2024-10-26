#include "../Headers/Api.h"

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
	CROW_ROUTE(app, "/mode")
		.methods(crow::HTTPMethod::Get)
		([this](crow::request req) {
		return modeGet(req);
			});
	CROW_ROUTE(app, "/mode")
		.methods(crow::HTTPMethod::Post)
		([this](crow::request req) {
		return modePost(req);
			});
	CROW_ROUTE(app, "/mode")
		.methods(crow::HTTPMethod::Delete)
		([this](crow::request req) {
		return modeDelete(req);
			});
}
crow::response Api::getSettings(crow::request req)
{
	return crow::response(ConfigController::getSettings().dump());
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
	else
	{
		for (auto key : keys)
		{
			auto parameter = req.url_params.get(key);
			return crow::response(validator::setSettingsParameter(key, parameter).dump());
		}
	}
}
crow::response Api::modes(crow::request req)
{
	return crow::response(ConfigController::getModes().dump());
}
crow::response Api::modeGet(crow::request req)
{
	json response;
	std::vector<std::string> keys = req.url_params.keys();
	if (keys.size() != 1)
	{
		response["status"] = "Error";
		response["description"] = "More/less than one parameter";
		return crow::response(response.dump());
	}
	else
	{
		for (auto key : req.url_params.keys())
		{
			auto parameter = req.url_params.get(key);
			return crow::response(validator::setModeParameter(key, parameter).dump());
		}
	}
}
crow::response Api::modePost(crow::request req)
{
	return crow::response(validator::addMode(req).dump());
}
crow::response Api::modeDelete(crow::request req)
{
	return crow::response(validator::deleteMode(req).dump());
}