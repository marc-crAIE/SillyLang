#pragma once

#include "Objects/SiObject.h"

class SiStringObject : public SiVarObject
{
public:
	const char* GetValue() const { return m_Value; }
	void SetValue(std::string& value) { m_Value = (char*)value.c_str(); }
public:
	static SiObject* FromString(std::string str);
	static SiObject* FromCharArray(const char* str);
	static SiObject* FromCharArrayAndSize(const char* str, size_t size);

	static SiStatus InitTypes();
private:
	char* m_Value;
	size_t m_Alloc;
};

SiAPI_DATA(SiTypeObject) SiStringType;

#define SiString_Check(self) SiObject_TypeCheck(self, &SiStringType)
#define SiString_CheckExact(self) Si_Is_Type(self, &SiStringType)

#define SiString_Cast(obj) (assert(SiString_Check(obj)), ((SiStringObject*)obj))