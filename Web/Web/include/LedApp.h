#pragma once
#include <Wt/WApplication.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WVBoxLayout.h>
#include <Wt/WHBoxLayout.h>
#include <Wt/WComboBox.h>
#include <Wt/WSlider.h>
#include <Wt/WCheckBox.h>
#include <Wt/WBootstrap5Theme.h>
#include <Wt/WLabel.h>
#include <Wt/WPushButton.h>
#include <Wt/WLineEdit.h>
#include <Wt/WColorPicker.h>
#include <Wt/WString.h>
#include "Server.h"

class LedApp : public Wt::WApplication {
public:
	explicit LedApp(const Wt::WEnvironment& env);

private:
	void setRoot();
	void setupContainers();
	void setupControls();

	void setupLogo();
	void setupModeSelector();
	void setupBrightnessSlider();
	void setupPowerSwitch();
	std::unique_ptr<Wt::WContainerWidget> createPropertyControl(Wt::WString screen_name, std::string name, float min, float max, float step, float value);
	std::unique_ptr<Wt::WContainerWidget> createColorControl(Wt::WString screen_name, std::string name, std::string value);

	void setValuesToControls();

	void createControlsProperties();

	Wt::WContainerWidget* main_container;
	Wt::WVBoxLayout* layout_for_containers;
	Wt::WContainerWidget* controls_container;
	Wt::WVBoxLayout* controls_layout;
	Wt::WContainerWidget* properties_container;
	Wt::WVBoxLayout* properties_layout = nullptr;
	Wt::WComboBox* mode_selector;
	Wt::WSlider* brightness_slider;
	Wt::WText* brightness_value_text;
	Wt::WCheckBox* power_switch;
	std::unique_ptr<Server> server;
};