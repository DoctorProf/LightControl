#include "../Headers/Api.h"

Api::Api(crow::SimpleApp& app) 
{
	registerRoutes(app);
}
void Api::registerRoutes(crow::SimpleApp& app) 
{
    CROW_ROUTE(app, "/setState")
        .methods(crow::HTTPMethod::GET)
        ([this](crow::request req) {
        return setState(req);
            });
    CROW_ROUTE(app, "/getInfo")
        .methods(crow::HTTPMethod::GET)
        ([this](crow::request req) {
        return getInfo(req);
            });

    CROW_ROUTE(app, "/getModes")
        .methods(crow::HTTPMethod::GET)
        ([this](crow::request req) {
        return getModes(req);
            });
    CROW_ROUTE(app, "/setBrightness")
        .methods(crow::HTTPMethod::GET)
        ([this](crow::request req) {
        return setBrightness(req);
            });
    CROW_ROUTE(app, "/selectMode")
        .methods(crow::HTTPMethod::GET)
        ([this](crow::request req) {
        return selectMode(req);
            });
    CROW_ROUTE(app, "/addMode")
        .methods(crow::HTTPMethod::POST)
        ([this](crow::request req) {
        return addMode(req);
            });

    CROW_ROUTE(app, "/setLedColors")
        .methods(crow::HTTPMethod::POST)
        ([this](crow::request req) {
        return setLedColors(req);
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
        return crow::response(response.dump(4));
    }

    response = validator::setParameter(state, "state", 0, 1);
    return crow::response(response.dump(4));
}
crow::response Api::getInfo(crow::request req)
{
    json info = json::parse(std::ifstream("config.json"));
    return crow::response(info["info"].dump(4));
}
crow::response Api::getModes(crow::request req)
{
    return crow::response(json::parse(std::ifstream("config.json"))["modes"].dump(4));
}
crow::response Api::setBrightness(crow::request req) 
{
    json response;
    auto brightness = req.url_params.get("brightness");

    if (!validator::missingParameter(brightness)) 
    {
        response["ok"] = false;
        response["description"] = "Missing parameter";
        return crow::response(response.dump(4));
    }

    response = validator::setParameter(brightness, "brightness", 0, 100);
    return crow::response(response.dump(4));
}
crow::response Api::selectMode(crow::request req)
{
    json response;
    auto mode_id = req.url_params.get("mode_id");

    if (!validator::missingParameter(mode_id))
    {
        response["ok"] = false;
        response["description"] = "Missing parameter";
        return crow::response(response.dump(4));
    }
    json modes = json::parse(std::ifstream("config.json"))["modes"];
    int count_modes = modes.size();
    response = validator::setParameter(mode_id, "mode_id", modes[0]["id"], modes[count_modes - 1]["id"]);
    return crow::response(response.dump(4));
}
crow::response Api::addMode(crow::request req)
{
    json response;
    response = validator::addMode(req);
    return crow::response(response.dump(4));
}

crow::response Api::setLedColors(crow::request req)
{
    return crow::response(req.body);
}