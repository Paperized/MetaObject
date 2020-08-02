#include <iostream>
#include "src/MetaManager.h"
#include "test/TestClass.h"

int main()
{
	MetaMngr.RegisterObject<int>()
		.AddMetaData("TYPE", "NUMBER")
		.AddMetaData("VERSION", "Common");

	MetaMngr.RegisterObject<double>();
	MetaMngr.RegisterObject<float>();
	MetaMngr.RegisterObject<MetaManager>()
		.AddMetaData("VERSION", "1.0")
		.AddMetaData("Description", "Core Register")
		.AddMetaData("About", "Store Type Related Stuff")
		.RemoveMetaData("VERSION")
		.AddMetaData("VERSION", "It was 2.0...")
		.ChangeMetaData("VERSION", "Or maybe 3.0");
		

	MetaMngr.RegisterObject<TestClass>()
		.AddMetaData("#VERSION", "1.0")
		.AddMetaData("Type", "DEBUG");

	TestClass::RemoveMetaData("Type"); // UTILS METHODS IN CLASS DEFINITION

	bool res = MetaMngr.GetCountMetaObjects() == 5;
	_ASSERT_EXPR(res, "Meta Manager Register Not Working Properly!");

	std::getchar();
}
