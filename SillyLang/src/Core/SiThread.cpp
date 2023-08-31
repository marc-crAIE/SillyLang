#include "Core/SiThread.h"

#include "Core/SiInterpreter.h"
#include "Error/SiError.h"

SiThread::SiThread(SiInterpreter* interp)
{
	m_Interp = interp;
	m_Interp->m_Thread = this;

	m_CurrException = nullptr;

	m_SiRecursionLimit = SI_RECURSION_LIMIT;
	m_SiRecursionRemaining = SI_RECURSION_LIMIT;
	m_CppRecursionRemaining = CPP_RECURSION_LIMIT;
}

bool SiThread::CheckRecursiveCall(const char* where)
{
	if (m_CppRecursionHeadroom)
	{
		if (m_CppRecursionRemaining < -m_CppRecursionHeadroom)
			SiError::Fatal("Cannot recover from stack overflow");
	}
	else
	{
		if (m_CppRecursionRemaining <= 0)
		{
			SiError::Format(&SiRecursionErrorException, "maximum recursion depth exceeded %s", where);
			++m_CppRecursionRemaining;
			return false;
		}
	}
	return true;
}
