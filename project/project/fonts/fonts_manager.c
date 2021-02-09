#include <config.h>
#include <fonts_manager.h>
#include <string.h>

static PT_FontOpr g_ptFontOprHead = NULL;


// 通用的注册字体的操作函数,在manager.c中
int RegisterFontOpr(PT_FontOpr ptFontOpr)
{
	PT_FontOpr ptTmp;

	if (!g_ptFontOprHead)
	{
		g_ptFontOprHead   = ptFontOpr;
		ptFontOpr->ptNext = NULL;
	}
	else
	{
		ptTmp = g_ptFontOprHead;
		while (ptTmp->ptNext)
		{
			ptTmp = ptTmp->ptNext;
		}
		ptTmp->ptNext     = ptFontOpr;
		ptFontOpr->ptNext = NULL;
	}

	return 0;
}

// 显示字体支持有多少种
void ShowFontOpr(void)
{
	int i = 0;
	PT_FontOpr ptTmp = g_ptFontOprHead;

	while (ptTmp) // 查找链表.
	{
		printf("%02d %s\n", i++, ptTmp->name);
		ptTmp = ptTmp->ptNext;  // 依次一级一级的查找.
	}
}

PT_FontOpr GetFontOpr(char *pcName)
{
	PT_FontOpr ptTmp = g_ptFontOprHead;
	
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

// 字体初始化
int FontsInit(void)
{
	int iError;

	// 初始化ASCII.在ascii.c中	
	iError = ASCIIInit();
	if (iError)
	{
		DBG_PRINTF("ASCIIInit error!\n");
		return -1;
	}

	// 国标码初始化, 在gbk.c中
	iError = GBKInit();
	if (iError)
	{
		DBG_PRINTF("GBKInit error!\n");
		return -1;
	}

	// freetype初始化, 在freetype.c中
	iError = FreeTypeInit();
	if (iError)
	{
		DBG_PRINTF("FreeTypeInit error!\n");
		return -1;
	}

	return 0;
}

