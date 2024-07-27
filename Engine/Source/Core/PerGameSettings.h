#pragma once
#include <string>

class ENGINE_API PerGameSettings {

	// Getters and setters for singleton static class
private:
	static PerGameSettings* inst;
public:
	static PerGameSettings* Instance() { return inst; }

public:
	// Constructor with Singleton assignment and predefined variables
	PerGameSettings();
	~PerGameSettings();

private:
	WCHAR m_GameName[MAX_NAME_STRING];
	WCHAR m_ShortName[MAX_NAME_STRING];
	HICON m_MainIcon;
	WCHAR m_BootTime[MAX_NAME_STRING];

public:
	static WCHAR* GameName() { return inst->m_GameName; };
	static VOID SetGameName(INT id) { LoadString(HInstance(), id, inst->m_GameName, MAX_NAME_STRING); }

	static WCHAR* ShortName() { return inst->m_ShortName; };
	static VOID SetShortName(INT id) { LoadString(HInstance(), id, inst->m_ShortName, MAX_NAME_STRING); }

	static HICON MainIcon() { return inst->m_MainIcon; };
	static VOID SetMainIcon(INT id) { LoadIcon(HInstance(), MAKEINTRESOURCE(id)); }

	static WCHAR* BootTime() { return inst->m_BootTime; };
};