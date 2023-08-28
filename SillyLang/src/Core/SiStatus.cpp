#include "Core/SiStatus.h"
#ifdef _MSC_VER
#  define SiStatus_GET_FUNC() __FUNCTION__
#else
#  define SiStatus_GET_FUNC() __func__
#endif

SiStatus SiStatus::Ok()
{
	return { STATUS_TYPE_OK };
}

SiStatus SiStatus::Error(const char* errorMsg)
{
	return {
		STATUS_TYPE_ERROR,
		SiStatus_GET_FUNC(),
		errorMsg
	};
}

SiStatus SiStatus::NoMemory()
{
	return Error("Memory allocation failed");
}

SiStatus SiStatus::Exit(int exitCode)
{
	return {
		STATUS_TYPE_EXIT,
		"",
		"",
		exitCode
	};
}
