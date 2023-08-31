#pragma once

#include "Core/SiThread.h"
#include "Objects/SiObject.h"
#include "Objects/SiExceptionObject.h"

class SiError final
{
public:
	static void Set(SiObject* exception);
	static void SetObject(SiObject* exception, SiObject* value);
	static void SetString(SiObject* exception, const char* str);

	static void Clear();
	static void Restore(SiObject* exception);

	template<typename ... Args>
	static void Format(SiObject* exception, const Si_string_t& format, Args ... args)
	{
		Si_size_t size = snprintf(nullptr, 0, format.c_str(), args ...) + 1; // Extra space for '\0'
		if (size <= 0)
		{
			SetString(&SiSystemErrorException, "error occurred when formatting string");
		}
		std::unique_ptr<char[]> buf(new char[size]);
		snprintf(buf.get(), size, format.c_str(), args ...);

		SetString(exception, Si_string_t(buf.get(), buf.get() + size - 1).c_str());
	}

	static void Fatal(const char* message);
	static void Fatal(SiObject* exception, const char* message);

	static void Print();
	static SiObject* Occurred();

	// Helper functions

	static void OutOfMemory();
};
