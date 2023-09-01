#include "Objects/SiIntObject.h"

#include "Objects/SiStringObject.h"

#pragma region Methods

static SiObject* Int_StrRepr(SiObject* self)
{
	SiIntObject* i = SiInt_SafeCast(self);
	SiObject* repr = SiStringObject::FromString(std::to_string(i->GetValue()));
	return repr;
}

static Si_hash_t Int_Hash(SiObject* self)
{
	SiIntObject* i = SiInt_SafeCast(self);
	return i->m_Value;
}

#pragma endregion


SiAPI_DATA(SiTypeObject) SiIntType = {
	SiVarObject_Head_Init(&SiIntType, 0),	// Base
	"int",									// Name
	"Integer object type",					// Doc
	sizeof(SiIntObject),					// Size
	0,										// ItemSize
	TYPE_FLAG_DEFAULT | TYPE_FLAG_BASETYPE,	// Flags
	Int_StrRepr,							// StringRepr
	Int_Hash,								// Hash
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
