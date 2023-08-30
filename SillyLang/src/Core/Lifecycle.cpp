#include "Core/Lifecycle.h"

#include "SillyLang.h"

static SiTypeObject* s_StaticTypes[] =
{
	&SiBaseType,

	&SiBoolType,
	&SiFloatType,
	&SiIntType,
	&SiListType,
	&SiStringType
};

SiStatus Lifecycle::InitTypes()
{
	SiStatus status = SiStatus::Ok();

	for (Si_size_t i = 0; i < Si_Array_Length(s_StaticTypes); i++) {
		SiTypeObject* type = s_StaticTypes[i];
		if (SiType_Ready(type) < 0)
			status = SiStatus::Error("Cannot initialize built-in type!");
	}

	return status;
}
