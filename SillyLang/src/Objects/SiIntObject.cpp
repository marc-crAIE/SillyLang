#include "Objects/SiIntObject.h"

#include "Objects/SiStringObject.h"

#pragma region Methods

static SiObject* Int_StrRepr(SiObject* self)
{
	if (!Si_Is_Type(self, &SiIntType))
		return nullptr;

	SiIntObject* i = SiInt_Cast(self);
	SiObject* repr = SiStringObject::FromString(std::to_string(i->GetValue()));
	return repr;
}

#pragma endregion


SiAPI_DATA(SiTypeObject) SiIntType = {
	SiVarObject_Head_Init(&SiIntType, 0),	// Base
	"int",									// Name
	"Integer object type",					// Doc
	sizeof(SiIntObject),					// Size
	0,										// ItemSize
	TYPEFLAG_DEFAULT | TYPEFLAG_BASETYPE,	// Flags
	Int_StrRepr,							// StringRepr
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
