#include "Headers/Api.h"
#include "Headers/Client.h"
#include <thread>

void apiThread(crow::SimpleApp& app) 
{
    app.port(8080).multithreaded().run();
}
int main() 
{
    httplib::MultipartFormDataItems files;
    Client client("http://localhost:10000");
    crow::SimpleApp app;
    Api api(app);

    bool run = true;
    bool type_mode_static = true;

    std::thread api_thread(&apiThread, std::ref(app));
    api_thread.detach();

    int previous_mode_id{0};

    while (run)
    {
        std::ifstream file("config.json");
        json config;
        file >> config;
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
            for (int i = 0; i < config["info"]["led_count"]; ++i) 
            {
                colors.push_back(color[0]);
                colors.push_back(color[1]);
                colors.push_back(color[2]);
            }
            if(!client.setLedColors(colors)) type_mode_static = true;
        }
        else 
        {

        }
    }
    return 0;
}