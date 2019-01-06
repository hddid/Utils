#ifndef ZHY_UTILS_PLATFORMLINUX_ARM_H
#define ZHY_UTILS_PLATFORMLINUX_ARM_H

#ifndef WIN32
#include <unistd.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <limits.h>
#include <stdint.h>

/** The thread static declarator (using TLS). */
#define ZHY_THREAD_STATIC	__thread
/**
* __thread是GCC内置的线程局部存储设施，存取效率可以和全局变量相比。__thread变量每一个线程有一份独立实体，
* 各个线程的值互不干扰。可以用来修饰那些带有全局性且值可能变，但是又不值得用全局变量保护的变量。
* __thread使用规则：只能修饰POD类型(类似整型指针的标量，不带自定义的构造、拷贝、赋值、析构的类型，二进制
* 内容可以任意复制memset,memcpy,且内容可以复原)，不能修饰class类型，因为无法自动调用构造函数和析构函数，
* 可以用于修饰全局变量，函数内的静态变量，不能修饰函数的局部变量或者class的普通成员变量，且__thread变量值
* 只能初始化为编译器常量(值在编译器就可以确定const int i=5,运行期常量是运行初始化后不再改变const int i=rand()).
*
#include<iostream>
#include<pthread.h>
#include<unistd.h>

using namespace std;
const int i=5;
__thread int var=i;//两种方式效果一样
//__thread int var=5;//

void* worker1(void* arg);
void* worker2(void* arg);

int main()
{
pthread_t pid1,pid2;
//__thread int temp=5;
static __thread  int temp=10;//修饰函数内的static变量

pthread_create(&pid1,NULL,worker1,NULL);
pthread_create(&pid2,NULL,worker2,NULL);

pthread_join(pid1,NULL);
pthread_join(pid2,NULL);

cout<<temp<<endl;//输出10
return 0;
}

void* worker1(void* arg)
{
cout<<++var<<endl;//输出 6
}

void* worker2(void* arg)
{
sleep(1);//等待线程1改变var值，验证是否影响线程2
cout<<++var<<endl;//输出6
}
*/

//---------------------------------------------------------------------------
// Files
//---------------------------------------------------------------------------
/** The maximum allowed file path size (in bytes). */
#define ZHY_FILE_MAX_PATH	256

//---------------------------------------------------------------------------
// Call back
//---------------------------------------------------------------------------
/** The std call type. */
#define ZHY_STDCALL			__stdcall

/** The call back calling convention. */
#define ZHY_CALLBACK_TYPE 

/** The C and C++ calling convension. */
#define ZHY_C_DECL

//---------------------------------------------------------------------------
// API Export/Import Macros
//---------------------------------------------------------------------------
/** Indicates an exported shared library function. */
#define ZHY_API_EXPORT				__attribute__ ((visibility("default")))

/** Indicates an imported shared library function. */
#define ZHY_API_IMPORT 

/** Indicates a deprecated function */
#define ZHY_API_DEPRECATED(msg)		__attribute__((warning("This function is deprecated: " msg)))

#define ZHY_PLATFORM_LINUX_NO_POSIX_MEMALIGN
#endif//ZHY_UTILS_PLATFORMLINUX_ARM_H