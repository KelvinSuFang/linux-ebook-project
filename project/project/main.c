#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <config.h>
#include <draw.h>
#include <encoding_manager.h>
#include <fonts_manager.h>
#include <disp_manager.h>
#include <string.h>


/* ./show_file [-s Size] [-f freetype_font_file] [-h HZK] <text_file> */
int main(int argc, char **argv)
{
	int iError;
	unsigned int dwFontSize = 16;
	char acHzkFile[128];
	char acFreetypeFile[128];
	char acTextFile[128];

	char acDisplay[128];	// 显示设备名,如fb

	char cOpr;
	int bList = 0; // 输入l的时候置位

	// 初始化方式,不一定要用memset.可以将第一个字符设为'\0'.
	acHzkFile[0]  = '\0';
	acFreetypeFile[0] = '\0';
	acTextFile[0] = '\0';

	strcpy(acDisplay, "fb");	// 赋值

	// 获得参数的用法
	while ((iError = getopt(argc, argv, "ls:f:h:d:")) != -1)
	{
		switch(iError)
		{
			case 'l':
			{
				  bList = 1;
				  break;
			}
			case 's':
			{
				  dwFontSize = strtoul(optarg, NULL, 0);
				  break;
			}
			case 'f':
			{
				  strncpy(acFreetypeFile, optarg, 128);
				  acFreetypeFile[127] = '\0';
				  break;
			}			
			case 'h':
			{
					strncpy(acHzkFile, optarg, 128);
					acHzkFile[127] = '\0';
					break;
			}
			case 'd':
			{
				strncpy(acDisplay, optarg, 128);
				acDisplay[127] = '\0';
				break;
			}
			default:
			{
					printf("Usage: %s [-s Size] [-d display] [-f font_file] [-h HZK] <text_file>\n", argv[0]);
					printf("Usage: %s -l\n", argv[0]);
					return -1;
					break;
			}
		}
	}

	if (!bList && (optind >= argc))
	{
		printf("Usage: %s [-s Size] [-d display] [-f font_file] [-h HZK] <text_file>\n", argv[0]);
		printf("Usage: %s -l\n", argv[0]);
		return -1;
	}

	// 显示初始化,在manager.c中
	iError = DisplayInit();
	if (iError)
	{
		printf("DisplayInit error!\n");
		return -1;
	}

	// 字体初始化,在manager.c中
	iError = FontsInit();
	if (iError)
	{
		printf("FontsInit error!\n");
		return -1;
	}

	// 编码初始化,在manager.c中
	iError = EncodingInit();
	if (iError)
	{
		printf("EncodingInit error!\n");
		return -1;
	}

	if (bList)  // 以下三个函数,都在manager.c中
	{
		printf("supported display:\n");
		ShowDispOpr();

		printf("supported font:\n");
		ShowFontOpr();

		printf("supported encoding:\n");
		ShowEncodingOpr();
		return 0;
	}

	strncpy(acTextFile, argv[optind], 128);
	acTextFile[127] = '\0';

	// 打开文本文件. 在draw.c中
	iError = OpenTextFile(acTextFile);
	if (iError)
	{
		printf("OpenTextFile error!\n");
		return -1;
	}

	// 设置font信息, 这个SetTextDetail函数可以改为SetFontDetail更符合逻辑
	iError = SetFontDetail(acHzkFile, acFreetypeFile, dwFontSize);
	if (iError)
	{
		printf("SetFontDetail error!\n");
		return -1;
	}

	DBG_PRINTF("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);

	// 通过这个设备名,来找到相应的显示设备.
	iError = SelectAndInitDisplay(acDisplay);
	if (iError)
	{
		printf("SelectAndInitDisplay error!\n");
		return -1;
	}
	
	DBG_PRINTF("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
	iError = ShowNextPage();
	DBG_PRINTF("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
	if (iError)
	{
		printf("Error to show first page\n");
		return -1;
	}

	while (1)
	{
		printf("Enter 'n' to show next page, 'u' to show previous page, 'q' to exit: ");

		do {
			cOpr = getchar();			
		} while ((cOpr != 'n') && (cOpr != 'u') && (cOpr != 'q'));

		if (cOpr == 'n')
		{
			ShowNextPage();
		}
		else if (cOpr == 'u')
		{
			ShowPrePage();			
		}
		else 
		{
			return 0;
		}			
	}
	return 0;
}

