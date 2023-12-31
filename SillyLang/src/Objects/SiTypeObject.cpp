#include "Objects/SiObject.h"

#include "Objects/SiBaseObject.h"

static int ReadyPreChecks(SiTypeObject* type)
{
	if (type->m_Flags & TYPE_FLAG_READY)
		return 1;

	assert((type->m_Flags & TYPE_FLAG_READYING) == 0);

	type->m_Flags |= TYPE_FLAG_READYING;

	if (type->m_Name == nullptr)
	{
		// TODO: return error
		return -1;
	}

	return 0;
}

static int ReadySetBaseType(SiTypeObject* type)
{
	SiTypeObject* base;

	// Initialize the tp_base (defaults to BaseObject unless thats's us)
	base = type->m_BaseType;
	if (base == NULL && type != &SiBaseType)
	{
		base = &SiBaseType;
		if (type->m_Flags & TYPE_FLAG_HEAPTYPE)
			type->m_BaseType = (SiTypeObject*)SiObject_NewRef(base);
		else
			type->m_BaseType = base;
	}

	// Init the base class
	if (base != NULL)
	{
		if (SiType_Ready(base) < 0)
			return -1;
	}

	// Init base type if null
	if (Si_Is_Type(type, NULL) && base != NULL)
		SiObject_SetType(type, Si_Type(base));

	return 0;
}

static int ReadyInherit(SiTypeObject* type)
{
	if (Si_Is_Type(type, &SiBaseType))
		return 0;

	SiTypeObject* base = type->m_BaseType;

	if (base == NULL)
		return -1;

	if (type->m_Method_StringRepr == NULL)
		type->m_Method_StringRepr = base->m_Method_StringRepr;

	if (type->m_Method_Hash == NULL)
		type->m_Method_Hash = base->m_Method_Hash;

	if (type->m_Method_Dealloc == NULL)
		type->m_Method_Dealloc = base->m_Method_Dealloc;

	if (type->m_Method_Free == NULL)
		type->m_Method_Free = base->m_Method_Free;

	return 0;
}

static void StopReadying(SiTypeObject* type)
{
	type->m_Flags &= ~TYPE_FLAG_READYING;
	type->m_Flags |= TYPE_FLAG_READY;
}

int SiTypeObject::Ready(SiTypeObject* type)
{
	int check = ReadyPreChecks(type);
	if (check < 0)
		goto error;
	else if (check > 0)
		return 0;

	if (ReadySetBaseType(type) < 0)
		goto error;

	if (ReadyInherit(type) < 0)
		goto error;

	StopReadying(type);
	return 0;

error:
	StopReadying(type);
	return -1;
}

bool SiTypeObject::IsSubtype(SiTypeObject* a, SiTypeObject* b)
{
	do
	{
		if (a == b)
			return true;
		a = a->m_BaseType;
	} while (a != nullptr);
	return (b == &SiBaseType);
}
