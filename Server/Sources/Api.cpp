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
        .methods(crow::HTTPMethod::POST)
        ([this](crow::request req) {
        return setBrightness(req);
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
crow::response Api::setBrightness(crow::request req) 
{
    auto brightness = req.url_params.get("brightness");
    if (!brightness) {
        return crow::response(400, "Missing brightness parameter");
    }

    int brightnessValue;
    try {
        brightnessValue = std::atoi(brightness);
    }
    catch (const std::invalid_argument&) {
        return crow::response(400, "Invalid brightness parameter");
    }

    std::ifstream input_file("data.json");
    json data_json;

    input_file >> data_json;
    input_file.close();
    data_json["brightness"] = brightnessValue;

    std::ofstream output_file("data.json");
    output_file << data_json.dump(4);

    return crow::response("Brightness set to " + std::to_string(brightnessValue));
}