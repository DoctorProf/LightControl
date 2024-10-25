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
    if (req.url_params.keys().size())
    {
        if (req.url_params.keys().size() > 1)
        {
            response["ok"] = false;
            response["description"] = "More than one parameter";
            return crow::response(response.dump());
        }
        for (auto key : req.url_params.keys())
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
    if (req.url_params.keys().size())
    {
        if (req.url_params.keys().size() > 1)
        {
            response["ok"] = false;
            response["description"] = "More than one parameter";
            return crow::response(response.dump());
        }
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
//crow::response Api::setModeParameter(crow::request req)
//{
//    json response;
//    auto parameter_name = req.url_params.get("parameter_name");
//    auto value = req.url_params.get("value");
//    if (!validator::checkCorrectParameters(ConfigController::getCurrentModeOptions(), { parameter_name }))
//    {
//        response["ok"] = false;
//        response["description"] = "Invalid parameter name";
//        return crow::response(response.dump());
//    }
//    if (!validator::missingParameter(value)) 
//    {
//        response["ok"] = false;
//        response["description"] = "Missing parameters";
//        return crow::response(response.dump());
//    }
//    ConfigController::updateOptions(value, parameter_name);
//    ConfigController::loadSettings();
//    response["ok"] = true;
//    response["description"] = std::format("{} set to {}", parameter_name, value);
//    ConfigController::setChangeOptions(true);
//    return crow::response(response.dump());
//}