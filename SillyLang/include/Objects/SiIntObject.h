#pragma once

#include "Objects/SiObject.h"

class SiIntObject : public SiVarObject
{
public:
	int GetValue() const { return m_Value; }
	void SetValue(int value) { m_Value = value; }
public:
	static SiObject* FromInt(Si_int32_t value);
	static SiObject* FromString(const char* str, int base = 10);

	static SiStatus InitTypes();
private:
	Si_int32_t m_Value;
};

SiAPI_DATA(SiTypeObject) SiIntType;

#define SiInt_Check(self) SiObject_TypeCheck(self, &SiIntType)
#define SiInt_CheckExact(self) Si_Is_Type(self, &SiIntType)

#define SiInt_Cast(obj) (assert(SiInt_Check(obj)), ((SiIntObject*)obj))