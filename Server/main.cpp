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
    Client client("http://192.168.1.21:10000");
    crow::SimpleApp app;
    Api api(app);

    bool run = true;
    bool type_mode_static = true;

    std::thread api_thread(&apiThread, std::ref(app));
    api_thread.detach();

    int previous_mode_id{ 0 };
    int previous_state{ 0 };
    int previous_brightness{ 0 };

    while (run)
    {
        json config = ConfigController::getConfig();
        int mode_id = config["info"]["mode_id"];
        int state = config["info"]["state"];
        float brightness = config["info"]["brightness"];

        if (previous_mode_id != mode_id || previous_state != state || previous_brightness != brightness) 
        {
            previous_mode_id = mode_id;
            previous_state = state;
            previous_brightness = brightness;
            type_mode_static = true;
        }
        json mode = config["modes"][mode_id];

        if ((mode["options"]["static"] || !state) && type_mode_static)
        {
            std::vector<uint8_t> colors;
            json color;
            brightness /= 255.f;
            if (state) color = config["modes"][mode_id]["options"]["color"];
            else color = {0, 0, 0};
            if (!client.setStripColor(color[0] * brightness, color[1] * brightness, color[2] * brightness)) type_mode_static = true;
            else type_mode_static = false;
        }
        else 
        {

        }
    }
    return 0;
}