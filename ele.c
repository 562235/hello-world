#include "list.h"
#include <stdio.h>
#include <linux/input.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/mman.h>

void show_elephoto(list head)//下滑 返回上一菜单
{
	list p = head->next;
	lcd_draw_jpg(0, 0, p->name, NULL, 0 , 0);

	int ret;
	while(1)
	{
		//printf("%d\n", 3);
		ret = ts_slide();
		
		if(ret == 0)//左滑
		{
		//	printf("%d\n", 123);
			p = p->next;
			if(p == head)
				p = head->next;
		}

		if(ret == 1)//右滑
		{
			//printf("%d\n", 321);
			p = p->prev;
			if(p == head)
				p = head->prev;
		}

		if(ret == 2)//下滑
		{
			break;
		}
		
		lcd_draw_jpg(0, 0, p->name, NULL, 0 , 0);

	}
}