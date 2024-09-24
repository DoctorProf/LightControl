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
    
}
crow::response Api::getInfo(crow::request req)
{
    return crow::response(json::parse(std::ifstream("data.json")).dump(4));
}
crow::response Api::getModes(crow::request req)
{
    json json_modes;
    json json_response = json::array();

    json_modes = json::parse(std::ifstream("modes.json"));

    for (int i = 0; i < json_modes.size(); ++i) 
    {
        json obj;
        obj["id"] = json_modes[i]["id"];
        obj["name"] = json_modes[i]["name"];
        json_response.push_back(obj);
    }

    return crow::response(json_response.dump(4));
}