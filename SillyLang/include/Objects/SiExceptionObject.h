#pragma once

#include "Objects/SiObject.h"

enum SiExceptionExitCodes
{
	EXC_EXIT_EXCEPTION = 1,
	EXC_EXIT_TYPE_ERROR,
	EXC_EXIT_INDEX_ERROR,
	EXC_EXIT_VALUE_ERROR,
	EXC_EXIT_SYNTAX_ERROR,
	EXC_EXIT_INDENTATION_ERROR,
	EXC_EXIT_RECURSION_ERROR,
	EXC_EXIT_SYSTEM_ERROR,
	EXC_EXIT_RUNTIME_ERROR,
	EXC_EXIT_MEMORY_ERROR
};

/*
*		Exception Objects
*/

struct SiExceptionObject : public SiVarObject
{
public:
	~SiExceptionObject();

	inline SiObject* GetType() const { return m_TypeStr; }
	inline SiObject* GetContext() const { return m_Context; }
	inline int GetExitCode() const { return m_ExitCode; }
public:
	SiObject* m_TypeStr;
	SiObject* m_Context;
	int m_ExitCode;
};

#define SiException_Check(self) ((Si_Type(self)->m_Flags & TYPE_FLAG_EXC_SUBCLASS) != 0)

#define SiException_Cast(obj) ((SiExceptionObject*)obj)
#define SiException_SafeCast(obj) (assert(SiException_Check(obj)), ((SiExceptionObject*)obj))

SiAPI_DATA(SiExceptionObject) SiException;

SiAPI_DATA(SiExceptionObject) SiTypeErrorException;
SiAPI_DATA(SiExceptionObject) SiIndexErrorException;
SiAPI_DATA(SiExceptionObject) SiValueErrorException;

SiAPI_DATA(SiExceptionObject) SiSyntaxErrorException;
SiAPI_DATA(SiExceptionObject) SiIndentationErrorException;
SiAPI_DATA(SiExceptionObject) SiRecursionErrorException;

SiAPI_DATA(SiExceptionObject) SiSystemErrorException;
SiAPI_DATA(SiExceptionObject) SiRuntimeErrorException;
SiAPI_DATA(SiExceptionObject) SiMemoryErrorException;

/*
*		Exception Types
*/

SiAPI_DATA(SiTypeObject) SiExceptionType;

SiAPI_DATA(SiTypeObject) SiTypeErrorExceptionType;
SiAPI_DATA(SiTypeObject) SiIndexErrorExceptionType;
SiAPI_DATA(SiTypeObject) SiValueErrorExceptionType;

SiAPI_DATA(SiTypeObject) SiSyntaxErrorExceptionType;
SiAPI_DATA(SiTypeObject) SiIndentationErrorExceptionType;

SiAPI_DATA(SiTypeObject) SiSystemErrorExceptionType;
SiAPI_DATA(SiTypeObject) SiRuntimeErrorExceptionType;
SiAPI_DATA(SiTypeObject) SiMemoryErrorExceptionType;
