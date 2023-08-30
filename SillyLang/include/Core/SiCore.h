#pragma once

#include "Core/SiRuntime.h"
#include "Core/SiStatus.h"

class SiCore final
{
public:
	static SiStatus Init(SiRuntime* runtime);
private:
	static SiStatus CreateInterpreter(SiRuntime* runtime);
};