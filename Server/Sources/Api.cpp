#include "../Headers/Api.h"

Api::Api(crow::SimpleApp& app) 
{
	registerRoutes(app);
}
void Api::registerRoutes(crow::SimpleApp& app) 
{
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
    
}
crow::response Api::getInfo(crow::request req)
{
    json info = json::parse(std::ifstream("config.json"));
    return crow::response(info["info"].dump(4));
}
crow::response Api::getModes(crow::request req)
{
    json config;
    json json_response = json::array();
    config = json::parse(std::ifstream("config.json"));

    for (int i = 0; i < config["modes"].size(); ++i)
    {
        json obj;
        obj["id"] = config["modes"][i]["id"];
        obj["name"] = config["modes"][i]["name"];
        json_response.push_back(obj);
    }
    return crow::response(json_response.dump(4));
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