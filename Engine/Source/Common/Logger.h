#pragma once

#include <string>

class ENGINE_API Logger {

	// Getters and setters for singleton static class
private:
	static Logger* inst;
public:
	static Logger* Instance() { return inst; }

	// Constructor
public:
	Logger();
	~Logger();


	// Print to Log File
	static VOID PrintLog(const WCHAR* fmt, ...);
	static std::wstring LogDirectory();
};