#include "Core/SiCore.h"

#include "Core/Lifecycle.h"
#include "Core/SiInterpreter.h"

SiStatus SiCore::Init(SiRuntime* runtime)
{
	SiStatus status;

	status = Lifecycle::InitTypes();
	if (status.IsException())
		return status;

	status = CreateInterpreter(runtime);
	if (status.IsException())
		return status;

	runtime->m_CoreInitialized = true;
	return status;
}

SiStatus SiCore::CreateInterpreter(SiRuntime* runtime)
{
	SiInterpreter* interp = new SiInterpreter();
	if (!interp)
		return SiStatus::Error("failed to initialize interpreter");

	SiThread* thread = new SiThread(interp);
	if (!thread)
		return SiStatus::Error("cannot make the first thread");

	runtime->m_MainInterp = interp;
	return SiStatus::Ok();
}
