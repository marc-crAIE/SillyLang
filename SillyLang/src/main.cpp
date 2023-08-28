#include <iostream>

#include "../SillyLang.h"

int main()
{
	SiStatus status = Lifecycle::InitTypes();

	SiObject* obj = SiIntObject::FromInt(10);
	SiIntObject* iObj = SiInt_Cast(obj);

	SiObject* obj2 = SiStringObject::FromCharArray("Hello world!");
	SiStringObject* sObj = SiString_Cast(obj2);

	std::cout << sObj->GetValue() << std::endl;

	return 0;
}