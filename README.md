# MetaObject
Easy to use Meta Data class to store class related informations!

## Installation
To add MetaObject to your C++ project clone this repository or download the single header file 
and import it into your project.

## Usage and Examples
After importing the repo you can use meta object by including it's header:
    
```c++
#include "path/MetaManager.h"
```

In MetaObject you can Register a type and add/modify/get/remoe a string pair as meta data (key, value).
Example:

```c++
// MetaMngr it's a shortcut for MetaManager::GetManager()
MetaMngr.RegisterObject<int>() // Register type
  .AddMetaData("TYPE", "NUMBER") // Keep adding stuff
  .AddMetaData("VERSION", "Common");

// Adding a custom class
MetaMngr.RegisterObject<MetaManager>()
  .AddMetaData("VERSION", "1.0")
  .AddMetaData("Description", "Core Register")
  .AddMetaData("About", "Store Type Related Stuff")
  .RemoveMetaData("VERSION")
  .AddMetaData("VERSION", "It was 2.0...")
  .ChangeMetaData("VERSION", "Or maybe 3.0");
```

Once registered and filled our meta data on startup we might want to change stuff in the future, if we have an accessible class definition we can use  **UTILITY_META_OBJECT_METHODS(type)**, it's a macro that provide the class some static methods to manipulate it's metadata without calling the manager instance.

Example:

```c++
#include "../src/MetaManager.h"

class TestClass
{
public:
	UTILITY_META_OBJECT_METHODS(TestClass) // <- Adds meta data static methods
};

// main.cpp
MetaMngr.RegisterObject<TestClass>()
  .AddMetaData("#VERSION", "1.0")
  .AddMetaData("Type", "DEBUG");

TestClass::RemoveMetaData("Type"); // UTILS METHODS IN CLASS DEFINITION
```

Note: In case of using UTILITY macro make sure you register the type before using it's static methods since it relies on MetaManager!

## Credits
MetaObject was created by [Ivan Lo Greco].
