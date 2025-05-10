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

class LedApp : public Wt::WApplication {
public:
	explicit LedApp(const Wt::WEnvironment& env);

private:
	void setRoot();
	void setupContainers();
	void setupControls();

	void setupModeSelector();
	void setupBrightnessSlider();
	void setupPowerSwitch();
	void connectSignals();
	void createPropertyControl();
	void createColorControl();

	Wt::WContainerWidget* main_container;
	Wt::WHBoxLayout* layout_for_containers;
	Wt::WContainerWidget* controls_container;
	Wt::WVBoxLayout* controls_layout;
	Wt::WContainerWidget* properties_container;
	Wt::WVBoxLayout* properties_layout;
	Wt::WComboBox* mode_selector;
	Wt::WSlider* brightness_slider;
	Wt::WCheckBox* power_switch;
};