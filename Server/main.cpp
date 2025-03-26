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

	std::thread api_thread(&apiThread, std::ref(app));
	api_thread.detach();

	ModeController mode_controller;

	float brightness;
	int state;
	bool* change_handler = ConfigController::getInstance()->getChangeHandler();
	bool type;
	bool first_request;
	const int led_count = ConfigController::getInstance()->getLedCount();

	while (true)
	{
		if (*change_handler)
		{
			brightness = ConfigController::getInstance()->getBrightness() / 255.f;
			state = ConfigController::getInstance()->getState();
			mode_controller.loadMode(ConfigController::getInstance()->getModeName());
			mode_controller.setLedCount(led_count);
			type = mode_controller.getTypeMode();
			first_request = true;
			*change_handler = false;
		}
		if (!state && first_request)
		{
			client.setStripColor(0, 0, 0);
			first_request = false;
		}
		if (type && first_request)
		{
			auto color = utils::INTToRGB(mode_controller.getStaticColor());
			std::transform(color.begin(), color.end(), color.begin(), [brightness](int value) {
				return value * brightness;
				});
			client.setStripColor(color[0], color[1], color[2]);
			first_request = false;
		}
		if (!type && state)
		{
			std::vector<int> colors(led_count * 3);
			mode_controller.getDynamicColor(colors.data());
			client.setLedColors(colors);
		}
	}
	return 0;
}