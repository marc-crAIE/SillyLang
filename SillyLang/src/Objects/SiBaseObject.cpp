#include "Objects/SiBaseObject.h"

#include <Memory/Mem.h>

#include "Objects/SiStringObject.h"

static SiObject* Object_StrRepr(SiObject* self)
{
	SiObject* repr = SiStringObject::FromCharArray(Si_Type(self)->m_Name);
	return repr;
}

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
	TYPE_FLAG_DEFAULT | TYPE_FLAG_BASETYPE,	// Flags
	Object_StrRepr,							// StringRepr
	Object_Dealloc,							// Dealloc
	Memory::Free,							// Free
	NULL									// BaseType
};