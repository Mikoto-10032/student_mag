#include <stdio.h>
#include <stdlib.h>
#include <getch.h>
#include <string.h>
#include "admin.h"
#include "teacher.h"
#include "tools.h"
#include "struct.h"

int tch_in_cnt=0;
int tch_out_cnt=0;
int tch_id = 1000;

char admin_pwd[30] = "admin";

//添加老师
void add_tch(void)
{
	debug("%s\n",__func__);
	for(;;)
	{
		if(tch_in_cnt >= TEACHER_MAX)
		{
			show_msg("系统升级中！\n",3);
		}
		printf("请输入教师姓名、性别:");
		scanf("%s %c",tch_in[tch_in_cnt].name,&tch_in[tch_in_cnt].sex);
		tch_in[tch_in_cnt].id = ++tch_id;
		tch_in[tch_in_cnt].lock = 0; 
		strcpy(tch_in[tch_in_cnt].pwd,"123456");
		tch_in_cnt++;
		show_msg("添加成功(1、继续添加\t0、返回主界面)\n输入指令：",0.5);
		stdin -> _IO_read_ptr = stdin -> _IO_read_end;
		char cmd;
		scanf("%c",&cmd);
		if(cmd=='0') break;
	}
}
//删除老师
void del_tch(void)
{
	debug("%s\n",__func__);
	int id_1,id_2;
	for(;;)
	{
		system("clear");
		printf("请输入要删除的教师工号:");
		scanf("%d",&id_1);
		printf("请再次确认教师工号:");
		scanf("%d",&id_2);
		if(id_1 == id_2) 
		{	
			break;
		}
		else 
		{
			printf("输入的工号不一致，删除失败！\n");
			anykey_continue();
			return;
		}
	}
	for(int i = 0;i < tch_in_cnt;i++)
	{
		if(tch_in[i].sex && (tch_in[i].id == id_1))
		{
			strcpy(tch_out[tch_out_cnt].name,tch_in[i].name);
			tch_out[tch_out_cnt].sex = tch_in[i].sex;
			for(int j = i;j < tch_in_cnt-1;j++)
			{
				//把要删除的老师名字和密码清空
				memset(tch_in[j].name,0,sizeof(char)*20);
				memset(tch_in[j].pwd,0,sizeof(char)*20);
				//将后一位老师信息赋给上一位
				strcpy(tch_in[j].name,tch_in[j+1].name);
				tch_in[j].sex = tch_in[j+1].sex;
				tch_in[j].id = tch_in[j+1].id;
				strcpy(tch_in[j].pwd,tch_in[j+1].pwd);
				tch_in[j].lock = tch_in[j+1].lock;
			}
			//再将最后一人的姓名、密码、性别置空
			memset(tch_in[tch_in_cnt-1].name,0,sizeof(char)*20);
			memset(tch_in[tch_in_cnt-1].pwd,0,sizeof(char)*20);
			tch_in[tch_in_cnt-1].sex = 0;
			tch_in_cnt--;
			tch_out_cnt++;
			show_msg("删除教师成功\n",0.5);
			anykey_continue();
			return;
		}
	}
	show_msg("您要删除的教师不存在！",0.5);
	anykey_continue();
}
//显示在校老师
void show_school_tch(void)
{
	debug("%s\n",__func__);
	for(int i=0;i<tch_in_cnt;i++)
	{
		printf("%s %s %d\n",tch_in[i].name,tch_in[i].sex=='m'? "男":"女",tch_in[i].id);
	}
	anykey_continue();
}
//显示离校老师
void show_exit_tch(void)
{
	debug("%s\n",__func__);
	for(int i=0;i<tch_out_cnt;i++)
	{
		printf("%s %s\n",tch_out[i].name,tch_out[i].sex=='m'? "男":"女");
	}
	anykey_continue();
}
//修改教师密码
void tch_modify(void)
{
	debug("%s\n",__func__);
	int id;
	char pwd_1[20] = {},pwd_2[20] = {};
	for(;;)
	{
		system("clear");
		stdin -> _IO_read_ptr = stdin -> _IO_read_end;
		printf("请输入教师工号:");
		scanf("%d",&id);
		for(int i = 0;i < tch_in_cnt;i++)
		{
			//遍历到要修改的老师
			if(tch_in[i].sex && (tch_in[i].id == id))
			{
				printf("请输入6位以上，20位以下的密码！\n");
				printf("请输入新密码:");
				scanf("%s",pwd_1);
				if(strlen(pwd_1) >= 20 || strlen(pwd_1)<=6)
				{
					printf("输入的密码不符合要求，修改失败！\n");
					anykey_continue();
					return;
				}
				printf("请确认新密码:");
				scanf("%s",pwd_2);
				if(strcmp(tch_in[i].pwd,pwd_1) == 0)
				{
					show_msg("修改的密码与原密码相同，修改失败！\n",0.5);
					anykey_continue();
					return;
				}
				else if(strcmp(pwd_1,pwd_2) == 0)
				{
					memset(tch_in[i].pwd,0,sizeof(char)*30);
					strcpy(tch_in[i].pwd,pwd_1);
					show_msg("修改密码成功！\n",0.5);
					anykey_continue();
					return;
				}
				else
				{
					show_msg("两次密码不一致，修改失败\n",0.5);
					anykey_continue();
					return;
				}
			}
		}
		show_msg("您要修改的教师不存在！\n",0.5);
		anykey_continue();
		return;
	}
}
//修改校长密码
void admin_modify(void)
{
	debug("%s\n",__func__);
	char pwd_1[20] = {},pwd_2[20] = {};
	for(;;)
	{
		system("clear");
		stdin -> _IO_read_ptr = stdin -> _IO_read_end;
		printf("请输入新密码:");
		scanf("%s",pwd_1);
		if(strlen(pwd_1) >= 20 || strlen(pwd_1)<=6)
		{
			show_msg("请输入6位以上，20位以下的密码！",1.0);
			continue;
		}
		printf("请确认新密码:");
		scanf("%s",pwd_2);
		if(strcmp(admin_pwd,pwd_1) == 0)
		{
			show_msg("修改的密码与原密码相同，修改失败！\n",0.5);
			anykey_continue();
			return;
		}
		else if(strcmp(pwd_1,pwd_2) == 0)
		{
			memset(admin_pwd,0,sizeof(char)*30);
			strcpy(admin_pwd,pwd_1);
			show_msg("修改密码成功！\n",0.5);
			anykey_continue();
			return;
		}
		else
		{
			show_msg("两次密码不一致，修改失败\n",0.5);
			anykey_continue();
			return;
		}
	}
}

//运行校长密码
void run_admin(void)
{
	for(;;)
	{
		//显示校长目录
		switch(admin_show())
		{
			case '1':add_tch();break;
			case '2':del_tch();break;
			case '3':show_school_tch();break;
			case '4':show_exit_tch();break;
			case '5':tch_modify();break;
			case '6':admin_modify();break;
			case '0':return;
			default:printf("输入的数字有误，请重新输入\n");anykey_continue();
		}
	}
}