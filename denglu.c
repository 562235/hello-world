#include "font.h"
#include "list.h"
#include <stdio.h>
#include <linux/input.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>


//登陆函数 可以输入账号密码 如果正确进入电子相册
int denglu(struct LcdDevice* lcd, font *f, bitmap *bm1, bitmap *bm2,int fd)
{
	//extern int arrlen1;
	//extern int arrlen2;
	lcd_draw_jpg(0, 0, "denglu.jpg", NULL, 0 , 0);
	int key, key1;
	int ret = 0;
	int ret1 = 0;
	char use[12] = "";
	char usecon[12] = "";
	char password[12] = "";
	char passcon[12] = "";
	while(1)
	{
		/*第一个while循环用于输入账号*/
		while(1)
		{
			key = touchScreen();
			if(key == -1)//等于-1 执行确认功能 开始输入密码
				break;
			if(key == -2)//如果等于-2 执行删除功能 
			{
				bm1 = createBitmapWithInit(200,32,4,getColor(0,255,255,255));//刷新输入框
				ret --;			//use数组将指向最后一个数
				use[ret] = use[ret+1];//将最后一个数用空格覆盖
				goto del;//不执行写入数据功能 直接显示输入框
			}
			if(key == -3)
			{	
				return 1;
			}
			ret += sprintf(use+ret, "%d", key);
		del:
			fontPrint(f,bm1,0,0,use,getColor(0,255,0,0),0);
			show_font_to_lcd(lcd->mp,200,200,bm1);
		}
		/*第二个while循环用于输入密码*/
		while(1)
		{
			key1 = touchScreen();
			if(key1 == -1)
				break;
			if(key1 == -2)
			{
				bm2 = createBitmapWithInit(200,32,4,getColor(0,255,255,255));
				ret1 --;
				password[ret1] = password[ret1+1];
				goto dele;
			}
			
			ret1 += sprintf(password+ret1, "%d", key1);
		dele:
			fontPrint(f,bm2,0,0,password,getColor(0,255,0,0),0);
			show_font_to_lcd(lcd->mp,200,250,bm2);
		}
		/*将fd文件定位到开头 ，然后读取账号密码，与我们刚输入的比较*/
		lseek(fd, 0, SEEK_SET);
		read(fd, usecon, strlen(use));
		read(fd, passcon, strlen(password));
		if(strcmp(usecon, use) == 0 && strcmp(password, passcon) == 0)
		{
			return -1;
		}
		else
		{
			printf("%s\n", "Enter again");
			continue;
		}
	}
			
}