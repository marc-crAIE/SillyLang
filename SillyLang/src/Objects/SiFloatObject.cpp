#include "Objects/SiFloatObject.h"

#include "Objects/SiStringObject.h"
#include "Utils/Hash.h"

#pragma region Methods

static SiObject* Float_StrRepr(SiObject* self)
{
	SiFloatObject* f = SiFloat_SafeCast(self);
	SiObject* repr = SiStringObject::FromString(std::to_string(f->GetValue()));
	return repr;
}

static Si_hash_t Float_Hash(SiObject* self)
{
	SiFloatObject* f = SiFloat_SafeCast(self);
	return Hash::Double(f, f->GetValue());
}

#pragma endregion


SiAPI_DATA(SiTypeObject) SiFloatType = {
	SiVarObject_Head_Init(&SiFloatType, 0),	// Base
	"float",								// Name
	"Floating point object type",			// Doc
	sizeof(SiFloatObject),					// Size
	0,										// ItemSize
	TYPE_FLAG_DEFAULT | TYPE_FLAG_BASETYPE,	// Flags
	Float_StrRepr,							// StringRepr
	Float_Hash,								// Hash
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
