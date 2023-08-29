#pragma once

#include "Objects/SiObject.h"

class SiStringObject : public SiVarObject
{
public:
	const char* GetValue() const { return m_Value; }
	void SetValue(Si_string_t& value) { m_Value = (char*)value.c_str(); }
public:
	static SiObject* FromString(Si_string_t str);
	static SiObject* FromCharArray(const char* str);
	static SiObject* FromCharArrayAndSize(const char* str, Si_size_t size);
private:
	char* m_Value;
	Si_size_t m_Alloc;
};

SiAPI_DATA(SiTypeObject) SiStringType;

#define SiString_Check(self) SiObject_TypeCheck(self, &SiStringType)
#define SiString_CheckExact(self) Si_Is_Type(self, &SiStringType)

#define SiString_Cast(obj) (assert(SiString_Check(obj)), ((SiStringObject*)obj))