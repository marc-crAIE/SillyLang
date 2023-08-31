#include "Objects/SiBoolObject.h"

#include "Objects/SiStringObject.h"

static SiObject* s_TrueStr = SiStringObject::FromCharArray("True");
static SiObject* s_FalseStr = SiStringObject::FromCharArray("False");
static SiObject* s_MaybeStr = SiStringObject::FromCharArray("Maybe");

#pragma region Methods

static SiObject* Bool_StrRepr(SiObject* self)
{
	if (!Si_Is_Type(self, &SiBoolType))
		return nullptr;

	SiBoolObject* boolean = (SiBoolObject*)self;
	
	if (boolean->m_Value == 1)
		return SiObject_NewRef(s_TrueStr);
	else if (boolean->m_Value == 0)
		return SiObject_NewRef(s_FalseStr);
	else
		return SiObject_NewRef(s_MaybeStr);
}

#pragma endregion


SiAPI_DATA(SiTypeObject) SiBoolType = {
	SiVarObject_Head_Init(&SiBoolType, 0),	// Base
	"bool",									// Name
	"Boolean object type",					// Doc
	sizeof(SiBoolObject),					// Size
	0,										// ItemSize
	TYPE_FLAG_DEFAULT | TYPE_FLAG_BASETYPE	// Flags
	| TYPE_FLAG_INT_SUBCLASS,				// ..
	Bool_StrRepr,							// StringRepr
	NULL,									// Dealloc
	NULL,									// Free
	&SiIntType								// BaseType
};

SiObject* SiBoolObject::FromInt(Si_int32_t value)
{
	SiObject* result;

	if (value == 1)
		result = Si_True;
	else if (value == 0)
		result = Si_False;
	else
		result = Si_Maybe;

	SiObject_NewRef(result);
	return result;
}

// The objects representing bool values True, False, and Maybe

SiIntObject SiTrueValue = {
	SiVarObject_Head_Init(&SiBoolType, 0),
	{ 1 }
};

SiIntObject SiFalseValue = {
	SiVarObject_Head_Init(&SiBoolType, 0),
	{ 0 }
};
SiIntObject SiMaybeValue = {
	SiVarObject_Head_Init(&SiBoolType, 0),
	{ -1 }
};