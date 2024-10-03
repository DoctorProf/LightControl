#include "../Headers/Client.h"

Client::Client(std::string baseUrl) : client(baseUrl){}

bool Client::setLedColors(std::vector<uint8_t> colors)
{
    std::string color(colors.begin(), colors.end());
    auto res = client.Post("/setLedColors", color, "application/octet-stream");
    if (res) 
    {
        std::cout << "Successful request" << std::endl;
        return true;
    }
    else 
    {
        std::cout << "Failed request" << std::endl;
        return false;
    }
}
bool Client::setStripColor(uint8_t r, uint8_t g, uint8_t b) 
{
    std::string url = "/setStripColor?r=" + std::to_string(r) + "&g=" + std::to_string(g) + "&b=" + std::to_string(b);

    auto res = client.Get(url.c_str());
    if (res)
    {
        std::cout << "Successful request" << std::endl;
        return true;
    }
    else
    {
        std::cout << "Failed request" << std::endl;
        return false;
    }
}