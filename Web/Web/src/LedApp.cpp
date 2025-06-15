#include "../include/LedApp.h"

LedApp::LedApp(const Wt::WEnvironment& env) : Wt::WApplication(env),
server(std::make_unique<Server>("127.0.0.1", 5000))
{
	setTheme(std::make_shared<Wt::WBootstrap5Theme>());

	useStyleSheet("./resources/themes/bootstrap/5/bootstrap.min.css");
	require("./resources/themes/bootstrap/5/bootstrap.bundle.min.js");

	auto version = std::to_string(time(nullptr));
	useStyleSheet("./resources/styles.css?v=" + version);

	setTitle("LED Controller");
	setRoot();
	setupContainers();
	setupControls();
	setValuesToControls();
	createControlsProperties();
}
void LedApp::setRoot()
{
	root()->addStyleClass("root d-flex justify-content-center align-items-center min-vh-100");
}
void LedApp::setupContainers()
{
	main_container = root()->addNew<Wt::WContainerWidget>();
	main_container->addStyleClass("glass-container py-4");

	layout_for_containers = main_container->setLayout(std::make_unique<Wt::WVBoxLayout>());
	layout_for_containers->setSpacing(40);
	layout_for_containers->setContentsMargins(100, 100, 100, 100);

	controls_container = layout_for_containers->addWidget(std::make_unique<Wt::WContainerWidget>());
	controls_container->addStyleClass("control-panel");
	controls_layout = controls_container->setLayout(std::make_unique<Wt::WVBoxLayout>());
	controls_layout->setContentsMargins(30, 30, 30, 30);
	controls_layout->setSpacing(25);

	properties_container = layout_for_containers->addWidget(std::make_unique<Wt::WContainerWidget>());
	properties_container->addStyleClass("params-panel");
	properties_container->setOverflow(Wt::Overflow::Auto);
	properties_layout = properties_container->setLayout(std::make_unique<Wt::WVBoxLayout>());
	properties_layout->setContentsMargins(30, 30, 30, 30);
}

void LedApp::setupControls()
{
	setupLogo();
	setupModeSelector();
	setupBrightnessSlider();
	setupPowerSwitch();
}
void LedApp::setupLogo()
{
	auto logo_container = controls_layout->addWidget(std::make_unique<Wt::WContainerWidget>(), 0, Wt::AlignmentFlag::Center);
	logo_container->setStyleClass("logo-container text-center mb-4");

	auto logo = logo_container->addNew<Wt::WImage>("favicon.ico");
	logo->setAlternateText("App Logo");
	logo->setStyleClass("app-logo");
	logo->resize(128, 128);
}

