#pragma once

#ifdef ZE_PLATFORM_WINDOWS
	#ifdef ZE_BUILD_DLL
		#define ZE_API __declspec(dllexport)
	#else	
		#define ZE_API __declspec(dllimport)
	#endif
#else
	#error ZixuanEngine only supports Windows
#endif

#define BIT(value) (1 << value)