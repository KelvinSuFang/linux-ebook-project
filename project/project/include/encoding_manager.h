
#ifndef _ENCODING_MANAGER_H
#define _ENCODING_MANAGER_H

#include <fonts_manager.h>
#include <disp_manager.h>

// 编码结构
typedef struct EncodingOpr {
	char *name;
	int iHeadLen;
	// 包含字体结构 , 支持这个文件的一些编码格式(得到点阵).
	PT_FontOpr ptFontOprSupportedHead;
	// 函数指针
	int (*isSupport)(unsigned char *pucBufHead);
	int (*GetCodeFrmBuf)(unsigned char *pucBufStart, unsigned char *pucBufEnd, unsigned int *pdwCode);
	// 单向链表结构
	struct EncodingOpr *ptNext;
}T_EncodingOpr, *PT_EncodingOpr;

int RegisterEncodingOpr(PT_EncodingOpr ptEncodingOpr);
void ShowEncodingOpr(void);
PT_DispOpr GetDispOpr(char *pcName);
PT_EncodingOpr SelectEncodingOprForFile(unsigned char *pucFileBufHead);
int AddFontOprForEncoding(PT_EncodingOpr ptEncodingOpr, PT_FontOpr ptFontOpr);
int DelFontOprFrmEncoding(PT_EncodingOpr ptEncodingOpr, PT_FontOpr ptFontOpr);
int EncodingInit(void);
int AsciiEncodingInit(void);
int  Utf16beEncodingInit(void);
int  Utf16leEncodingInit(void);
int  Utf8EncodingInit(void);

#endif /* _ENCODING_MANAGER_H */

