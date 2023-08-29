#include "Objects/SiFloatObject.h"

#include "Objects/SiStringObject.h"

#pragma region Methods

static SiObject* Float_StrRepr(SiObject* self)
{
	if (!Si_Is_Type(self, &SiFloatType))
		return nullptr;

	SiFloatObject* f = SiFloat_Cast(self);
	SiObject* repr = SiStringObject::FromString(std::to_string(f->GetValue()));
	return repr;
}

#pragma endregion


SiAPI_DATA(SiTypeObject) SiFloatType = {
	SiVarObject_Head_Init(&SiFloatType, 0),	// Base
	"float",								// Name
	"Floating point object type",			// Doc
	sizeof(SiFloatObject),					// Size
	0,										// ItemSize
	TYPEFLAG_DEFAULT | TYPEFLAG_BASETYPE,	// Flags
	Float_StrRepr,							// StringRepr
	NULL,									// Dealloc
	NULL,									// Free
	NULL									// BaseType
};

SiObject* SiFloatObject::FromFloat(float value)
{
	return FromDouble(value);
}

SiObject* SiFloatObject::FromDouble(double value)
{
	SiFloatObject* obj = SiObject_New(SiFloatObject, &SiFloatType);
	obj->m_Value = value;
	return SiObject_Cast(obj);
}

SiObject* SiFloatObject::FromString(const char* str)
{
	SiFloatObject* obj = SiObject_New(SiFloatObject, &SiFloatType);
	obj->m_Value = std::stod(str);
	return SiObject_Cast(obj);
}
