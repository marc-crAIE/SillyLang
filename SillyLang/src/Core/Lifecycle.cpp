#include "Core/Lifecycle.h"

#include "../SillyLang.h"

SiStatus Lifecycle::InitTypes()
{
	SiStatus status;

	status = SiIntObject::InitTypes();
	if (status.IsException())
		return status;

	status = SiStringObject::InitTypes();
	if (status.IsException())
		return status;

	return SiStatus::Ok();
}
