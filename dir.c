#include "list.h"
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

struct Picture picture[20];

int dirSearch(char *pathname, list head)
{
	int count = 0;
	DIR *dir = opendir(pathname);
	if(dir == NULL){
		perror("open dir failed:");
		return -1;
	}
	struct dirent *dirp = NULL;
	//读目录项，当把目录里面的内容全部读完之后，就返回NULL，while就退出了
	while( dirp = readdir(dir) ){
		if( strcmp(dirp->d_name,".") == 0 || strcmp(dirp->d_name,"..") == 0   )
			continue;
		
		char filename[512];
		bzero(filename,512);
		sprintf(filename,"%s/%s",pathname, dirp->d_name);
		struct stat st;
		stat(filename,&st);
		if( S_ISREG(st.st_mode) ){
			//搜索jpeg图片存放到picture数组中，再将数组中的数据放到双向链表中
			if( strcmp( filename + strlen(filename) -4 , ".jpg" )==0 || strcmp( filename + strlen(filename) -4 , ".jpeg" )==0){
				picture[count].type = 1;
				strcpy(picture[count].name, dirp->d_name);
				list new = newNode(picture[count].type, picture[count].name);
				list_add_tail(new, head);
				count++;
			}			
		}else if( S_ISDIR(st.st_mode) ){
			dirSearch(filename, head);
		}
			
	}

	closedir(dir);
	return 0;
}