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

int SiTypeObject::Ready(SiTypeObject* type)
{
	SiTypeObject* base;

	if (type->m_Flags & TYPEFLAG_READY)
		return 0;

	assert((type->m_Flags & TYPEFLAG_READYING) == 0);

	type->m_Flags |= TYPEFLAG_READYING;

	if (type->m_Name == nullptr)
	{
		// TODO: return error
		goto error;
	}

	// Initialize the tp_base (defaults to BaseObject unless thats's us)
	base = type->m_BaseType;
	if (base == NULL && type != &SiBaseType)
	{
		base = &SiBaseType;
		if (type->m_Flags & TYPEFLAG_HEAPTYPE)
			type->m_BaseType = (SiTypeObject*)SiObject_NewRef(base);
		else
			type->m_BaseType = base;
	}

	// Init the base class
	if (base != NULL)
	{
		if (SiType_Ready(base) < 0)
			goto error;
	}

	// Init base type if null
	if (Si_Is_Type(type, NULL) && base != NULL)
		SiObject_SetType(type, Si_Type(base));
error:
	type->m_Flags &= ~TYPEFLAG_READYING;
	return 0;
}
