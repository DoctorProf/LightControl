#include "../../include/controllers/ModeController.h"
#include <iostream>

ModeController::ModeController() : dll(nullptr) {}

ModeController::~ModeController() {
	unloadMode();
}

bool ModeController::loadMode(std::string name)
{
	unloadMode();

	dll = LoadLibraryA(("modes/" + name).c_str());
	if (!dll)
	{
		std::cerr << "Failed to load DLL: " << name << std::endl;
		return false;
	}

	getTypeFunc = loadFunction<func_int>("getType");
	setColorFunc = loadFunction<func_setColor>("setColor");
	setSpeedFunc = loadFunction<func_setSpeed>("setSpeed");
	setWaveLengthFunc = loadFunction<func_setWaveLength>("setWaveLength");
	getColorFunc = loadFunction<func_int>("getColor");

	if (!getTypeFunc || !setColorFunc || !setSpeedFunc || !setWaveLengthFunc || !getColorFunc)
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

	getTypeFunc = nullptr;
	setColorFunc = nullptr;
	setSpeedFunc = nullptr;
	setWaveLengthFunc = nullptr;
	getColorFunc = nullptr;
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

int ModeController::getType()
{
	if (getTypeFunc) {
		return getTypeFunc();
	}
	std::cerr << "getType function is not loaded!" << std::endl;
	return -1;
}

void ModeController::setColor(int red, int green, int blue)
{
	if (setColorFunc)
	{
		setColorFunc(red, green, blue);
	}
	else
	{
		std::cerr << "setColor function is not loaded!" << std::endl;
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

int ModeController::getColor()
{
	if (getColorFunc)
	{
		return getColorFunc();
	}
	std::cerr << "getColor function is not loaded!" << std::endl;
	return -1;
}