#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "list.h"

/*
 *函数名：init_list
 *函数功能：初始化头节点
 *参数：void
 *返回值：list
 */
list init_list()
{
	list head = malloc(sizeof(node));
	if(head != NULL)
	{
		head->prev = head;
		head->next = head;
	}
	return head;
}

/*
 *函数名：newNode
 *函数功能：初始化新节点
 *参数：void
 *返回值：list
 */
list newNode(int type, char *name)
{
	list new = malloc(sizeof(node));
	if(new != NULL)
	{
		new->type = type;
		new->name = name;
		new->prev = NULL;
		new->next = NULL;
		return new;
	}

	return new;
}

/*
 *函数名：init_list
 *函数功能：将新节点链接到链表最后
 *参数：void
 *返回值：list
 */
void list_add_tail(list new,list head)
{
	new->next = head;
	new->prev = head->prev;
	
	head->prev->next = new;
	head->prev = new;
}