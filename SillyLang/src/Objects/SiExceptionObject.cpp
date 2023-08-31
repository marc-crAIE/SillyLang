#include "Objects/SiExceptionObject.h"

#include "Objects/SiStringObject.h"

#define SI_EXCEPTION_TYPE_DEF(type, name, desc) \
SiAPI_DATA(SiTypeObject) Si ##type## Type = {	\
	SiVarObject_Head_Init(&Si ##type## Type, 0),\
	name,										\
	desc,										\
	sizeof(SiExceptionObject),					\
	0,											\
	TYPE_FLAG_DEFAULT | TYPE_FLAG_BASETYPE		\
	| TYPE_FLAG_EXC_SUBCLASS,					\
	NULL,										\
	NULL,										\
	NULL,										\
	&SiExceptionType							\
}

#define SI_EXCEPTION_VALUE_DEF(type, name, exitCode)	\
SiExceptionObject Si ## type = {								\
	SiVarObject_Head_Init(&Si ## type ## Type, 0),				\
	SiStringObject::FromCharArray(name),						\
	NULL,														\
	exitCode,													\
};

#define SI_EXCEPTION_DEF(type, name, desc, exitCode)	\
SI_EXCEPTION_TYPE_DEF(type, name, desc);						\
SI_EXCEPTION_VALUE_DEF(type, name, exitCode)

SiAPI_DATA(SiTypeObject) SiExceptionType = {
	SiVarObject_Head_Init(&SiExceptionType, 0),	// Base
	"Exception",								// Name
	"Exception object type",					// Doc
	sizeof(SiExceptionObject),					// Size
	0,											// ItemSize
	TYPE_FLAG_DEFAULT | TYPE_FLAG_BASETYPE		// Flags
	| TYPE_FLAG_EXC_SUBCLASS,					// ..
	NULL,										// StringRepr
	NULL,										// Dealloc
	NULL,										// Free
	NULL										// BaseType
};

SI_EXCEPTION_VALUE_DEF(Exception, "Exception", EXC_EXIT_EXCEPTION);

SI_EXCEPTION_DEF(TypeErrorException, "TypeErrorException", "Type error exception object type", EXC_EXIT_TYPE_ERROR);
SI_EXCEPTION_DEF(IndexErrorException, "IndexErrorException", "Index error exception object type", EXC_EXIT_INDEX_ERROR);
SI_EXCEPTION_DEF(ValueErrorException, "ValueErrorException", "Value error exception object type", EXC_EXIT_VALUE_ERROR);

SI_EXCEPTION_DEF(SyntaxErrorException, "SyntaxErrorException", "Syntax error exception object type", EXC_EXIT_SYNTAX_ERROR);
SI_EXCEPTION_DEF(IndentationErrorException, "IndentationErrorException", "Indentation error exception object type", EXC_EXIT_INDENTATION_ERROR);
SI_EXCEPTION_DEF(RecursionErrorException, "RecursionErrorException", "Recursion error exception object type", EXC_EXIT_RECURSION_ERROR);

SI_EXCEPTION_DEF(SystemErrorException, "SystemErrorException", "System error exception object type", EXC_EXIT_SYSTEM_ERROR);
SI_EXCEPTION_DEF(RuntimeErrorException, "RuntimeErrorException", "Runtime error exception object type", EXC_EXIT_RUNTIME_ERROR);
SI_EXCEPTION_DEF(MemoryErrorException, "MemoryErrorException", "Memory error exception object type", EXC_EXIT_MEMORY_ERROR);

SiExceptionObject::~SiExceptionObject()
{
	m_TypeStr->DecRef();
	m_Context->DecRef();
}