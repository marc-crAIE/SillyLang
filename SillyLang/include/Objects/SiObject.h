#pragma once

#include "port.h"

#include "Core/SiStatus.h"

typedef struct SiTypeObject SiTypeObject;

#pragma region Object

struct SiObject
{
public:
	void Init(SiTypeObject* type);
	void NewRef();

	void Print();

	inline SiObject* ToString();

	inline void SetType(SiTypeObject* type);
	SiTypeObject* GetType() const { return m_Type; }

	inline void IncRef() { m_RefCount++; }
	inline void DecRef() 
	{ 
		m_RefCount--;
		if (m_RefCount == 0)
			m_Type->m_Method_Dealloc(this);
	}
public:
	static SiObject* New(SiTypeObject* type);
	static SiObject* NewRef(SiObject* obj);
public:
	size_t m_RefCount;
	SiTypeObject* m_Type;
};

#define SiObject_Cast(op) ((SiObject*)(op))
#define SiObject_Cast_Const(op) ((const SiObject*)(op))

#define SiObject_Head SiObject m_Base;
#define SiObject_Head_Init(type) { 1, type }

#define SiObject_New(type, typedef) (type*)SiObject::New(typedef)
#define SiObject_NewRef(obj) SiObject::NewRef(SiObject_Cast(obj))

#define SiObject_SetType(obj, type) SiObject_Cast(obj)->SetType(type)

#pragma endregion

#pragma region Variable-size Object

struct SiVarObject : public SiObject
{
public:
	inline void SetSize(size_t size) { m_Size = size; }
	size_t GetSize() const { return m_Size; }
public:
	size_t m_Size;
private:
	friend SiObject;
};

#define SiVarObject_Cast(op) ((SiVarObject*)(op))
#define SiVarObject_Cast_Const(op) ((const SiVarObject*)(op))

#define SiVarObject_Head SiVarObject m_Base;
#define SiVarObject_Head_Init(type, size) { SiObject_Head_Init(type), size }

#define SiVarObject_SetSize(obj, size) SiVarObject_Cast(obj)->SetSize(size)

#pragma endregion

#pragma region Misc

#define Si_Type(ob) SiObject_Cast(ob)->GetType()
#define Si_Size(ob) (SiVarObject_Cast(ob)->GetSize())

#pragma endregion

#pragma region Type Object

enum SiTypeFlags
{
	TYPEFLAG_DEFAULT	= 0,

	TYPEFLAG_READY		= (1UL << 0),
	TYPEFLAG_READYING	= (1UL << 1),

	TYPEFLAG_HEAPTYPE	= (1UL << 2),
	TYPEFLAG_BASETYPE	= (1UL << 3),
};

inline SiTypeFlags operator|(SiTypeFlags a, SiTypeFlags b)
{
	return static_cast<SiTypeFlags>(static_cast<int>(a) | static_cast<int>(b));
}

inline SiTypeFlags& operator|=(SiTypeFlags& a, SiTypeFlags b)
{
	return a = static_cast<SiTypeFlags>(static_cast<int>(a) | static_cast<int>(b));
}

inline SiTypeFlags operator&(SiTypeFlags a, SiTypeFlags b)
{
	return static_cast<SiTypeFlags>(static_cast<int>(a) & static_cast<int>(b));
}

inline SiTypeFlags& operator&=(SiTypeFlags& a, SiTypeFlags b)
{
	return a = static_cast<SiTypeFlags>(static_cast<int>(a) & static_cast<int>(b));
}

inline SiTypeFlags operator~(SiTypeFlags a)
{
	return static_cast<SiTypeFlags>(~static_cast<int>(a));
}

typedef SiObject* (*StrRepr)(SiObject*);
typedef void (*Destructor)(SiObject*);
typedef void (*FreeFunc)(void*);

struct SiTypeObject
{
public:
	static int Ready(SiTypeObject* type);

	static inline bool IsType(const SiObject* obj, const SiTypeObject* type)
	{
		return Si_Type(obj) == type;
	}
public:
	SiVarObject_Head;
	const char* m_Name;				// SiObject type name
	const char* m_Doc;				// SiObject type documentation
	size_t m_Size;
	size_t m_ItemSize;				// Used for memory allocation
	SiTypeFlags m_Flags;			// Flags for specific features and behaviour

	/* Methods to implement standard operations */

	StrRepr m_Method_StringRepr;	// SiString representation
	Destructor m_Method_Dealloc;
	FreeFunc m_Method_Free;

	SiTypeObject* m_BaseType;
};

#define SiType_Ready(type) SiTypeObject::Ready(type)

#define Si_Is_Type(obj, type) SiTypeObject::IsType(SiObject_Cast_Const(obj), type)
#define SiObject_TypeCheck(obj, type) (Si_Is_Type(obj, type))

#pragma endregion
