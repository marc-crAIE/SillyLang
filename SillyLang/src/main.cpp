#include <iostream>

#include "SillyLang.h"
#include "Core/SiCore.h"

SiStatus SiMain_Init()
{
	SiStatus status = SillyLang::Init();
	if (status.IsException())
	{
		std::cout << "Error: " << status.ErrorMsg << std::endl;
		return status;
	}

	return status;
}

int SiMain()
{
	int exitCode = 0;

	SiStatus status = SiMain_Init();
	if (status.IsException())
		exitCode = status.ExitCode;

	SiObject* obj = SiObject_NewRef(Si_Maybe);
	Si_hash_t hash = obj->Hash();
	std::cout << hash << std::endl;
	SiObject* objHash = SiIntObject::FromInt(hash);
	objHash->Print();

	if (SiError::Occurred())
		SiError::Print();

	SillyLang::GetRuntime()->Finalize();
	return exitCode;
}

int main(int argc, char** argv)
{
	return SiMain();
}