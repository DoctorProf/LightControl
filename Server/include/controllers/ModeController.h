#pragma once
#include <string>
#include <Windows.h>
#include <vector>

using func_int = int(*)();
using func_setStaticColor = void(*)(int, int, int);
using func_setSpeed = void(*)(float);
using func_setWaveLength = void(*)(int);
using func_getDynamicColorFunc = void(*)(int*);
using func_setLedCount = void(*)(int);

class ModeController
{
public:
	ModeController();
	~ModeController();

	bool loadMode(std::string name);
	void unloadMode();
	void setLedCount(int count);
	int getTypeMode();
	void setStaticColor(int red, int green, int blue);
	void setSpeed(float speed);
	void setWaveLength(int length);
	int getStaticColor();
	void getDynamicColor(int* output);

private:
	HMODULE dll;
	void(*setLedCountFunc)(int) = nullptr;
	int(*getTypeModeFunc)() = nullptr;
	void(*setStaticColorFunc)(int, int, int) = nullptr;
	void(*setSpeedFunc)(float) = nullptr;
	void(*setWaveLengthFunc)(int) = nullptr;
	int(*getStaticColorFunc)() = nullptr;
	void(*getDynamicColorFunc)(int*) = nullptr;

	template <typename T>
	T loadFunction(std::string functionName);
};