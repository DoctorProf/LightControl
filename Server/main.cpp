#include "Headers/Api.h"
#include "Headers/Client.h"
#include <thread>

void apiThread(crow::SimpleApp& app) 
{
    app.port(8080).multithreaded().run();
}
int main() 
{
    ConfigController::updateConfig();
    Client client("http://127.0.0.1:10000");
    crow::SimpleApp app;
    Api api(app);

    bool run = true;
    bool type_mode_static = true;

    std::thread api_thread(&apiThread, std::ref(app));
    api_thread.detach();

    int previous_mode_id{ 0 };
    int previous_state{ 1 };

    while (run)
    {
        json config = ConfigController::getConfig();
        int mode_id = config["info"]["mode_id"];
        int state = config["info"]["state"];

        if (previous_mode_id != mode_id || previous_state != state) 
        {
            previous_mode_id = mode_id;
            previous_state = state;
            type_mode_static = true;
        }
        json mode = config["modes"][mode_id];

        if ((mode["static"] || !state) && type_mode_static)
        {
            std::vector<uint8_t> colors;
            json color;
            if (state) color = config["modes"][mode_id]["color"];
            else color = {0, 0, 0};
            if (!client.setStripColor(color[0], color[1], color[2])) type_mode_static = true;
            else type_mode_static = false;
        }
        else 
        {

        }
    }
    return 0;
}