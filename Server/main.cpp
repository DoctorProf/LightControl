#include "include/api/Api.h"
#include "include/network/Client.h"
#include "include/controllers/ModeController.h"
#include <thread>
#include <chrono>
#include <algorithm>

void apiThread(crow::SimpleApp& app)
{
	app.port(ConfigController::getInstance()->getServerPort()).multithreaded().run();
}
int main()
{
	ConfigController::getInstance()->readConfig();
	ConfigController::getInstance()->loadData();

	Client client;
	crow::SimpleApp app;
	Api api(app);

	std::thread api_thread(&apiThread, std::ref(app));
	api_thread.detach();

	ModeController mode_controller;

	float brightness = ConfigController::getInstance()->getBrightness() / 255.f;
	int state = ConfigController::getInstance()->getState();
	int* change_handler = ConfigController::getInstance()->getChangeHandler();
	bool type;
	bool first_request = true;
	const int led_count = ConfigController::getInstance()->getLedCount();

	mode_controller.loadMode(ConfigController::getInstance()->getModeName());
	mode_controller.setLedCount(led_count);
	mode_controller.setParameters(ConfigController::getInstance()->getModeParams().dump().c_str());
	type = mode_controller.getTypeMode();

	const int max_requests_per_second = 60;
	const std::chrono::milliseconds interval = std::chrono::milliseconds(1000 / max_requests_per_second);
	auto last_call_time = std::chrono::high_resolution_clock::now();

	while (true)
	{
		if (*change_handler)
		{
			switch (*change_handler)
			{
			case 1:
			{
				brightness = ConfigController::getInstance()->getBrightness() / 255.f;
				break;
			}
			case 2:
			{
				mode_controller.loadMode(ConfigController::getInstance()->getModeName());
				mode_controller.setLedCount(led_count);
				mode_controller.setParameters(ConfigController::getInstance()->getModeParams().dump().c_str());
				type = mode_controller.getTypeMode();
				break;
			}
			case 3:
			{
				state = ConfigController::getInstance()->getState();
				break;
			}
			case 4:
			{
				mode_controller.setParameters(ConfigController::getInstance()->getModeParams().dump().c_str());
				break;
			}
			}
			first_request = true;
			*change_handler = 0;
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
			if (!client.setStripColor(color[0], color[1], color[2])) continue;
			first_request = false;
		}
		if (!type && state)
		{
			auto current_time = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double> elapsed = current_time - last_call_time;

			if (elapsed < interval)
			{
				std::this_thread::sleep_for(interval - std::chrono::duration_cast<std::chrono::milliseconds>(elapsed));
			}
			last_call_time = std::chrono::high_resolution_clock::now();

			std::vector<int> colors(led_count * 3);
			mode_controller.getDynamicColor(colors.data());
			std::transform(colors.begin(), colors.end(), colors.begin(), [brightness](int value) {
				return value * brightness;
				});
			client.setLedColors(colors);
		}
	}
	return 0;
}