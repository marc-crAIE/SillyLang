#include "Error/SiError.h"

#include "Core/SillyLang.h"
#include "Objects/SiStringObject.h"

void SiError::Set(SiObject* exception)
{
	SetObject(exception, SiObject_Cast(NULL));
}

void SiError::SetObject(SiObject* exception, SiObject* value)
{
	if (!SiException_Check(exception))
	{
		SetString(&SiSystemErrorException, "exception is not an Exception object");
		return;
	}
	assert(SiString_Check(value));

	SiExceptionObject* exc = SiException_Cast(exception);
	value->IncRef();
	exc->m_Context = value;
	Restore(exc);
}

void SiError::SetString(SiObject* exception, const char* str)
{
	SiObject* value = SiStringObject::FromCharArray(str);
	SetObject(exception, value);
	value->DecRef();
}

void SiError::Clear()
{
	Restore(nullptr);
}

void SiError::Restore(SiObject* exception)
{
	SiThread* thread = SillyLang::GetThread();
	SiObject* oldException;
	
	oldException = thread->m_CurrException;
	thread->m_CurrException = exception;

	exception->IncRef();
	oldException->DecRef();
}

void SiError::Fatal(const char* message)
{
	Fatal(&SiSystemErrorException, message);
}

void SiError::Fatal(SiObject* exception, const char* message)
{
	SetString(exception, message);
}

void SiError::Print()
{
	SiThread* thread = SillyLang::GetThread();
	assert(thread != nullptr);

	if (Occurred())
	{
		SiExceptionObject* exc = SiException_Cast(thread->m_CurrException);
		std::string msg = SiString_Cast(exc->GetType())->GetValue();
		msg += ": ";
		msg += SiString_Cast(exc->GetContext())->GetValue();

		std::cout << msg << std::endl;
		SillyLang::Exit(exc->m_ExitCode);
	}
}

SiObject* SiError::Occurred()
{
	SiThread* thread = SillyLang::GetThread();
	assert(thread != nullptr);
	return thread->m_CurrException;
}

void SiError::OutOfMemory()
{
	SetString(&SiMemoryErrorException, "out of memory");
}
