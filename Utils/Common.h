/***********************************
 *
 * file Common.h
 * ingroup GroupName
 * TODO: long description
 * author Haoyu_Zeng
 * version 1.0
 * date  2018/08/31 16:25
 * E-mail: 1150566379@qq.com
 *
 ***********************************/
#ifndef ZHY_UTILS_COMMON_H
#define ZHY_UTILS_COMMON_H

#include <string> /// C++ std library
#include <cv.h>

#if (defined WIN32 || defined _WIN32) && defined UTILS_EXPORTS
#	define UTILS_API_EXPORTS __declspec(dllexport) 
#else 
#	define UTILS_API_EXPORTS 
#endif 

#ifndef UTILS_EXTERN_C 
#	ifdef __cplusplus 
#		define UTILS_EXTERN_C extern "C" 
#	else 
#		define UTILS_EXTERN_C 
#	endif 
#endif 

#if defined WIN32 || defined _WIN32 
#	define UTILS_CDECL	__cdecl 
#else 
#	define UTILS_CDECL 
#endif 

#ifndef UTILS_API 
# define UTILS_API(rettype) UTILS_EXTERN_C UTILS_API_EXPORTS rettype UTILS_CDECL 
#endif 

#ifndef UTILS_IMPL 
# define UTILS_IMPL UTILS_EXTERN_C 
#endif 


//---------------------------------------------------------------------------
// Base Macros
//---------------------------------------------------------------------------
#define OST_DISABLE_COPY(Class)			\
	Class (const Class&);				\
	Class &operator=(const Class&);


#define OST_ABS(a)					( (a) < 0   ? (-(a)) : (a) )
#define OST_SUB_ABS(a, b)			( (a) > (b) ? ((a) - (b)) : ((b) - (a)) )
#define OST_MIN(a, b)				( (a) < (b) ? (a) : (b) )
#define OST_MAX(a, b)				( (a) > (b) ? (a) : (b) )
#define OST_SWAP(a, b, t)			( (t) = (a); (a) = (b); (b) = (t); )

//[x,y]
#define HY_RANDOM(x,y)              ( rand() % (y - x +1) + (x))

#define HY_ABS(a)					( (a) < 0   ? (-(a)) : (a) )


#define OST_SAFE_DELETE(x)			{ if(x) delete x; x = 0; }
#define OST_SAFE_DELETE_ARRAY(x)	{ if(x) delete[] x; x = 0; }


/** Converts n into a pre-processor string.  */
#define OST_STRINGIFY_HELPER(n)		#n
#define OST_STRINGIFY(n)			OST_STRINGIFY_HELPER(n)
#define OST_CONNECTION(a, b)		(a##b)


#define OST_GETLENGTH_ARRAY(a)			sizeof(a) / sizeof(a[0])
#define OST_STRCPY_ARRAY_SIZE(a, b, l)	{ if(a && b) strncpy(a, b, l); }
#define OST_STRCPY_ARRAY(a, b)			{													\
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
#define OST_PI						3.141592653589793f
#define OST_RGB2GRAY(r, g, b)		( ((b) * 117 + (g) * 601 + (r) * 306) >> 10 )


//---------------------------------------------------------------------------
// date and time at compile time
//---------------------------------------------------------------------------
#define OST_TIMESTAMP				__DATE__ " " __TIME__


enum RET_ERROR_CODE
{
	RET_ERROR_FAIL = -1,
	RET_ERROR_OK,
	RET_ERROR_IMAGE,
};

#endif // ZHY_UTILS_COMMON_H

