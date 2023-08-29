#include "Objects/SiObject.h"

#include "Memory/Mem.h"

#include "Objects/SiBaseObject.h"

void SiObject::Init(SiTypeObject* type)
{
	SetType(type);
	NewRef();
}

void SiObject::NewRef()
{
	m_RefCount = 1;
}

inline void SiObject::SetType(SiTypeObject* type)
{
	m_Type = type;
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
