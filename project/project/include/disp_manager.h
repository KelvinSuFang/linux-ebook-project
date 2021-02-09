#ifndef _DISP_MANAGER_H
#define _DISP_MANAGER_H


// 显示对象结构体. 面向对象编程的思想
typedef struct DispOpr {
	char *name;	//显示设备名.
	int iXres;
	int iYres;
	int iBpp;
	// 函数指针处理
	int (*DeviceInit)(void);
	int (*ShowPixel)(int iPenX, int iPenY, unsigned int dwColor);
	int (*CleanScreen)(unsigned int dwBackColor);
	// 链表结构, 可以包含多种显示设备
	struct DispOpr *ptNext;
}T_DispOpr, *PT_DispOpr;


int RegisterDispOpr(PT_DispOpr ptDispOpr);
void ShowDispOpr(void);
int DisplayInit(void);
int FBInit(void);

#endif /* _DISP_MANAGER_H */

