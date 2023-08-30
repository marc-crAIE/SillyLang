#include "Core/SiRuntime.h"

#include "Memory/Mem.h"

SiStatus SiRuntime::Init()
{
	if (m_Initialized)
		return SiStatus::Ok();

	// Currently does nothing
	// Will have more in the future

	m_Initialized = true;
	return SiStatus::Ok();
}

void SiRuntime::Finalize()
{
	if (!m_Initialized)
		return;

	Memory::Free(m_MainInterp->GetThread());
	Memory::Free(m_MainInterp);

	m_Initialized = false;
}
