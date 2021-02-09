
#ifndef _FONTS_MANAGER_H
#define _FONTS_MANAGER_H

// ȫ�ֽṹ��,���ݶ��ַ�ʽ����,��ascii, gbk, freetype.
typedef struct FontBitMap {
	int iXLeft;	//����ߵ�x����
	int iYTop;	//�������y����
	int iXMax;	//x���ֵ
	int iYMax;	//y���ֵ
	
	int iBpp;	// ��ʾһ�������ж��? 1bit? or 1byte?
	// ��������Ŀ��,��Ϊ��������ṹ���ܹ�����freetype��ascii,gbk.
	// ��Ϊfreetype�����ش�С���̶�,��Ҫ���ܶദ��.
	int iPitch;   /* ���ڵ�ɫλͼ, ��������֮��Ŀ�� */
	
	int iCurOriginX;	// ��ǰԭ��x����
	int iCurOriginY;	// ��ǰԭ��y����
	int iNextOriginX;	// ��һ��ԭ��x����
	int iNextOriginY;	// ��һ��ԭ��y����
	unsigned char *pucBuffer;	//��������bufָ��
}T_FontBitMap, *PT_FontBitMap;

// ȫ�ֵ�. �ṹ������һ��,������:freetype, ASCII.GBK.�������ı��˼��.
typedef struct FontOpr {
	char *name;
	// ��������ĺ���ָ��
	int (*FontInit)(char *pcFontFile, unsigned int dwFontSize);
	int (*GetFontBitmap)(unsigned int dwCode, PT_FontBitMap ptFontBitMap);
	//����ṹ
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

