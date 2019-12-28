#include "font.h"
#include "list.h"
#include <stdio.h>
#include <linux/input.h>
#include <linux/fb.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <dirent.h>
#include <string.h>

//int arrlen1 = 0;
//int arrlen2 = 0;
struct LcdDevice* lcd;

int main(int argc, char const *argv[])
{
	int fd, i = 0, n;
	fd = open("user.txt", O_RDWR | O_CREAT, S_IRWXU); //打开用户文件，用于读写账号和密码
	//ts_open("/dev/input/event0"); //打开触摸板文件，用于滑动函数的使用
	//lcd_draw_jpg(0, 0, "denglu.jpg", NULL, 0 , 0); //显示登陆界面

	//初始化Lcd
	lcd = init_lcd("/dev/fb0");
	//打开字体	
	font *f = fontLoad("/usr/share/fonts/DroidSansFallback.ttf");
	//字体大小的设置
	fontSetSize(f,32);
	//创建画板（点阵图）
	bitmap *bm = createBitmapWithInit(200,32,4,getColor(0,255,255,255)); //也可使用createBitmapWithInit函数，改变画板颜色
	bitmap *bm1 = createBitmapWithInit(200,32,4,getColor(0,255,255,255));
	bitmap *bm2 = createBitmapWithInit(200,32,4,getColor(0,255,255,255));
	bitmap *bm3 = createBitmapWithInit(200,32,4,getColor(0,255,255,255));

	/*进入登陆界面，如果要注册点击注册按键进入注册界面。输入完账号密码按确定键退出循环*/
	while(1)
	{
		i = denglu(lcd, f, bm, bm1, fd);
		if( i < 0)
			break;
		zhuce(lcd, f, bm2, bm3, fd);
	}
	list head = init_list();
	dirSearch(argv[1], head);//打开指定目录流，从中读取jpg图片，并将数据放到双向循环链表中
	
	show_elephoto(head);//电子相册功能 可以滑动
	

	fontUnload(f);
	destroyBitmap(bm);
	//ts_close();


	return 0;
}
