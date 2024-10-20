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
    json previous_options = {};

    /*
    * API ����� RenameMode(std:string name);
    * ��������� ������ id �����
    * ����� ����� ��� ���� options ����
    * �������� ������ SelectMode
    * ��������� �������� ���� �� id, �������
    */

    while (run)
    {
        int mode_id = ConfigController::getCurrentModeId();
        int state = ConfigController::getState();
        float brightness = ConfigController::getBrightness();
        json options = ConfigController::getCurrentModeOptions();;

        if (previous_mode_id != mode_id || previous_state != state || previous_brightness != brightness || previous_options != options)
        {
            previous_mode_id = mode_id;
            previous_state = state;
            previous_brightness = brightness;
            previous_options = options;
            type_mode_static = true;
        }
        if ((options["static"] || !state) && type_mode_static)
        {
            int r = 0;
            int g = 0;
            int b = 0;
            brightness /= 255.f;
            if (state)
            {
                r = options["color"][0];
                g = options["color"][1];
                b = options["color"][2];
            }
            if (!client.setStripColor(r * brightness, g * brightness, b * brightness)) 
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