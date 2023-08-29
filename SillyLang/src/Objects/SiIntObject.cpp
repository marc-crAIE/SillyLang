#include "Objects/SiIntObject.h"

#include "Memory/Mem.h"

SiTypeObject SiIntType = {
	SiVarObject_Head_Init(&SiIntType, 0),	// Base
	"int",									// Name
	"Integer object type",					// Doc
	sizeof(SiIntObject),					// Size
	0,										// ItemSize
	TYPEFLAG_DEFAULT | TYPEFLAG_BASETYPE,	// Flags
	NULL,									// Dealloc
	NULL,									// Free
	NULL									// BaseType
};

SiObject* SiIntObject::FromInt(Si_int32_t value)
{
	SiIntObject* obj = SiObject_New(SiIntObject, &SiIntType);
	obj->m_Value = value;
	return SiObject_Cast(obj);
}

SiObject* SiIntObject::FromString(const char* str, int base)
{
	SiIntObject* obj = SiObject_New(SiIntObject, &SiIntType);
	obj->m_Value = std::stoi(str, nullptr, base);
	return SiObject_Cast(obj);
}
