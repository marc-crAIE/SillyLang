#include "Objects/SiStringObject.h"

#include "Memory/Mem.h"

#include "Error/SiError.h"

#pragma region Methods

static SiObject* String_StrRepr(SiObject* self)
{
	return self;
}

#pragma endregion


SiAPI_DATA(SiTypeObject) SiStringType = {
	SiVarObject_Head_Init(&SiStringType, 0),	// Base
	"string",									// Name
	"String object type",						// Doc
	sizeof(SiStringObject),						// Size
	0,											// ItemSize
	TYPE_FLAG_DEFAULT | TYPE_FLAG_BASETYPE,		// Flags
	String_StrRepr,								// StringRepr
	NULL,										// Dealloc
	NULL,										// Free
	NULL										// BaseType
};

SiObject* SiStringObject::FromString(Si_string_t str)
{
	return FromCharArray(str.c_str());
}

SiObject* SiStringObject::FromCharArray(const char* str)
{
	return FromCharArrayAndSize(str, strlen(str));
}

SiObject* SiStringObject::FromCharArrayAndSize(const char* str, Si_size_t size)
{
	SiStringObject* obj;
	size_t alloc;

	if (size < 0)
	{
		SiError::SetString(&SiSystemErrorException, "negative size passed to SiStringObject_FromCharArrayAndSize");
		return NULL;
	}

	obj = SiObject_New(SiStringObject, &SiStringType);
	if (obj == NULL)
		return NULL;
	if (size == 0)
	{
		obj->m_Value = NULL;
		alloc = 0;
	}
	else
	{
		alloc = size + 1;
		obj->m_Value = (char*)Memory::Alloc(alloc);
		if (str != NULL && size > 0)
			memcpy(obj->m_Value, str, size);
		obj->m_Value[size] = '\0'; // Trailing NULL byte (end of string)
	}
	SiVarObject_SetSize(obj, size);
	obj->m_Alloc = alloc;
	return SiObject_Cast(obj);
}
