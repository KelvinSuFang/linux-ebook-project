#include <config.h>
#include <encoding_manager.h>
#include <string.h>
#include <stdlib.h>

static PT_EncodingOpr g_ptEncodingOprHead;

int RegisterEncodingOpr(PT_EncodingOpr ptEncodingOpr)
{
	PT_EncodingOpr ptTmp;

	if (!g_ptEncodingOprHead)
	{
		g_ptEncodingOprHead   = ptEncodingOpr;
		ptEncodingOpr->ptNext = NULL;
	}
	else
	{
		ptTmp = g_ptEncodingOprHead;
		while (ptTmp->ptNext)
		{
			ptTmp = ptTmp->ptNext;
		}
		ptTmp->ptNext	      = ptEncodingOpr;
		ptEncodingOpr->ptNext = NULL;
	}

	return 0;
}


// 链表查找, 显示编码对象...
void ShowEncodingOpr(void)
{
	int i = 0;
	PT_EncodingOpr ptTmp = g_ptEncodingOprHead;

	while (ptTmp)  //查找链表知道遇到NULL.
	{
		printf("%02d %s\n", i++, ptTmp->name);
		ptTmp = ptTmp->ptNext; // 依次一级一级的查找.
	}
}

// 为给定文件选择特定编码.  输入参数为文本的mmap后的fd
PT_EncodingOpr SelectEncodingOprForFile(unsigned char *pucFileBufHead)
{
	PT_EncodingOpr ptTmp = g_ptEncodingOprHead;

	// 对链表中的每种编码方式都进行查找,看是否支持
	while (ptTmp)
	{	
		if (ptTmp->isSupport(pucFileBufHead))
			return ptTmp;
		else
			ptTmp = ptTmp->ptNext;
	}
	return NULL;
}


int AddFontOprForEncoding(PT_EncodingOpr ptEncodingOpr, PT_FontOpr ptFontOpr)
{
	PT_FontOpr ptFontOprCpy;
	
	if (!ptEncodingOpr || !ptFontOpr)
	{
		return -1;
	}
	else
	{
		ptFontOprCpy = malloc(sizeof(T_FontOpr));
		if (!ptFontOprCpy)
		{
			return -1;
		}
		else
		{
			memcpy(ptFontOprCpy, ptFontOpr, sizeof(T_FontOpr));
			ptFontOprCpy->ptNext = ptEncodingOpr->ptFontOprSupportedHead;
			ptEncodingOpr->ptFontOprSupportedHead = ptFontOprCpy;
			return 0;
		}		
	}
}


int DelFontOprFrmEncoding(PT_EncodingOpr ptEncodingOpr, PT_FontOpr ptFontOpr)
{
	PT_FontOpr ptTmp;
	PT_FontOpr ptPre;
		
	if (!ptEncodingOpr || !ptFontOpr)
	{
		return -1;
	}
	else
	{
		ptTmp = ptEncodingOpr->ptFontOprSupportedHead;
		if (strcmp(ptTmp->name, ptFontOpr->name) == 0)
		{
			/* 删除头节点 */
			ptEncodingOpr->ptFontOprSupportedHead = ptTmp->ptNext;
			free(ptTmp);
			return 0;
		}

		ptPre = ptEncodingOpr->ptFontOprSupportedHead;
		ptTmp = ptPre->ptNext;
		while (ptTmp)
		{
			if (strcmp(ptTmp->name, ptFontOpr->name) == 0)
			{
				/* 从链表里取出、释放 */
				ptPre->ptNext = ptTmp->ptNext;
				free(ptTmp);
				return 0;
			}
			else
			{
				ptPre = ptTmp;
				ptTmp = ptTmp->ptNext;
			}
		}

		return -1;
	}
}

// 编码初始化
int EncodingInit(void)
{
	int iError;

	iError = AsciiEncodingInit();
	if (iError)
	{
		DBG_PRINTF("AsciiEncodingInit error!\n");
		return -1;
	}

	iError = Utf16leEncodingInit();
	if (iError)
	{
		DBG_PRINTF("Utf16leEncodingInit error!\n");
		return -1;
	}
	
	iError = Utf16beEncodingInit();
	if (iError)
	{
		DBG_PRINTF("Utf16beEncodingInit error!\n");
		return -1;
	}
	
	iError = Utf8EncodingInit();
	if (iError)
	{
		DBG_PRINTF("Utf8EncodingInit error!\n");
		return -1;
	}

	return 0;
}

