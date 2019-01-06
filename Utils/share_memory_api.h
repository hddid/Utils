

#ifndef CN_VICKY_SHAREMEMAPI_H
#define	CN_VICKY_SHAREMEMAPI_H

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/sem.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <iostream>

typedef int     SMHandle;
typedef key_t   SM_KEY;
typedef size_t  SM_SIZE;
typedef ushort  SMUID_t;

#define INVALID_SM_HANDLE -1

union semun
{
	int val;
	struct semid_ds *buf;
	unsigned short *arry;
};

enum RET_ERROR_CODE
{
	RET_ERROR_FAIL = -1,
	RET_ERROR_OK = 1,
};

namespace ShareMemApi
{

	/*
	*  创建ShareMem 内存区
	*  得到一个共享内存标识符或创建一个共享内存对象并返回共享内存标识符
	*	key   创建ShareMem 的关键值
	*  Size  创建大小
	*	返回 对应ShareMem保持值
	*/
	SMHandle CreateShareMem(SM_KEY key, SM_SIZE size);

	/*
	* 打开ShareMem 内存区
	* key   打开ShareMem 的关键值
	* Size  打开大小
	* 返回  对应ShareMem 保持值
	*/
	SMHandle OpenShareMem(SM_KEY key, SM_SIZE size);

	/*
	*  映射ShareMem 内存区
	*  把共享内存区对象映射到调用进程的地址空间，连接共享内存标识符为shmid的共享内存，连接
	*  成功后把共享内存区对象映射到调用进程的地址空间，随后可像本地空间一样访问
	*	handle 映射ShareMem 的保持值
	*  返回 ShareMem 的数据指针
	*/
	void* MapShareMem(SMHandle handle);

	/*
	*  关闭映射   ShareMem 内存区
	*  与shmat函数相反，是用来断开与共享内存附加点的地址，禁止本进程访问此片共享内存
	*	MemoryPtr ShareMem 的数据指针
	*  返回 0成功 -1失败
	*/
	int UnMapShareMem(const void* MemoryPtr);

	/*
	*  关闭ShareMem
	*  完成对共享内存的控制,关闭共享内存(ipcrm -m shmid)。
	* 	handle  需要关闭的ShareMem 保持值
	*  返回 0成功 -1失败
	*/
	int CloseShareMem(SMHandle handle);

	int set_semvalue(int sem_id);

	void del_semvalue(int sem_id);

	int semaphore_p(int sem_id);

	int semaphore_p_no_wait(int sem_id);

	int semaphore_v(int sem_id);

}

#endif//CN_VICKY_SHAREMEMAPI_H
