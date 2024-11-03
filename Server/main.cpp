#include "Headers/Api.h"
#include "Headers/Client.h"
#include <thread>

void apiThread(crow::SimpleApp& app)
{
	app.port(ConfigController::getInstance()->getPortServer()).multithreaded().run();
}
int main()
{
	ConfigController::getInstance()->readIp();
	ConfigController::getInstance()->readModes();
	ConfigController::getInstance()->readSettings();
	bool run = ConfigController::getInstance()->updateCurrentData();
	Client client(ConfigController::getInstance()->getIpClient());
	crow::SimpleApp app;
	Api api(app);

	bool type_mode_static = true;

	std::thread api_thread(&apiThread, std::ref(app));
	api_thread.detach();

	while (run)
	{
		bool changed = ConfigController::getInstance()->isChange();
		bool state = ConfigController::getInstance()->getState();
		json mode = ConfigController::getInstance()->getCurrentMode();

		if (changed)
		{
			type_mode_static = true;
			ConfigController::getInstance()->setIsChange(false);
		}
		if ((mode["static"] || !state) && type_mode_static)
		{
			std::vector<int> color{ 0, 0, 0 };
			float brightness = ConfigController::getInstance()->getBrightness() / 255.f;
			if (state)
			{
				color = parser::hexToRGB(mode["options"]["color"]);
			}
			if (!client.setStripColor(color[0] * brightness, color[1] * brightness, color[2] * brightness))
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