#include "include/api/Api.h"
#include "include/network/Client.h"
#include <thread>
#include <random>
#include <chrono>
#include <atomic>
#include <algorithm>
#include "include/controllers/ModeController.h"

void apiThread(crow::SimpleApp& app)
{
	app.multithreaded().run();
}
int main()
{
	srand(time(NULL));

	ConfigController::getInstance()->readConfig();
	ConfigController::getInstance()->updateData();

	Client client(ConfigController::getInstance()->getAddressClient());
	crow::SimpleApp app;
	Api api(app);

	bool run = true;

	std::thread api_thread(&apiThread, std::ref(app));
	api_thread.detach();

	ModeController mode_controller;
	mode_controller.loadMode("mode.dll");
	auto color = mode_controller.getColor();
	auto color_vec = utils::INTToRGB(color);
	std::cout << "r " << color_vec[0] << " g " << color_vec[1] << " b " << color_vec[2] << std::endl;
	while (run)
	{
	}
	return 0;
}