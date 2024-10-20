#include "Headers/Api.h"
#include "Headers/Client.h"
#include <thread>
#include <csignal>

void apiThread(crow::SimpleApp& app) 
{
    app.port(8080).multithreaded().run();
}
int main() 
{
    ConfigController::readConfigFile("config.json");
    ConfigController::updateParameters();
    Client client("http://127.0.0.1:10000");
    crow::SimpleApp app;
    Api api(app);

    bool run = true;
    bool type_mode_static = true;

    std::thread api_thread(&apiThread, std::ref(app));
    api_thread.detach();

    int previous_mode_id{ 0 };
    int previous_state{ 0 };
    int previous_brightness{ 0 };
    json previous_color = { 0, 0, 0 };

    while (run)
    {
        /*json config = ConfigController::getConfig();
        int mode_id = config["info"]["mode_id"];
        int state = config["info"]["state"];
        float brightness = config["info"]["brightness"];
        json mode = config["modes"][mode_id];
        json color = mode["options"]["color"];*/
        int mode_id = ConfigController::getCurrentModeId();
        int state = ConfigController::getState();
        float brightness = ConfigController::getBrightness();
        json mode = ConfigController::getCurrentMode();
        json color = mode["options"]["color"];

        if (previous_mode_id != mode_id || previous_state != state || previous_brightness != brightness || previous_color != color) 
        {
            previous_mode_id = mode_id;
            previous_state = state;
            previous_brightness = brightness;
            previous_color = color;
            type_mode_static = true;
        }
        if ((mode["options"]["static"] || !state) && type_mode_static)
        {
            brightness /= 255.f;
            if (!state) color = { 0, 0, 0 };
            int r = color[0];
            int g = color[1];
            int b = color[2];
            if (!client.setStripColor(r * brightness, g * brightness, b * brightness)) type_mode_static = true;
            else type_mode_static = false;
        }
        else 
        {

        }
    }
    return 0;
}