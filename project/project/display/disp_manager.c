
#include <config.h>
#include <disp_manager.h>
#include <string.h>

//显示设备的链表头,用链表来表示,表明可以同时支持好几种,是模块化,对象编程思想.
static PT_DispOpr g_ptDispOprHead;

int RegisterDispOpr(PT_DispOpr ptDispOpr)
{
	PT_DispOpr ptTmp;

	// 首先头没有指向,是NULL的
	if (!g_ptDispOprHead)
	{
		// 头--指向第一个链表元素
		g_ptDispOprHead   = ptDispOpr;
		// 将下一级先置NULL
		ptDispOpr->ptNext = NULL;
	}
	else
	{
		ptTmp = g_ptDispOprHead;
		while (ptTmp->ptNext)
		{
			ptTmp = ptTmp->ptNext;
		}
		ptTmp->ptNext	  = ptDispOpr;
		ptDispOpr->ptNext = NULL;
	}

	return 0;
}


void ShowDispOpr(void)
{
	int i = 0;
	PT_DispOpr ptTmp = g_ptDispOprHead;

	while (ptTmp)  // 查找链表.
	{
		printf("%02d %s\n", i++, ptTmp->name);
		ptTmp = ptTmp->ptNext;
	}
}

// 通过名字,在链表中查找到相应的显示设备.
PT_DispOpr GetDispOpr(char *pcName)
{
	PT_DispOpr ptTmp = g_ptDispOprHead;
	
	while (ptTmp)
	{
		if (strcmp(ptTmp->name, pcName) == 0)
		{
			return ptTmp;
		}
		ptTmp = ptTmp->ptNext;
	}
	return NULL;
}


// 显示初始化
int DisplayInit(void)
{
	int iError;
	
	iError = FBInit();

	return iError;
}

