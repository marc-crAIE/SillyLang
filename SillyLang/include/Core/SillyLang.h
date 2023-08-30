#pragma once

#include "Core/SiStatus.h"
#include "Core/SiRuntime.h"

class SillyLang final
{
public:
	static SiStatus Init();
	static void Exit(int exitCode);
private:
	static SiRuntime m_Runtime;
};