#ifndef ZHY_UTILS_HYLOGCONFIG_H
#define ZHY_UTILS_HYLOGCONFIG_H
#if (defined WIN32 || defined _WIN32) && defined AKLOG_EXPORTS
#	define AKLOG_API_EXPORTS __declspec(dllexport)
#else
#	define AKLOG_API_EXPORTS
#endif

#ifndef AKLOG_EXTERN_C
#	ifdef __cplusplus
#		define AKLOG_EXTERN_C extern "C"
#	else
#		define AKLOG_EXTERN_C
#	endif
#endif

#if defined WIN32 || defined _WIN32
#	define AKLOG_CDECL	__cdecl
#else
#	define AKLOG_CDECL
#endif


#define AKLOG_VERSION_MAJOR 
#define AKLOG_VERSION_MINOR 
#define AKLOG_VERSION_REVISION 
#define AKLOG_VERSION_BUILD 

#endif ZHY_UTILS_HYLOGCONFIG_H