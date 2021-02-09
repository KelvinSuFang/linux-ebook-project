
#ifndef _FONTS_MANAGER_H
#define _FONTS_MANAGER_H

// 全局结构体,兼容多种方式编码,如ascii, gbk, freetype.
typedef struct FontBitMap {
	int iXLeft;	//最左边的x坐标
	int iYTop;	//最上面的y坐标
	int iXMax;	//x最大值
	int iYMax;	//y最大值
	
	int iBpp;	// 表示一个像素有多大? 1bit? or 1byte?
	// 设计这个的目的,是为了让这个结构体能够兼容freetype和ascii,gbk.
	// 因为freetype的像素大小不固定,需要做很多处理.
	int iPitch;   /* 对于单色位图, 两行象素之间的跨度 */
	
	int iCurOriginX;	// 当前原点x坐标
	int iCurOriginY;	// 当前原点y坐标
	int iNextOriginX;	// 下一个原点x坐标
	int iNextOriginY;	// 下一个原点y坐标
	unsigned char *pucBuffer;	//字体数据buf指针
}T_FontBitMap, *PT_FontBitMap;

// 全局的. 结构体类型一样,包含了:freetype, ASCII.GBK.面向对象的编程思想.
typedef struct FontOpr {
	char *name;
	// 操作处理的函数指针
	int (*FontInit)(char *pcFontFile, unsigned int dwFontSize);
	int (*GetFontBitmap)(unsigned int dwCode, PT_FontBitMap ptFontBitMap);
	//链表结构
	struct FontOpr *ptNext;
}T_FontOpr, *PT_FontOpr;


int RegisterFontOpr(PT_FontOpr ptFontOpr);
void ShowFontOpr(void);
int FontsInit(void);
int ASCIIInit(void);
int GBKInit(void);
int FreeTypeInit(void);
PT_FontOpr GetFontOpr(char *pcName);

#endif /* _FONTS_MANAGER_H */

