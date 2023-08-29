#include "Objects/SiBaseObject.h"

#include <Memory/Mem.h>

static void Object_Dealloc(SiObject* self)
{
	Si_Type(self)->m_Method_Free(SiObject_Cast(self));
}

SiAPI_DATA(SiTypeObject) SiBaseType
{
	SiVarObject_Head_Init(&SiBaseType, 0),	// Base
	"type",									// Name
	"Base type",							// Doc
	sizeof(SiObject),						// Size
	0,										// ItemSize
	TYPEFLAG_DEFAULT | TYPEFLAG_BASETYPE,	// Flags
	(Destructor)Object_Dealloc,				// Dealloc
	Memory::Free,							// Free
	NULL									// BaseType
};