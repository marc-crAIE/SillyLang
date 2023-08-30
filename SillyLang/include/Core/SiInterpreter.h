#pragma once

#include "Core/SiThread.h"

class SiCore;
class SiRuntime;

class SiInterpreter final
{
public:
	SiInterpreter() = default;
	~SiInterpreter() = default;

	inline SiThread* GetThread() const { return m_Thread; }
private:
	SiThread* m_Thread;
private:
	friend SiThread;
	friend SiCore;
};