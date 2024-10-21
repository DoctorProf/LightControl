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

    /*
    * API метод RenameMode(std:string name);
    * Изменение логики id модов
    * Общий метод для сета options мода
    * Изменить логику SelectMode
    * Получение текущего мода по id, неверно
    */
    while (run)
    {
        int mode_id = ConfigController::getCurrentModeId();
        int state = ConfigController::getState();
        float brightness = ConfigController::getBrightness();
        json options = ConfigController::getCurrentModeOptions();;

        if (previous_mode_id != mode_id || previous_state != state || previous_brightness != brightness || ConfigController::isChangeOptions())
        {
            previous_mode_id = mode_id;
            previous_state = state;
            previous_brightness = brightness;
            type_mode_static = true;
            ConfigController::setChangeOptions(false);
        }
        if ((ConfigController::getCurrentMode()["static"] || !state) && type_mode_static)
        {
            std::vector<int> color{ 0, 0, 0 };
            brightness /= 255.f;
            if (state)
            {
                color = parser::hexToRGB(options["color"]);
            }
            if (!client.setStripColor(color[0] * brightness, color[1] * brightness, color[2] * brightness))
            {
                type_mode_static = true;
            }
            else 
            {
                type_mode_static = false;
            }
        }
        else 
        {

        }
    }
    return 0;
}