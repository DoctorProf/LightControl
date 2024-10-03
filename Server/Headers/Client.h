#pragma once
#include <httplib.h>

class Client 
{
public:
    Client(std::string baseUrl);
    bool setLedColors(std::vector<uint8_t> colors);
    bool setStripColor(uint8_t r, uint8_t g, uint8_t b);
private:
    httplib::Client client;
};