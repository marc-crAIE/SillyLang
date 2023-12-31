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

	Si_hash_t Hash();
	inline SiObject* ToString();

	inline void SetType(SiTypeObject* type);
	SiTypeObject* GetType() const { return m_Type; }

	void IncRef();
	void DecRef();
public:
	static SiObject* New(SiTypeObject* type);
	static SiObject* NewRef(SiObject* obj);
public:
	Si_size_t m_RefCount;
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
	inline void SetSize(Si_size_t size) { m_Size = size; }
	Si_size_t GetSize() const { return m_Size; }
public:
	Si_size_t m_Size;
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
	TYPE_FLAG_DEFAULT		= 0,

	TYPE_FLAG_READY			= (1UL << 0),
	TYPE_FLAG_READYING		= (1UL << 1),

	TYPE_FLAG_HEAPTYPE		= (1UL << 2),
	TYPE_FLAG_BASETYPE		= (1UL << 3),

	TYPE_FLAG_INT_SUBCLASS	= (1UL << 4),
	TYPE_FLAG_LIST_SUBCLASS = (1UL << 5),
	TYPE_FLAG_EXC_SUBCLASS	= (1UL << 6),
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
typedef Si_hash_t (*HashFunc)(SiObject*);
typedef void (*Destructor)(SiObject*);
typedef void (*FreeFunc)(void*);

struct SiTypeObject
{
public:
	static int Ready(SiTypeObject* type);

	static inline bool IsType(const SiObject* obj, const SiTypeObject* type) { return Si_Type(obj) == type; }
	static bool IsSubtype(SiTypeObject* a, SiTypeObject* b);
public:
	SiVarObject_Head;
	const char* m_Name;				// SiObject type name
	const char* m_Doc;				// SiObject type documentation
	Si_size_t m_Size;
	Si_size_t m_ItemSize;			// Used for memory allocation
	SiTypeFlags m_Flags;			// Flags for specific features and behaviour

	/* Methods to implement standard operations */

	StrRepr m_Method_StringRepr;	// SiString representation
	HashFunc m_Method_Hash;			// Hash of the object
	Destructor m_Method_Dealloc;
	FreeFunc m_Method_Free;

	SiTypeObject* m_BaseType;
};

#define SiType_Ready(type) SiTypeObject::Ready(type)

#define Si_Is_Type(obj, type) SiTypeObject::IsType(SiObject_Cast_Const(obj), type)
#define SiObject_TypeCheck(obj, type) (Si_Is_Type(obj, type) || SiTypeObject::IsSubtype(Si_Type(obj), type))

#pragma endregion
