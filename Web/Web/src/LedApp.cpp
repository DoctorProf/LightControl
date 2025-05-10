#include "../include/LedApp.h"

LedApp::LedApp(const Wt::WEnvironment& env) : Wt::WApplication(env)
{
	setTheme(std::make_shared<Wt::WBootstrap5Theme>());

	addMetaHeader("viewport", "width=device-width, initial-scale=1");
	addMetaHeader("charset", "UTF-8");

	useStyleSheet("/resources/themes/bootstrap/5/bootstrap.min.css");
	require("/resources/themes/bootstrap/5/bootstrap.bundle.min.js");

	auto version = std::to_string(time(nullptr));
	useStyleSheet("/resources/styles.css?v=" + version);

	setTitle("LED Controller");
	setRoot();
	setupContainers();
	setupControls();
	connectSignals();
}
void LedApp::setRoot()
{
	root()->addStyleClass("root d-flex flex-column min-vh-100");
}
void LedApp::setupContainers()
{
	main_container = root()->addNew<Wt::WContainerWidget>();
	main_container->addStyleClass("container glass-container py-4");
	main_container->setMaximumSize(1200, Wt::WLength::Auto); // Максимальная ширина контейнера

	layout_for_containers = main_container->setLayout(std::make_unique<Wt::WHBoxLayout>());
	layout_for_containers->setContentsMargins(0, 0, 0, 0);
	layout_for_containers->setSpacing(40); // Горизонтальный отступ между панелями

	layout_for_containers->setSpacing(40);
	layout_for_containers->setContentsMargins(20, 20, 20, 20);
	// Контейнер для элементов управления
	controls_container = layout_for_containers->addWidget(std::make_unique<Wt::WContainerWidget>());
	controls_container->addStyleClass("control-panel");
	controls_layout = controls_container->setLayout(std::make_unique<Wt::WVBoxLayout>());
	controls_layout->setContentsMargins(30, 30, 30, 30);
	controls_layout->setSpacing(25); // Вертикальные отступы между элементами

	// Контейнер для свойств
	properties_container = layout_for_containers->addWidget(std::make_unique<Wt::WContainerWidget>());
	properties_container->addStyleClass("params-panel");
	properties_layout = properties_container->setLayout(std::make_unique<Wt::WVBoxLayout>());
	properties_layout->setContentsMargins(30, 30, 30, 30);
}

void LedApp::setupControls()
{
	setupModeSelector();
	setupBrightnessSlider();
	setupPowerSwitch();
}
void LedApp::setupModeSelector()
{
	mode_selector = controls_layout->addWidget(std::make_unique<Wt::WComboBox>(), 1, Wt::AlignmentFlag::Center);
	mode_selector->addStyleClass("form-select text-center control-element");
	mode_selector->addItem("Mode 1");
	mode_selector->addItem("Mode 2");
	mode_selector->setWidth(Wt::WLength(85, Wt::LengthUnit::Percentage));
	mode_selector->setMargin(15, Wt::Side::Bottom);
}
void LedApp::setupBrightnessSlider()
{
	auto sliderContainer = controls_layout->addWidget(std::make_unique<Wt::WContainerWidget>());
	sliderContainer->setStyleClass("slider-container");

	auto slider = sliderContainer->addNew<Wt::WSlider>();
	slider->setStyleClass("form-range");
	slider->setNativeControl(true);
	slider->setMinimum(0);
	slider->setMaximum(100);
	slider->setValue(50);
	slider->resize(Wt::WLength(100, Wt::LengthUnit::Percentage), Wt::WLength::Auto);

	auto labelsContainer = sliderContainer->addNew<Wt::WContainerWidget>();
	labelsContainer->setStyleClass("slider-labels");
	labelsContainer->addNew<Wt::WText>("0%")->setStyleClass("text-muted small");
	labelsContainer->addNew<Wt::WText>("100%")->setStyleClass("text-muted small");
}
void LedApp::setupPowerSwitch()
{
	auto switchContainer = controls_layout->addWidget(std::make_unique<Wt::WContainerWidget>());
	switchContainer->addStyleClass("d-flex align-items-center justify-content-center py-3");

	power_switch = switchContainer->addNew<Wt::WCheckBox>();
	power_switch->addStyleClass("custom-switch");
	power_switch->setInline(false);
}
void LedApp::connectSignals()
{
}
void LedApp::createPropertyControl()
{
}
void LedApp::createColorControl()
{
}