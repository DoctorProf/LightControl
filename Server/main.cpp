#include "Headers/Api.h"
#include "Headers/Client.h"
#include <thread>
#include <csignal>

void apiThread(crow::SimpleApp& app) 
{
    app.port(ConfigController::getPortServer()).multithreaded().run();
}
int main() 
{
    ConfigController::readIp();
    ConfigController::readModes();
    ConfigController::readSettings();
    bool run = ConfigController::updateCurrentData();
    Client client(ConfigController::getIpClient());
    crow::SimpleApp app;
    Api api(app);

   bool type_mode_static = true;

    std::thread api_thread(&apiThread, std::ref(app));
    api_thread.detach();
    /*
    * API метод RenameMode(std:string name);
    * Изменение логики id модов
    * Общий метод для сета options мода
    * Изменить логику SelectMode
    * Получение текущего мода по id, неверно
    */
    while (run)
    {
        bool changed = ConfigController::isChange();
        bool state = ConfigController::getState();

        if (changed)
        {
            type_mode_static = true;
            ConfigController::setIsChange(false);
        }
        if ((ConfigController::getCurrentMode()["static"] || !state) && type_mode_static)
        {
            std::vector<int> color{ 0, 0, 0 };
            float brightness = ConfigController::getBrightness() / 255.f;
            if (state)
            {
                color = parser::hexToRGB(ConfigController::getCurrentModeOptions()["color"]);
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