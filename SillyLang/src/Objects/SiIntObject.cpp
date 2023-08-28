#include "Objects/SiIntObject.h"

#include "Memory/Mem.h"

#pragma region Methods

static void Int_Dealloc(SiIntObject* self)
{
	Si_Type(self)->m_Method_Free(SiObject_Cast(self));
}

#pragma endregion

SiTypeObject SiIntType = {
	SiVarObject_Head_Init(&SiIntType, 0),	// Base
	"int",									// Name
	"Integer object type",					// Doc
	sizeof(SiIntObject),					// Size
	0,										// ItemSize
	TYPEFLAG_DEFAULT | TYPEFLAG_BASETYPE,	// Flags
	(Destructor)Int_Dealloc,				// Dealloc
	Memory::Free,							// Free
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

SiStatus SiIntObject::InitTypes()
{
	if (SiType_Ready(&SiIntType) < 0)
		return SiStatus::Error("Cannot init int type");
	return SiStatus::Ok();
}
