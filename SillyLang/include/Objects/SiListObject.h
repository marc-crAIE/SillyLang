#pragma once

#include "Objects/SiObject.h"

struct SiListObject : public SiVarObject
{
public:
	void Add(SiObject* item);
	void Resize(Si_size_t newSize);
	void SetItem(SiObject* item, Si_size_t index);

	inline Si_size_t GetSize() const { return Si_Size(this); }
	inline Si_size_t GetAllocated() const { return m_Alloc; }
	inline SiObject** GetItems() { return m_Items; }
public:
	static SiObject* Create(Si_size_t size = 0);
public:
	SiObject** m_Items;
	Si_size_t m_Alloc;
};

SiAPI_DATA(SiTypeObject) SiListType;

#define SiList_Check(self) SiObject_TypeCheck(self, &SiListType)
#define SiList_CheckExact(self) Si_Is_Type(self, &SiListType)

#define SiList_Cast(obj) (assert(SiList_Check(obj)), ((SiListObject*)obj))