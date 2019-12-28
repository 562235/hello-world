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

/*注册界面，当在登陆界面点击用户注册时跳转*/
void zhuce(struct LcdDevice* lcd, font *f, bitmap *bm, bitmap *bm1, int fd)
{
	//extern int arrlen1;
	//extern int arrlen2;
	lcd_draw_jpg(0, 0, "zhuce.jpg", NULL, 0 , 0);
	int key, key1;
	int ret = 0, ret1 = 0;
	char use[12] = "";
	char password[12] = "";
	//用于输入账号 可以删除
	while(1)
	{
		key = touchScreen();
		if(key == -1)
			break;
		if(key == -2)
		{	
			bm = createBitmapWithInit(200,32,4,getColor(0,255,255,255));
			ret --;
			use[ret] = use[ret+1];
			goto del;
		}
		ret += sprintf(use+ret, "%d", key);
	del:
		fontPrint(f,bm,0,0,use,getColor(0,255,0,0),0);
		show_font_to_lcd(lcd->mp,200,200,bm);
	}
	//将账号数据存放至文件，下次进入程序可以不用注册
	//arrlen1 = strlen(use);
	write(fd, use, strlen(use));

	//用于输入密码 可以删除
	while(1)
	{
		key1 = touchScreen();
		if(key1 == -1)
			break;
		if(key1 == -2)
		{
			bm1 = createBitmapWithInit(200,32,4,getColor(0,255,255,255));
			ret1--;
			password[ret1] = password[ret1+1];
			goto dele;
		}
		ret1 += sprintf(password+ret1, "%d", key1);
	dele:
		fontPrint(f,bm1,0,0,password,getColor(0,255,0,0),0);
		show_font_to_lcd(lcd->mp,200,250,bm1);
	}
	//将密码数据存放至文件，下次进入程序可以不用注册
	//arrlen2 = strlen(password);
	write(fd,password,strlen(password));
	return;
}