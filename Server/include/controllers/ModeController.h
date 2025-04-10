#pragma once
#include <string>
#include <Windows.h>
#include <vector>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

using func_int = int(*)();
using func_getDynamicColorFunc = void(*)(int*);
using func_setLedCount = void(*)(int);
using func_setParameters = void(*)(const char*);

class ModeController
{
public:
	ModeController();
	~ModeController();

	bool loadMode(std::string name);
	void unloadMode();
	void setLedCount(int count);
	int getTypeMode();
	void setParameters(const char* parameters);
	int getStaticColor();
	void getDynamicColor(int* output);

private:
	HMODULE dll;
	void(*setLedCountFunc)(int) = nullptr;
	int(*getTypeModeFunc)() = nullptr;
	void(*setParametersFunc)(const char*) = nullptr;
	int(*getStaticColorFunc)() = nullptr;
	void(*getDynamicColorFunc)(int*) = nullptr;

	template <typename T>
	T loadFunction(std::string function_name);
};