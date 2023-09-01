#pragma once

#include "Objects/SiObject.h"

class SiStringObject : public SiVarObject
{
public:
	const char* GetValue() const { return m_Value; }
	void SetValue(Si_string_t& value) { m_Value = (char*)value.c_str(); }
public:
	static SiObject* Concat(SiObject* a, const char* b);
	static SiObject* Concat(SiObject* a, SiObject* b);

	static SiObject* FromString(Si_string_t str);

	template<typename ... Args>
	static SiObject* FromFormat(const Si_string_t& format, Args ... args)
	{
		Si_size_t size = snprintf(nullptr, 0, format.c_str(), args ...) + 1; // Extra space for '\0'
		if (size <= 0)
		{
			SiError::SetString(&SiSystemErrorException, "error occurred when formatting string");
		}
		std::unique_ptr<char[]> buf(new char[size]);
		snprintf(buf.get(), size, format.c_str(), args ...);

		return FromCharArray(Si_string_t(buf.get(), buf.get() + size - 1).c_str());
	}

	static SiObject* FromCharArray(const char* str);
	static SiObject* FromCharArrayAndSize(const char* str, Si_size_t size);
private:
	char* m_Value;
	Si_size_t m_Alloc;
};

SiAPI_DATA(SiTypeObject) SiStringType;

#define SiString_Check(self) SiObject_TypeCheck(self, &SiStringType)
#define SiString_CheckExact(self) Si_Is_Type(self, &SiStringType)

#define SiString_Cast(obj) ((SiStringObject*)obj)
#define SiString_SafeCast(obj) (assert(SiString_Check(obj)), ((SiStringObject*)obj))