#include <iostream>

#include "../SillyLang.h"

SiStatus init()
{
	SiStatus status = Lifecycle::InitTypes();
	if (status.IsException())
		std::cout << "An error occured with initializing object types" << std::endl;
	return status;
}

int main()
{
	SiStatus status = init();
	if (status.IsException())
		return -1;

	SiObject* obj = SiIntObject::FromInt(10);
	SiObject* obj2 = SiStringObject::FromCharArray("Hello world!");
	SiObject* obj3 = SiObject_NewRef(Si_True);

	obj2->Print();

	return 0;
}