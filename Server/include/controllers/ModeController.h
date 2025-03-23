#pragma once
#include <string>
#include <Windows.h>

using func_int = int(*)();
using func_setColor = void(*)(int, int, int);
using func_setSpeed = void(*)(float);
using func_setWaveLength = void(*)(int);

class ModeController
{
public:
	ModeController();
	~ModeController();

	bool loadMode(std::string name);

	void unloadMode();

	int getType();
	void setColor(int red, int green, int blue);
	void setSpeed(float speed);
	void setWaveLength(int length);
	int getColor();

private:
	HMODULE dll;

	int(*getTypeFunc)() = nullptr;
	void(*setColorFunc)(int, int, int) = nullptr;
	void(*setSpeedFunc)(float) = nullptr;
	void(*setWaveLengthFunc)(int) = nullptr;
	int(*getColorFunc)() = nullptr;

	template <typename T>
	T loadFunction(std::string functionName);
};