#pragma once

/** DLL exporter/importer */
#ifdef ZE_PLATFORM_WINDOWS
	#ifdef ZE_BUILD_DLL
		#define ZE_API __declspec(dllexport)
	#else	
		#define ZE_API __declspec(dllimport)
	#endif
#else
	#error ZixuanEngine only supports Windows
#endif

/** 
 * Helper for getting bits for flags/masks 
 * @param value		How many bits to shift to the left
 */
#define BIT(value) (1 << value)

/**
 * Assert with error message logging 
 * @param succeeded		A boolean expression to assert true
 * @param ...			Error messages if the succeeded went false
 */
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

/** 
 * Delete a pointer no matter what 
 * @param ptr		The pointer to be deleted
 */
#define ZE_DELETE(ptr)\
	delete ptr;\
	ptr = nullptr;

 /**
  * Delete a pointer if it's valid
  * @param ptr		The pointer to be deleted
  */
#define ZE_SAFE_DELETE(ptr) \
	if (ptr)\
	{\
		ZE_DELETE(ptr);\
	}

/**
 * Binds a member function to an event
 * @param func		The func with class's scope. For example, Application::OnEvent
 */
#define BIND_EVENT_FUNCTION(func)\
	std::bind(&func, this, std::placeholders::_1)