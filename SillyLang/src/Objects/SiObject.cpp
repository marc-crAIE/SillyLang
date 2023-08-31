#include "Objects/SiObject.h"

#include "Core/SillyLang.h"

#include "Memory/Mem.h"
#include "Error/SiError.h"

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
		return SiStringObject::FromFormat("<%s object at %p>", m_Type->m_Name, this);

	SiThread* thread = SillyLang::GetThread();

	if (thread->EnterRecursiveCall("while getting the string representation of an object"))
		return nullptr;
	SiObject* repr = (*m_Type->m_Method_StringRepr)(this);
	thread->LeaveRecursiveCall();

	if (!repr)
		goto error;

	if (!SiString_Check(repr))
	{
		SiError::Format(&SiTypeErrorException, "returned a non-string (type %.200s)", Si_Type(repr)->m_Name);
		repr->DecRef();
		return nullptr;
	}

	return repr;
error:
	return SiObject_NewRef(s_ErrorString);
}

inline void SiObject::SetType(SiTypeObject* type)
{
	m_Type = type;
}

void SiObject::IncRef()
{
	if (this)
		m_RefCount++;
}

void SiObject::DecRef()
{
	if (this)
	{
		m_RefCount--;
		if (m_RefCount == 0)
			m_Type->m_Method_Dealloc(this);
	}
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
