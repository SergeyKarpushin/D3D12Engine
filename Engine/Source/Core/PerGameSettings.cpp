#include "Engine.h"

PerGameSettings* PerGameSettings::inst;

PerGameSettings::PerGameSettings()
{
	inst = this;
}

PerGameSettings::~PerGameSettings()
{
}
