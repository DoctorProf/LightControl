#include "Headers/Api.h"
#include <crow/app.h>

int main() 
{
    crow::SimpleApp app;
    Api api(app);

    bool run = true;

    app.port(8080).multithreaded().run();

    while (run)
    {

    }
    return 0;
}