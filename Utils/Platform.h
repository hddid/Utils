#ifndef ZHY_UTILS_PLATFORM_H
#define ZHY_UTILS_PLATFORM_H

//---------------------------------------------------------------------------
// Platform Defines
//---------------------------------------------------------------------------
enum
{
	ZHY_PLATFORM_WIN32 = 1,
	ZHY_PLATFORM_LINUX_X86 = 2,
	ZHY_PLATFORM_LINUX_ARM = 3,
	ZHY_PLATFORM_ANDROID = 4,
	ZHY_PLATFORM_MACOSX = 5,
};

#if (defined _WIN32)
#	ifndef RC_INVOKED
#		if _MSC_VER < 1400
#			error OpenST Platform Abstraction Layer - Win32 - Microsoft Visual Studio version below 2005 are not supported!
#		endif
#	endif
#	include "PlatformWin32.h"
#	define ZHY_PLAFORM           ZHY_PLATFORM_WIN32
#	define ZHY_PLATFORM_STRING   "win32"
#elif (__linux__ && (i386 || __x86_64__))
#	include "ZHYPlatformLinux-x86.h"
#	define ZHY_PLAFORM           ZHY_PLATFORM_LINUX_X86
#	define ZHY_PLATFORM_STRING   "linux-x86"
#elif (__linux__ && __arm__)
#	include "ZHYPlatformLinux-Arm.h"
#	define ZHY_PLAFORM           ZHY_PLATFORM_LINUX_ARM
#	define ZHY_PLATFORM_STRING   "linux-arm"
#elif defined (ANDROID)
#	include "ZHYPlatformAndroid.h"
#	define ZHY_PLAFORM           ZHY_PLATFORM_ANDROID
#	define ZHY_PLATFORM_STRING   "android"
#elif (__APPLE__)
#	include "ZHYPlatformMacOSX.h"
#	define ZHY_PLAFORM           ZHY_PLATFORM_MACOSX
#	define ZHY_PLATFORM_STRING   "macosx"
#else
#	error OpenST Platform Abstraction Layer - Unsupported Platform!
#endif

//---------------------------------------------------------------------------
// API Export/Import Macros
//---------------------------------------------------------------------------
#ifdef __cplusplus
#	define ZHY_C extern "C"
#	define ZHY_C_API_EXPORT  ZHY_C  ZHY_API_EXPORT
#	define ZHY_C_API_IMPORT  ZHY_C  ZHY_API_IMPORT
#	define ZHY_CPP_API_EXPORT       ZHY_API_EXPORT
#	define ZHY_CPP_API_IMPORT       ZHY_API_IMPORT
#else // __cplusplus
#	define ZHY_C_API_EXPORT         ZHY_API_EXPORT
#	define ZHY_C_API_IMPORT         ZHY_API_IMPORT
#endif  // __cplusplus


#ifdef OPENST_EXPORT
#	define ZHY_C_API    ZHY_C_API_EXPORT
#	define ZHY_CPP_API  ZHY_CPP_API_EXPORT
#else // OPENNI2_EXPORT
#	define ZHY_C_API    ZHY_C_API_IMPORT
#	define ZHY_CPP_API  ZHY_CPP_API_IMPORT
#endif//OPENST_EXPORT

//---------------------------------------------------------------------------
// Base Macros
//---------------------------------------------------------------------------
#define ZHY_DISABLE_COPY(Class)			\
	Class (const Class&);				\
	Class &operator=(const Class&);


#define ZHY_ABS(a)					( (a) < 0   ? (-(a)) : (a) )
#define ZHY_SUB_ABS(a, b)			( (a) > (b) ? ((a) - (b)) : ((b) - (a)) )
#define ZHY_MIN(a, b)				( (a) < (b) ? (a) : (b) )
#define ZHY_MAX(a, b)				( (a) > (b) ? (a) : (b) )
#define ZHY_SWAP(a, b, t)			( (t) = (a); (a) = (b); (b) = (t); )


#define ZHY_SAFE_DELETE(x)			{ if(x) delete x; x = 0; }
#define ZHY_SAFE_DELETE_ARRAY(x)	{ if(x) delete[] x; x = 0; }


/** Converts n into a pre-processor string.  */
#define ZHY_STRINGIFY_HELPER(n)		#n
#define ZHY_STRINGIFY(n)			ZHY_STRINGIFY_HELPER(n)
#define ZHY_CONNECTION(a, b)		(a##b)


#define ZHY_GETLENGTH_ARRAY(a)			sizeof(a) / sizeof(a[0])
#define ZHY_STRCPY_ARRAY_SIZE(a, b, l)	{ if(a && b) strncpy(a, b, l); }
#define ZHY_STRCPY_ARRAY(a, b)			{													\
											if(a && b)										\
											{												\
												size_t len1 = strlen(a);					\
												size_t len2 = strlen(b);					\
												strncpy(a, b, len1 < len2 ? len1 : len2);	\
											}												\
										}


//---------------------------------------------------------------------------
// Digital Image Macros
//---------------------------------------------------------------------------
#define ZHY_PI						3.141592653589793f
#define ZHY_RGB2GRAY(r, g, b)		( ((b) * 117 + (g) * 601 + (r) * 306) >> 10 )


//---------------------------------------------------------------------------
// date and time at compile time
//---------------------------------------------------------------------------
#define ZHY_TIMESTAMP				__DATE__ " " __TIME__


//---------------------------------------------------------------------------
// The default memory alignment
//---------------------------------------------------------------------------
#define ZHY_DEFAULT_MEM_ALIGN		16


#endif//ZHY_UTILS_PLATFORM_H
