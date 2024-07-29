#include "Engine.h"
#include "Simulation.h"
#include "Engine/SpashScreen.h"

Engine::Simulation::Simulation()
{
}

Engine::Simulation::~Simulation()
{
}

VOID Engine::Simulation::PreInitialize()
{
	Logger::PrintDebugSeperator();
	Logger::PrintLog(L"Application Starting...\n");
	Logger::PrintLog(L"Game Name: %s\n", PerGameSettings::GameName());
	Logger::PrintLog(L"Boot Time: %s\n", Time::GetDateTime().c_str());
	Logger::PrintLog(L"Engine Mode: %s\n", Engine::EngineModeToString().c_str());
	Logger::PrintDebugSeperator();

	SplashScreen::Open();
}
