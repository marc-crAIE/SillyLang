#include "Core/SillyLang.h"

#include <stdlib.h>

#include "Core/SiCore.h"

SiRuntime SillyLang::m_Runtime;

SiStatus SillyLang::Init()
{
	SiStatus status = m_Runtime.Init();
	if (status.IsException())
		return status;

	if (!m_Runtime.IsCoreInitialized())
	{
		status = SiCore::Init(&m_Runtime);
		if (status.IsException())
			return status;
	}

	return status;
}

void SillyLang::Exit(int exitCode)
{
	exit(exitCode);
}
