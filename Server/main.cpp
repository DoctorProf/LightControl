#include "Headers/Api.h"
#include "Headers/Client.h"
#include <thread>

json ConfigController::config = json::object();
bool ConfigController::is_updated = false;

void apiThread(crow::SimpleApp& app) 
{
    app.port(8080).multithreaded().run();
}
int main() 
{
    ConfigController::updateConfig();
    httplib::MultipartFormDataItems files;
    Client client("http://127.0.0.1:10000");
    crow::SimpleApp app;
    Api api(app);

    bool run = true;
    bool type_mode_static = true;

    std::thread api_thread(&apiThread, std::ref(app));
    api_thread.detach();

    int previous_mode_id{0};

    while (run)
    {
        if (!ConfigController::isUpdated()) continue;
        json config = ConfigController::getConfig();
        int mode_id = config["info"]["mode_id"];

        if (previous_mode_id != mode_id) 
        {
            type_mode_static = true;
        }
        previous_mode_id = mode_id;
        json mode = config["modes"][mode_id];

        if (mode["static"] && type_mode_static) 
        {
            std::vector<uint8_t> colors;
            json color = config["modes"][mode_id]["color"];
            if (!client.setStripColor(color[0], color[1], color[2])) type_mode_static = true;
            else type_mode_static = false;
        }
        else 
        {

        }
    }
    return 0;
}