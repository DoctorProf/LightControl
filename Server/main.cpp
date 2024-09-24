#include "Headers/Api.h"
#include <crow/app.h>

int main() 
{
    crow::SimpleApp app;
    Api api(app);

    app.port(8080).multithreaded().run();
}