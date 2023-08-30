#pragma once

#include "Core/SiStatus.h"
#include "Core/SiInterpreter.h"

class SiCore;

class SiRuntime final
{
public:
	SiStatus Init();
	void Finalize();

	inline SiInterpreter* GetInterpreter() const { return m_MainInterp; }
	inline SiThread* GetThread() const { return m_MainInterp->GetThread(); }

	inline bool IsInitialized() const { return m_Initialized && m_CoreInitialized; }
	inline bool IsRuntimeInitialized() const { return m_Initialized; }
	inline bool IsCoreInitialized() const { return m_CoreInitialized; }
private:
	bool m_Initialized;			// Is SillyLang initialized?
	bool m_CoreInitialized;		// Is the runtime core initialized?

	SiInterpreter* m_MainInterp;
private:
	friend SiCore;
};