#ifndef ZHY_UTILS_PLATFORM_WIN32_H
#define ZHY_UTILS_PLATFORM_WIN32_H

//---------------------------------------------------------------------------
// Prerequisites
//---------------------------------------------------------------------------
#ifndef WINVER						// Allow use of features specific to Windows XP or later
#	define WINVER			0x0501
#endif

#ifndef _WIN32_WINNT				// Allow use of features specific to Windows XP or later
#	define _WIN32_WINNT		0x0501
#endif	

#ifndef _WIN32_WINDOWS				// Allow use of features specific to Windows 98 or later
#	define _WIN32_WINDOWS	0x0410
#endif

#ifndef _WIN32_IE					// Allow use of features specific to IE 6.0 or later
#	define _WIN32_IE		0x0600
#endif

#define WIN32_LEAN_AND_MEAN			// Exclude rarely-used stuff from Windows headers


//---------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------
#include <windows.h>

#include <io.h>
#include <string>
#include <time.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <malloc.h>

//---------------------------------------------------------------------------
// Undeprecate CRT functions
//---------------------------------------------------------------------------
#ifndef _CRT_SECURE_NO_DEPRECATE 
#	define _CRT_SECURE_NO_DEPRECATE 1
#endif


//---------------------------------------------------------------------------
// Verify that we're built with the multithreaded 
// versions of the runtime libraries 
//---------------------------------------------------------------------------
#if defined(_MSC_VER) && !defined(_MT)
#	error Must compile with /MD, /MDd, /MT or /MTd
#endif


//---------------------------------------------------------------------------
// Check debug/release settings consistency 
//---------------------------------------------------------------------------
#if defined(NDEBUG) && defined(_DEBUG)
#	error Inconsistent build settings (check for /MD[d])
#endif


//---------------------------------------------------------------------------
// Call backs
//---------------------------------------------------------------------------
/** The std call type. */
#define ZHY_STDCALL			__stdcall

/** The call back calling convention. */
#define ZHY_CALLBACK_TYPE	ZHY_STDCALL

/** The C and C++ calling convension. */
#define ZHY_C_DECL			__cdecl


//---------------------------------------------------------------------------
// Indicates a deprecated function
// Before VS2005 there was no support for declspec deprecated...
//---------------------------------------------------------------------------
#if _MSC_VER < 1400
#	define ZHY_API_DEPRECATED(msg)
#else
#	define ZHY_API_DEPRECATED(msg)	__declspec(deprecated(msg))
#endif


//---------------------------------------------------------------------------
// API Export/Import Macros
//---------------------------------------------------------------------------
/** Indicates an exported and imported shared library function. */
#define ZHY_API_EXPORT		__declspec(dllexport)
#define ZHY_API_IMPORT		__declspec(dllimport)


#endif//ZHY_UTILS_PLATFORM_WIN32_H
