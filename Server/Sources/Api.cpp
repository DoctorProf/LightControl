#include "../Headers/Api.h"

Api::Api(crow::SimpleApp& app) 
{
	registerRoutes(app);
}
void Api::registerRoutes(crow::SimpleApp& app) 
{
    CROW_ROUTE(app, "/getInfo")
        .methods(crow::HTTPMethod::Get)
        ([this](crow::request req) {
        return getInfo(req);
            });
    CROW_ROUTE(app, "/getModes")
        .methods(crow::HTTPMethod::Get)
        ([this](crow::request req) {
        return getModes(req);
            });
    CROW_ROUTE(app, "/setState")
        .methods(crow::HTTPMethod::Get)
        ([this](crow::request req) {
        return setState(req);
            });
    CROW_ROUTE(app, "/setBrightness")
        .methods(crow::HTTPMethod::Get)
        ([this](crow::request req) {
        return setBrightness(req);
            });
    CROW_ROUTE(app, "/selectMode")
        .methods(crow::HTTPMethod::Get)
        ([this](crow::request req) {
        return selectMode(req);
            });
    CROW_ROUTE(app, "/addMode")
        .methods(crow::HTTPMethod::Post)
        ([this](crow::request req) {
        return addMode(req);
            }); 
    CROW_ROUTE(app, "/setModeParameter")
        .methods(crow::HTTPMethod::Get)
        ([this](crow::request req) {
        return setModeParameter(req);
            });
    CROW_ROUTE(app, "/deleteMode")
        .methods(crow::HTTPMethod::Delete)
        ([this](crow::request req) {
        return deleteMode(req);
            });
}
crow::response Api::setState(crow::request req) 
{
    json response;
    auto state = req.url_params.get("state");

    if (!validator::missingParameter(state))
    {
        response["ok"] = false;
        response["description"] = "Missing parameter";
        return crow::response(response.dump());
    }

    response = validator::setParameter(state, "state", 0, 1);
    return crow::response(response.dump());
}
crow::response Api::getInfo(crow::request req)
{
    return crow::response(ConfigController::getInfo().dump());
}
crow::response Api::getModes(crow::request req)
{
    return crow::response(ConfigController::getModes().dump());
}
crow::response Api::setBrightness(crow::request req) 
{
    json response;
    auto brightness = req.url_params.get("brightness");
    if (!validator::missingParameter(brightness)) 
    {
        response["ok"] = false;
        response["description"] = "Missing parameter";
        return crow::response(response.dump());
    }
    response = validator::setParameter(brightness, "brightness", 0, 255);
    return crow::response(response.dump());
}
crow::response Api::selectMode(crow::request req)
{
    json response;
    auto mode_id = req.url_params.get("mode_id");
    if (!validator::missingParameter(mode_id))
    {
        response["ok"] = false;
        response["description"] = "Missing parameter";
        return crow::response(response.dump());
    }
    json modes = ConfigController::getModes();
    int count_modes = modes.size();
    response = validator::setParameter(mode_id, "mode_id", modes[0]["id"], modes[count_modes - 1]["id"]);
    return crow::response(response.dump());
}
crow::response Api::addMode(crow::request req)
{
    json response;
    response = validator::addMode(req);
    return crow::response(response.dump());
}
crow::response Api::deleteMode(crow::request req) 
{

}
crow::response Api::setModeParameter(crow::request req)
{
    json response;
    auto parameter_name = req.url_params.get("parameter_name");
    auto value = req.url_params.get("value");
    if (!validator::checkCorrectParameters(ConfigController::getCurrentModeOptions(), { parameter_name }))
    {
        response["ok"] = false;
        response["description"] = "Invalid parameter name";
        return crow::response(response.dump());
    }
    if (!validator::missingParameter(value)) 
    {
        response["ok"] = false;
        response["description"] = "Missing parameters";
        return crow::response(response.dump());
    }
    ConfigController::updateOptions(value, parameter_name);
    ConfigController::loadSettings();
    response["ok"] = true;
    response["description"] = std::format("{} set to {}", parameter_name, value);
    ConfigController::setChangeOptions(true);
    return crow::response(response.dump());
}