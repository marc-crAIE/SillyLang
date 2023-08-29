#include <iostream>

#include "../SillyLang.h"

int main()
{
	SiStatus status = Lifecycle::InitTypes();
	if (status.IsException())
	{
		std::cout << "An error occured with initializing object types" << std::endl;
		return -1;
	}

	SiObject* obj = SiIntObject::FromInt(10);
	SiIntObject* iObj = SiInt_Cast(obj);

	SiObject* obj2 = SiStringObject::FromCharArray("Hello world!");
	SiStringObject* sObj = SiString_Cast(obj2);

	std::cout << sObj->GetValue() << std::endl;

	return 0;
}