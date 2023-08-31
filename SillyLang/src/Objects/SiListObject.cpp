#include "Objects/SiListObject.h"

#include <Memory/Mem.h>

#include "Error/SiError.h"

#pragma region Helper Functions

static inline bool List_ValidIndex(Si_size_t i, Si_size_t limit)
{
	return i < limit;
}

static int List_Resize(SiListObject* self, Si_size_t newSize)
{
	SiObject** items;
	Si_size_t newAlloc, numAllocBytes;
	Si_size_t alloc = self->GetAllocated();

	if (alloc >= newSize && newSize >= (alloc >> 1))
	{
		assert(self->GetItems() != nullptr || newSize != 0);
		SiVarObject_SetSize(self, newSize);
		return 0;
	}

	/* This code will over-allocate the list proportional to its size
	*  which allows it to make room for addition growth. This just helps
	*  with performance with reallocating memory especially in cases where
	*  there may be a long sequence of appending.
	* 
	*  The growth pattern is: 0, 4, 8, 16, 24, 32, 40, 52, 64, 76, ...
	*/
	newAlloc = ((Si_size_t)newSize + (newSize >> 3) + 6) & ~(Si_size_t)3;

	if (newSize - Si_Size(self) > (Si_size_t)(newAlloc - newSize))
		newAlloc = ((Si_size_t)newSize + 3) & ~(Si_size_t)3;

	if (newSize == 0)
		newAlloc = 0;
	numAllocBytes = newAlloc * sizeof(SiObject*);
	items = (SiObject**)Memory::Realloc(self->m_Items, numAllocBytes);
	if (items == nullptr)
	{
		SiError::OutOfMemory();
		return -1;
	}

	self->m_Items = items;
	SiVarObject_SetSize(self, newSize);
	self->m_Alloc = newAlloc;
	return 0;
}

static int List_Append(SiListObject* self, SiObject* obj)
{
	assert(obj != nullptr);

	Si_size_t n = self->GetSize();
	assert((Si_size_t)n + 1 < SI_SIZE_T_MAX);
	if (List_Resize(self, n + 1) < 0)
		return -1;

	obj->IncRef();
	self->m_Items[n] = obj;
	return 0;
}

#pragma endregion

SiAPI_DATA(SiTypeObject) SiListType = {
	SiVarObject_Head_Init(&SiListType, 0),	// Base
	"list",									// Name
	"List object type",						// Doc
	sizeof(SiListObject),					// Size
	0,										// ItemSize
	TYPE_FLAG_DEFAULT | TYPE_FLAG_BASETYPE	// Flags
	| TYPE_FLAG_LIST_SUBCLASS,				// ..
	NULL,									// StringRepr
	NULL,									// Dealloc
	NULL,									// Free
	NULL									// BaseType
};

void SiListObject::Add(SiObject* item)
{
	List_Append(this, item);
}

void SiListObject::Resize(Si_size_t newSize)
{
	List_Resize(this, newSize);
}

void SiListObject::SetItem(SiObject* item, Si_size_t index)
{
	if (!List_ValidIndex(index, GetSize()))
	{
		item->DecRef();
		// TODO: Index out of range exception
		SiError::SetString(&SiIndexErrorException, "list assignment index out of range");
		return;
	}

	m_Items[index]->DecRef();
	m_Items[index] = item;
}

SiObject* SiListObject::Create(Si_size_t size)
{
	SiListObject* obj;
	Si_size_t alloc;

	obj = SiObject_New(SiListObject, &SiListType);
	if (obj == nullptr)
		return nullptr;

	if (size == 0)
	{
		obj->m_Items = nullptr;
		alloc = 0;
	}
	else
	{
		alloc = size * sizeof(SiObject*);
		obj->m_Items = (SiObject**)(Memory::Alloc(alloc));
	}

	SiVarObject_SetSize(obj, size);
	obj->m_Alloc = size;
	return SiObject_Cast(obj);
}
