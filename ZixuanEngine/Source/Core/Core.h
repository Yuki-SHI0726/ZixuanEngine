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


#ifdef ZE_ENABLE_ASSERTS
	#define ZE_ASSERT(succeeded, ...) \
		if (!(succeeded))\
		{\
			ZE_LOG(Error, __VA_ARGS__);\
		}\
		assert((succeeded));
#else
	#define ZE_ASSERT(succeeded, ...)
#endif

#define ZE_DELETE(ptr)\
	delete ptr;\
	ptr = nullptr;

#define ZE_SAFE_DELETE(ptr) \
	if (ptr)\
	{\
		ZE_DELETE(ptr);\
	}

#define BIND_EVENT_FUNCTION(func)\
	std::bind(&func, this, std::placeholders::_1)