#pragma once

#include "Objects/SiObject.h"

struct SiFloatObject : public SiVarObject
{
public:
	double GetValue() const { return m_Value; }
	void SetValue(double value) { m_Value = value; }
public:
	static SiObject* FromFloat(float value);
	static SiObject* FromDouble(double value);
	static SiObject* FromString(const char* str);
public:
	double m_Value;
};

SiAPI_DATA(SiTypeObject) SiFloatType;

#define SiFloat_Check(self) SiObject_TypeCheck(self, &SiFloatType)
#define SiFloat_CheckExact(self) Si_Is_Type(self, &SiFloatType)

#define SiFloat_Cast(obj) ((SiFloatObject*)obj)
#define SiFloat_SafeCast(obj) (assert(SiFloat_Check(obj)), ((SiFloatObject*)obj))