void LedApp::setupModeSelector()
{
	mode_selector = controls_layout->addWidget(std::make_unique<Wt::WComboBox>(), 1, Wt::AlignmentFlag::Center);
	mode_selector->addStyleClass("form-select text-center control-element");
	mode_selector->setMargin(15, Wt::Side::Bottom);
	mode_selector->setWidth(Wt::WLength(85, Wt::LengthUnit::Percentage));

	mode_selector->changed().connect([this] {
		server->setSettings("mode_name", mode_selector->valueText().toUTF8());
		createControlsProperties();
		});
}
void LedApp::setupBrightnessSlider()
{
	auto slider_container = controls_layout->addWidget(std::make_unique<Wt::WContainerWidget>(), 1, Wt::AlignmentFlag::Center);
	slider_container->setStyleClass("slider-container text-center w-100");

	brightness_slider = slider_container->addNew<Wt::WSlider>();
	brightness_slider->setStyleClass("form-range brightness-slider mx-auto");
	brightness_slider->setNativeControl(true);
	brightness_slider->setMinimum(0);
	brightness_slider->setMaximum(100);
	brightness_slider->setValue(0);
	brightness_slider->resize(500, 50);

	brightness_value_text = slider_container->addNew<Wt::WText>("0%");
	brightness_value_text->addStyleClass("text-muted mt-2 d-block");

	brightness_slider->input().connect([=] {
		brightness_value_text->setText(brightness_slider->valueText() + "%");
		server->setSettings("brightness", brightness_slider->value() * 2.55);
		});
}
void LedApp::setupPowerSwitch()
{
	auto switch_container = controls_layout->addWidget(std::make_unique<Wt::WContainerWidget>());
	switch_container->addStyleClass("d-flex align-items-center justify-content-center py-3");

	power_switch = switch_container->addNew<Wt::WCheckBox>();
	power_switch->addStyleClass("custom-switch");

	power_switch->changed().connect([this] {
		server->setSettings("state", power_switch->isChecked());
		});
}
std::unique_ptr<Wt::WContainerWidget> LedApp::createPropertyControl(
	Wt::WString screen_name, std::string name, float min, float max, float step, float value)
{
	auto container = std::make_unique<Wt::WContainerWidget>();
	container->addStyleClass("param-group bg-dark rounded p-3 mb-3");

	auto title = container->addWidget(std::make_unique<Wt::WText>(screen_name));
	title->addStyleClass("h5 text-light mb-2");

	auto slider_container = container->addWidget(std::make_unique<Wt::WContainerWidget>());
	slider_container->addStyleClass("d-flex align-items-center gap-3");

	int precision = 1000;

	auto slider = slider_container->addWidget(std::make_unique<Wt::WSlider>());
	slider->setNativeControl(true);
	slider->addStyleClass("form-range flex-grow-1");

	int int_min = static_cast<int>(min * precision);
	int int_max = static_cast<int>(max * precision);
	int int_value = static_cast<int>(value * precision);
	int int_step = static_cast<int>(step * precision);

	slider->setMinimum(int_min);
	slider->setMaximum(int_max);
	slider->setValue(int_value);
	slider->setStep(int_step);
	slider->resize(300, 30);

	auto value_text = container->addWidget(std::make_unique<Wt::WText>());
	value_text->setText(Wt::WString("{1}").arg(value));
	value_text->addStyleClass("text-muted mt-2 d-block text-center");

	slider->input().connect([=, precision = precision]() mutable {
		float actual_value = static_cast<float>(slider->value()) / precision;
		std::ostringstream oss;
		oss << std::fixed << std::setprecision(2) << actual_value;
		value_text->setText(Wt::WString(oss.str()));
		server->setModeParams(name, "value", actual_value);
		});

	return container;
}
std::unique_ptr<Wt::WContainerWidget> LedApp::createColorControl(Wt::WString screen_name, std::string name, std::string value)
{
	auto container = std::make_unique<Wt::WContainerWidget>();
	container->addStyleClass("color-control mb-4 p-3 bg-dark rounded");

	container->addWidget(std::make_unique<Wt::WText>(screen_name))
		->addStyleClass("h5 text-light mb-3");

	auto color_picker = container->addWidget(std::make_unique<Wt::WColorPicker>());
	color_picker->setColor(Wt::WColor(value));
	color_picker->addStyleClass("custom-color-picker");
	color_picker->setInline(true);

	auto value_text = container->addWidget(std::make_unique<Wt::WText>());
	value_text->setText(value);
	value_text->addStyleClass("text-muted mt-2 d-block text-center");

	color_picker->colorInput().connect([=]() mutable {
		Wt::WColor new_color = color_picker->color();
		std::string color_value = new_color.cssText();
		value_text->setText(color_value);
		server->setModeParams(name, "value", color_value);
		});

	return container;
}

void LedApp::setValuesToControls()
{
	json modes = server->getModes();
	json settings = server->getSettings();

	for (int i = 0; i < modes["modes"].size(); ++i)
	{
		std::string mode = modes["modes"][i];

		mode_selector->addItem(mode);
		if (mode == settings["mode_name"].get<std::string>())
		{
			mode_selector->setValueText(mode);
		}
	}
	int brightness = std::ceil(settings["brightness"].get<float>() / 2.55);
	brightness_slider->setValue(brightness);
	brightness_value_text->setText(std::to_string(brightness) + "%");
	int state = settings["state"];
	power_switch->setChecked(state);
}

void LedApp::createControlsProperties()
{
	try {
		if (properties_layout) {
			properties_container->removeChild(properties_layout);
			properties_layout = nullptr;
		}
		properties_layout = properties_container->setLayout(std::make_unique<Wt::WVBoxLayout>());
		properties_layout->setContentsMargins(30, 30, 30, 30);
		json mode_parameters = server->getModeParams();

		for (auto& [param_name, param_data] : mode_parameters.items())
		{
			std::string type = param_data["type"];
			Wt::WString screen_name = param_data["screen_name"].get<std::string>();
			if (type == "color")
			{
				std::string value = param_data["value"];
				properties_layout->addWidget(std::move(createColorControl(screen_name, param_name, param_data["value"].get<std::string>())), 1, Wt::AlignmentFlag::Center);
			}
			else if (type == "float")
			{
				float value = param_data["value"];
				float min = param_data["min"];
				float max = param_data["max"];
				float step = param_data["step"];
				properties_layout->addWidget(std::move(createPropertyControl(screen_name, param_name, min, max, step, value)), 1, Wt::AlignmentFlag::Center);
			}
		}
	}
	catch (const json::exception& e) {
		std::cerr << "JSON error: " << e.what() << std::endl;
	}
}