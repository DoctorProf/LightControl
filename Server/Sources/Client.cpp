#include "../Headers/Client.h"

Client::Client(std::string baseUrl) : client(baseUrl)
{
    //client.set_connection_timeout(0, 500000);
    //client.set_read_timeout(1, 0);
    //client.set_write_timeout(1, 0);
}

bool Client::setLedColors(std::vector<uint8_t> colors)
{
    std::string color(colors.begin(), colors.end());
    httplib::Result res = client.Post("/setLedColors", color, "application/octet-stream");
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