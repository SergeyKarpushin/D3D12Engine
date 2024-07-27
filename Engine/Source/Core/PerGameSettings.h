#pragma once


class ENGINE_API PerGameSettings {

	// Getters and setters for singleton static class
private:
	static PerGameSettings* inst;
public:
	static PerGameSettings* Instance() { return inst; }

	// Constructor
public:
	PerGameSettings();
	~PerGameSettings();

private:
	WCHAR m_GameName[MAX_NAME_STRING];
	WCHAR m_ShortName[MAX_NAME_STRING];
	HICON m_MainIcon;
	WCHAR m_BootTime[MAX_NAME_STRING];
};