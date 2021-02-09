
#include <config.h>
#include <fonts_manager.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H

static int FreeTypeFontInit(char *pcFontFile, unsigned int dwFontSize);
static int FreeTypeGetFontBitmap(unsigned int dwCode, PT_FontBitMap ptFontBitMap);

/* 构造, 设置, 注册一个结构体 */


// 全局的. 结构体类型和其他同类型如ASCII.GBK是一样的.面向对象的编程思想.
static T_FontOpr g_tFreeTypeFontOpr = {
	.name          = "freetype",
	.FontInit      = FreeTypeFontInit,
	.GetFontBitmap = FreeTypeGetFontBitmap,
};

static FT_Library g_tLibrary;
static FT_Face g_tFace;
static FT_GlyphSlot g_tSlot;

static int FreeTypeFontInit(char *pcFontFile, unsigned int dwFontSize)
{
	int iError;

	/* 显示矢量字体 */
	iError = FT_Init_FreeType(&g_tLibrary );			   /* initialize library */
	/* error handling omitted */
	if (iError)
	{
		DBG_PRINTF("FT_Init_FreeType failed\n");
		return -1;
	}
	
	iError = FT_New_Face(g_tLibrary, pcFontFile, 0, &g_tFace); /* create face object */
	/* error handling omitted */
	if (iError)
	{
		DBG_PRINTF("FT_Init_FreeType failed\n");		
		return -1;
	}
	
	g_tSlot = g_tFace->glyph;

	iError = FT_Set_Pixel_Sizes(g_tFace, dwFontSize, 0);
	if (iError)
	{
		DBG_PRINTF("FT_Set_Pixel_Sizes failed : %d\n", dwFontSize);
		return -1;
	}
	
	
	return 0;
}

// 获取点阵字体(freetype矢量字体)的位图
static int FreeTypeGetFontBitmap(unsigned int dwCode, PT_FontBitMap ptFontBitMap)
{
	int iError;
	int iPenX = ptFontBitMap->iCurOriginX;  // 转换后,LCD的x坐标
	int iPenY = ptFontBitMap->iCurOriginY;	// 转换后,LCD的y坐标
#if 0
	FT_Vector tPen;

	tPen.x = 0;
	tPen.y = 0;
	
	/* set transformation */
	FT_Set_Transform(g_tFace, 0, &tPen);
#endif

	/* load glyph image into the slot (erase previous one) */
	//iError = FT_Load_Char(g_tFace, dwCode, FT_LOAD_RENDER );
	iError = FT_Load_Char(g_tFace, dwCode, FT_LOAD_RENDER | FT_LOAD_MONOCHROME);
	if (iError)
	{
		DBG_PRINTF("FT_Load_Char error for code : 0x%x\n", dwCode);
		return -1;
	}

	//DBG_PRINTF("iPenX = %d, iPenY = %d, bitmap_left = %d, bitmap_top = %d, width = %d, rows = %d\n", iPenX, iPenY, g_tSlot->bitmap_left, g_tSlot->bitmap_top, g_tSlot->bitmap.width, g_tSlot->bitmap.rows);
	ptFontBitMap->iXLeft    = iPenX + g_tSlot->bitmap_left; // 加上位图的left边界
	ptFontBitMap->iYTop     = iPenY - g_tSlot->bitmap_top;	// 减去位图的top边界
	ptFontBitMap->iXMax     = ptFontBitMap->iXLeft + g_tSlot->bitmap.width;
	ptFontBitMap->iYMax     = ptFontBitMap->iYTop  + g_tSlot->bitmap.rows;
	ptFontBitMap->iBpp      = 1;
	ptFontBitMap->iPitch    = g_tSlot->bitmap.pitch;
	ptFontBitMap->pucBuffer = g_tSlot->bitmap.buffer;
	
	ptFontBitMap->iNextOriginX = iPenX + g_tSlot->advance.x / 64; // 单位是64像素.
	ptFontBitMap->iNextOriginY = iPenY;

	//DBG_PRINTF("iXLeft = %d, iYTop = %d, iXMax = %d, iYMax = %d, iNextOriginX = %d, iNextOriginY = %d\n", ptFontBitMap->iXLeft, ptFontBitMap->iYTop, ptFontBitMap->iXMax, ptFontBitMap->iYMax, ptFontBitMap->iNextOriginX, ptFontBitMap->iNextOriginY);

	return 0;
}


// 这个函数类似于注册---供上层调用, 本文件其他函数是static的.
// freetype初始化
int FreeTypeInit(void)
{
	// 通用的注册字体的操作函数,在manager.c中
	return RegisterFontOpr(&g_tFreeTypeFontOpr);
}

