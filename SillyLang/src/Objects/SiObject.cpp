#include "Objects/SiObject.h"

#include "Memory/Mem.h"

#include "Objects/SiBaseObject.h"
#include "Objects/SiStringObject.h"

static SiObject* s_ErrorString = SiStringObject::FromCharArray("<NULL>");

void SiObject::Init(SiTypeObject* type)
{
	SetType(type);
	NewRef();
}

void SiObject::NewRef()
{
	m_RefCount = 1;
}

void SiObject::Print()
{
	SiStringObject* repr = SiString_Cast(ToString());
	std::cout << repr->GetValue() << std::endl;
}

inline SiObject* SiObject::ToString()
{
	if (!m_Type->m_Method_StringRepr)
		goto error;

	SiObject* repr = (*m_Type->m_Method_StringRepr)(this);
	if (repr == nullptr || !SiString_Check(repr))
		goto error;

	return repr;
error:
	return SiObject_NewRef(s_ErrorString);
}

inline void SiObject::SetType(SiTypeObject* type)
{
	m_Type = type;
}

void SiObject::DecRef()
{
	m_RefCount--;
	if (m_RefCount == 0)
		m_Type->m_Method_Dealloc(this);
}

SiObject* SiObject::New(SiTypeObject* type)
{
	SiObject* obj = (SiObject*)Memory::Alloc(type->m_Size);
	obj->Init(type);
	return obj;
}

SiObject* SiObject::NewRef(SiObject* obj)
{
	obj->IncRef();
	return obj;
}
