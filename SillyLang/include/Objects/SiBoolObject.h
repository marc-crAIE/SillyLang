#pragma once

#include "Objects/SiIntObject.h"

// Bool is marked as final as it should not be inherited from

class SiBoolObject final : public SiIntObject
{
public:
	static SiObject* FromInt(Si_int32_t value);
};

SiAPI_DATA(SiTypeObject) SiBoolType;

#define SiBool_Check(x) Si_Is_Type(x, &SiBoolType)

/*
	Booleans are weird in SillyLang as it has 3 bool values:
		- True
		- False
		- Maybe
	True is for a value equal to 1, False is for a value equal to 0, and Maybe is for any other value as clearly
	it is not decided if the result should be 1 or 0. So maybe its either one but not sure.
	Purpose? Not sure but seems like a silly thing to have.

	Also make sure to increase the reference count of each value when returning.
*/

// Do not use these directly, instead use the macros
SiAPI_DATA(SiIntObject) SiTrueValue, SiFalseValue, SiMaybeValue;

// Use these macros
#define Si_True ((SiObject*) &SiTrueValue)
#define Si_False ((SiObject*) &SiFalseValue)
#define Si_Maybe ((SiObject*) &SiMaybeValue)

// Macros for returning Si_True, Si_False, and Si_Maybe
#define Si_Return_True return SiObject_NewRef(Si_True);
#define Si_Return_False return SiObject_NewRef(Si_False);
#define Si_Return_Maybe return SiObject_NewRef(Si_Maybe);