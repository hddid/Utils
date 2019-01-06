/***********************************
 *
 * file UVersion.h
 * ingroup GroupName
 * TODO: long description
 * author Haoyu_Zeng
 * version 1.0
 * date  2018/08/31 20:19
 * E-mail: 1150566379@qq.com
 *
 ***********************************/
#ifndef OST_CORE_OSTVERSION_H
#define OST_CORE_OSTVERSION_H

#include "Common.h"

#define OST_VERSION_MAJOR			1
#define OST_VERSION_MINOR			0
#define OST_VERSION_MAINTENANCE		0
#define OST_VERSION_BUILD			1

/** OpenST version (in brief string format): "Major.Minor.Maintenance (Build)" */ 
#define OST_BRIEF_VERSION_STRING					\
	OST_STRINGIFY(OST_VERSION_MAJOR) "."			\
	OST_STRINGIFY(OST_VERSION_MINOR) "."			\
	OST_STRINGIFY(OST_VERSION_MAINTENANCE)			\
	" (Build " OST_STRINGIFY(OST_VERSION_BUILD)  OST_TIMESTAMP ")"

/** OpenST version (in numeric format): (OpenST major version * 100000000 + OpenNI minor version * 1000000 + OpenST maintenance version * 10000 + OpenST build version). */
#define OST_VERSION (OST_VERSION_MAJOR * 100000000 + OST_VERSION_MINOR * 1000000 + OST_VERSION_MAINTENANCE * 10000 + OST_VERSION_BUILD)
#define OST_CREATE_API_VERSION(major, minor) ((major)*1000 + (minor))
#define OST_API_VERSION OST_CREATE_API_VERSION(OST_VERSION_MAJOR, OST_VERSION_MINOR)

/** OpenST version (in string format): "Major.Minor.Maintenance.Build-Platform (MMM DD YYYY HH:MM:SS)". */ 
//#define OST_VERSION_STRING						\
//	OST_BRIEF_VERSION_STRING  "-"				\
//	OST_PLATFORM_STRING " (" OST_TIMESTAMP ")"

typedef struct _OSTVersion
{
	/** Major version number */
	int major;
	/** Minor version number */
	int minor;
	/** Maintenance build number */
	int maintenance;
	/** Build number */
	int build;
}OSTVersion;

#endif//OST_CORE_OSTVERSION_H