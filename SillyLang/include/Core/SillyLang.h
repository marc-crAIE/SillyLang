#pragma once

#include "Core/SiStatus.h"
#include "Core/SiRuntime.h"

class SillyLang final
{
public:
	static SiStatus Init();
	static void Exit(int exitCode);

	static inline SiRuntime* GetRuntime() { return &m_Runtime; }
	static inline SiInterpreter* GetInterpreter() { return (&m_Runtime)->GetInterpreter(); }
	static inline SiThread* GetThread() { return (&m_Runtime)->GetThread(); }
private:
	static SiRuntime m_Runtime;
};