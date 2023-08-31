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

	SiObject* obj = SiStringObject::FromCharArray("Hello world!");
	obj->Print();

	if (SiError::Occurred())
		SiError::Print();

	SillyLang::GetRuntime()->Finalize();
	return exitCode;
}

int main(int argc, char** argv)
{
	return SiMain();
}