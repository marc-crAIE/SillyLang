#include "Objects/SiStringObject.h"

#include "Memory/Mem.h"
#include "Utils/Hash.h"
#include "Error/SiError.h"

#pragma region Methods

static SiObject* String_StrRepr(SiObject* self)
{
	SiObject* repr = SiStringObject::FromCharArray("\"");
	repr = SiStringObject::Concat(repr, self);
	repr = SiStringObject::Concat(repr, "\"");
	return repr;
}

static Si_hash_t String_Hash(SiObject* self)
{
	SiStringObject* str = SiString_SafeCast(self);
	return Hash::CRC32B(str->GetValue());
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
	String_Hash,								// Hash
	NULL,										// Dealloc
	NULL,										// Free
	NULL										// BaseType
};

SiObject* SiStringObject::Concat(SiObject* a, const char* b)
{
	SiObject* bStr = SiStringObject::FromCharArray(b);
	SiObject* result = Concat(a, bStr);
	bStr->DecRef();
	return result;
}

SiObject* SiStringObject::Concat(SiObject* a, SiObject* b)
{
	if (!SiString_Check(a) || !SiString_Check(b))
	{
		SiError::SetString(&SiTypeErrorException, "can only concat strings");;
		return nullptr;
	}
	
	SiStringObject* result = nullptr;

	if (Si_Size(a) == 0)
	{
		result = SiString_SafeCast(b);
		result->IncRef();
		return SiObject_Cast(result);
	}

	if (Si_Size(b) == 0)
	{
		result = SiString_SafeCast(a);
		result->IncRef();
		return SiObject_Cast(result);
	}

	result = SiString_SafeCast(SiStringObject::FromCharArrayAndSize(nullptr, Si_Size(a) + Si_Size(b)));
	if (result)
	{
		memcpy(result->m_Value, SiString_SafeCast(a)->m_Value, Si_Size(a));
		memcpy(result->m_Value + Si_Size(a), SiString_SafeCast(b)->m_Value, Si_Size(b));
	}
	
	return SiObject_Cast(result);
}

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
