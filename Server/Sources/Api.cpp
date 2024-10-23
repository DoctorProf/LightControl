#include "../Headers/Api.h"

Api::Api(crow::SimpleApp& app) 
{
	registerRoutes(app);
}
void Api::registerRoutes(crow::SimpleApp& app) 
{
    CROW_ROUTE(app, "/settings")
        .methods(crow::HTTPMethod::Get)
        ([this](crow::request req) {
        return settings(req);
            });
    CROW_ROUTE(app, "/modes")
        .methods(crow::HTTPMethod::Get)
        ([this](crow::request req) {
        return modes(req);
            });
    CROW_ROUTE(app, "/mode")
        .methods(crow::HTTPMethod::Get)
        ([this](crow::request req) {
        return mode(req);
            });
    CROW_ROUTE(app, "/mode")
        .methods(crow::HTTPMethod::Post)
        ([this](crow::request req) {
        return mode(req);
            });
    CROW_ROUTE(app, "/mode")
        .methods(crow::HTTPMethod::Delete)
        ([this](crow::request req) {
        return mode(req);
            });
}
crow::response Api::settings(crow::request req) 
{
    json response;
    std::cout << req.raw_url;
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
    else 
    {
        return crow::response(ConfigController::getSettings().dump());
    }
}
crow::response Api::modes(crow::request req) 
{
    return crow::response(ConfigController::getModes().dump());
}
crow::response Api::mode(crow::request req) 
{
    json response;
    switch (req.method)
    {
    case crow::HTTPMethod::Get:
        break;
    case crow::HTTPMethod::Post:
        break;
    case crow::HTTPMethod::Delete:
        break;
    default:
        response["ok"] = false;
        response["description"] = "Invalid http method";
        return crow::response(response.dump());
    }
}
//crow::response Api::addMode(crow::request req)
//{
//    json response;
//    response = validator::addMode(req);
//    return crow::response(response.dump());
//}
//crow::response Api::deleteMode(crow::request req) 
//{
//
//}
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