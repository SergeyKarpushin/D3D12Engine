#include "Engine.h"

PerGameSettings* PerGameSettings::inst;

PerGameSettings::PerGameSettings()
{
	inst = this;

	wcscpy_s(inst->m_GameName, L"undefined");
	wcscpy_s(inst->m_ShortName, L"undefined");
	wcscpy_s(inst->m_BootTime, Time::GetDateTime(TRUE).c_str());
	wcscpy_s(inst->m_SplashURL, L"..\\Engine\\Content\\Images\\Splash.bmp");
}

PerGameSettings::~PerGameSettings()
{
}
