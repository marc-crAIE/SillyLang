#include "Core/SiThread.h"

#include "Core/SiInterpreter.h"

SiThread::SiThread(SiInterpreter* interp)
{
	m_Interp = interp;
	m_Interp->m_Thread = this;
}
