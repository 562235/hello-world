#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>


#define one x>4 && x < 75 && y > 415 && y < 472
#define two x>84 && x < 155 && y > 415 && y < 472
#define three x>164 && x < 235 && y > 415 && y < 472
#define four x>243 && x < 316 && y > 415 && y < 472
#define five x>323 && x < 396 && y > 415 && y < 472
#define six x>405 && x < 476 && y > 415 && y < 472
#define seven x>484 && x < 557 && y > 415 && y < 472
#define eight x>565 && x < 638 && y > 415 && y < 472
#define nine x>644 && x < 719 && y > 415 && y < 472
#define zero x>724 && x < 799 && y > 415 && y < 472
#define yes x>574 && x < 635 && y > 334 && y < 394
#define delete x>658 && x < 726 && y > 334 && y < 394
#define zhuce x>92 && x < 192 && y > 322 && y < 362

/*用于滑动函数的变量*/
int ts_fd;

//滑动的距离必须大于150个像素
//返回值： 0 左滑   1 右滑   2 下滑   -1 不满足任何滑动条件
int ts_slide()
{
	//read函数第一次返回的x和第一次返回的y就是begin_x和begin_y
	int begin_x, begin_y;
	int end_x, end_y;

	int flag_x = 0;//0代表还未还未进行第一次读取 1代表已经进行了第一次读取
	int flag_y = 0;


	struct input_event ev;
	ts_fd = open("/dev/input/event0", O_RDONLY);
	if(ts_fd == -1)
	{
		printf("open ts failed\n");
	}
	while(1)
	{
		read(ts_fd, &ev, sizeof(ev));//在读取触摸屏文件的时候是阻塞的
		if(ev.type == EV_ABS && ev.code == ABS_X)
		{
			if(flag_x == 0)
			{
				begin_x = ev.value;
				flag_x = 1;
			}

			end_x = ev.value;
		}

		if(ev.type == EV_ABS && ev.code == ABS_Y)
		{
			if(flag_y == 0)
			{
				begin_y = ev.value;
				flag_y = 1;
			}

			end_y = ev.value;
		}

		if(ev.type == EV_KEY && ev.code == BTN_TOUCH && ev.value == 0)//手指抬起
		{
			break;
		}
	}


	if(begin_x - end_x >= 150)//左滑
	{
		return 0;
	}

	if(end_x - begin_x >= 150)//右滑
	{
		return 1;
	}

	if(end_y - begin_y >= 150)//下滑
	{
		return 2;
	}

	close(ts_fd);
	return -1;

}

int touchScreen()
{
	struct input_event ts;
	int x,y;
	int fs = open("/dev/input/event0", O_RDONLY);
	if(fs == -1)
	{
		printf("open ts failed\n");
	}
	while(1){
		read(fs,&ts,sizeof(ts));
	
		if(ts.type == EV_ABS  && ts.code == ABS_X){
			x=ts.value;
		}
		
		if(ts.type == EV_ABS  && ts.code == ABS_Y){
			y=ts.value;
		}
		
		if( ts.type == EV_KEY && ts.code == BTN_TOUCH && ts.value == 0 ){
			/*手指离开触摸屏时刻 x，y的数值*/
			if(one)
			{
				printf("%d\n", 1);
				return 1;
			}
			if(two)
			{
				printf("%d\n", 2);
				return 2;
			}
			if(three)
			{
				printf("%d\n", 3);
				return 3;
			}
			if(four)
			{
				printf("%d\n", 4);
				return 4;
			}
			if(five)
			{
				printf("%d\n", 5);
				return 5;
			}
			if(six)
			{
				printf("%d\n", 6);
				return 6;
			}
			if(seven)
			{
				printf("%d\n", 7);
				return 7;
			}
			if(eight)
			{
				printf("%d\n", 8);
				return 8;
			}
			if(nine)
			{
				printf("%d\n", 9);
				return 9;
			}
			if(zero)
			{
				printf("%d\n", 0);
				return 0;
			}
			if(yes)
			{
				printf("%s\n", "yes");
				return -1;
			}
			if(delete)
			{
				printf("%s\n", "delete");
				return -2;
			}
			if(zhuce)
			{
				printf("%s\n", "zhuce");
				return -3;
			}

		}
	}
	close(fs);
}

