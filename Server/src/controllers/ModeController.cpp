#include "../../include/controllers/ModeController.h"
#include <iostream>

ModeController::ModeController() : dll(nullptr) {}

ModeController::~ModeController() {
	unloadMode();
}

bool ModeController::loadMode(std::string name)
{
	unloadMode();

	dll = LoadLibraryA(("modes/" + name + ".dll").c_str());
	if (!dll)
	{
		std::cerr << "Failed to load DLL: " << name << std::endl;
		return false;
	}

	setLedCountFunc = loadFunction<func_setLedCount>("setLedCount");
	getTypeModeFunc = loadFunction<func_int>("getTypeMode");
	setStaticColorFunc = loadFunction<func_setStaticColor>("setStaticColor");
	setSpeedFunc = loadFunction<func_setSpeed>("setSpeed");
	setWaveLengthFunc = loadFunction<func_setWaveLength>("setWaveLength");
	getStaticColorFunc = loadFunction<func_int>("getStaticColor");
	getDynamicColorFunc = loadFunction<func_getDynamicColorFunc>("getDynamicColor");

	if (!getTypeModeFunc || !setSpeedFunc || !setSpeedFunc || !setWaveLengthFunc || !getStaticColorFunc)
	{
		std::cerr << "Failed to load one or more functions from DLL: " << name << std::endl;
		unloadMode();
		return false;
	}

	return true;
}

void ModeController::unloadMode()
{
	if (dll)
	{
		FreeLibrary(dll);
		dll = nullptr;
	}
	setLedCountFunc = nullptr;
	getTypeModeFunc = nullptr;
	setStaticColorFunc = nullptr;
	setSpeedFunc = nullptr;
	setWaveLengthFunc = nullptr;
	getStaticColorFunc = nullptr;
	getDynamicColorFunc = nullptr;
}

template <typename T>
T ModeController::loadFunction(std::string functionName)
{
	if (!dll)
	{
		return nullptr;
	}
	return reinterpret_cast<T>(GetProcAddress(dll, functionName.c_str()));
}
void ModeController::setLedCount(int count)
{
	if (setLedCountFunc)
	{
		setLedCountFunc(count);
	}
	else
	{
		std::cerr << "setLedCount function is not loaded!" << std::endl;
	}
}

int ModeController::getTypeMode()
{
	if (getTypeModeFunc)
	{
		return getTypeModeFunc();
	}
	std::cerr << "getTypeMode function is not loaded!" << std::endl;
	return -1;
}

void ModeController::setStaticColor(int red, int green, int blue)
{
	if (setStaticColorFunc)
	{
		setStaticColorFunc(red, green, blue);
	}
	else
	{
		std::cerr << "setStaticColor function is not loaded!" << std::endl;
	}
}

void ModeController::setSpeed(float speed)
{
	if (setSpeedFunc)
	{
		setSpeedFunc(speed);
	}
	else
	{
		std::cerr << "setSpeed function is not loaded!" << std::endl;
	}
}

void ModeController::setWaveLength(int length)
{
	if (setWaveLengthFunc)
	{
		setWaveLengthFunc(length);
	}
	else
	{
		std::cerr << "setWaveLength function is not loaded!" << std::endl;
	}
}

int ModeController::getStaticColor()
{
	if (getStaticColorFunc)
	{
		return getStaticColorFunc();
	}
	std::cerr << "getStaticColor function is not loaded!" << std::endl;
	return -1;
}
void ModeController::getDynamicColor(int* output)
{
	if (getDynamicColorFunc)
	{
		getDynamicColorFunc(output);
	}
	else
	{
		std::cerr << "getDynamicColor function is not loaded!" << std::endl;
	}
}