#include <stdio.h>
#include <stdlib.h>
#include <getch.h>
#include <string.h>
#include "admin.h"
#include "teacher.h"
#include "tools.h"
#include "struct.h"

int tch_in_cnt=0;//在职教师的总人数
int tch_out_cnt=0;//离职教师的总人数
int tch_id = 1000;//教师工号从1000开始计算

char admin_pwd[30] = "123456";

//添加老师
void add_tch(void)
{
	debug("%s\n",__func__);
	system("clear");//清理屏幕
	for(;;)
	{
		if(tch_in_cnt >= TEACHER_MAX)//判断在职教师人数大于可容纳最大人数
		{
			//如果在职教师人数大于等于可容纳最大人数
			show_msg("系统升级中！\n",0.5);
			break;//退出死循环，返回校长界面
		}
		printf("请输入教师姓名、性别:");
		scanf("%s %c",tch_in[tch_in_cnt].name,&tch_in[tch_in_cnt].sex);//输入教师姓名、性别
		tch_in[tch_in_cnt].id = ++tch_id;//新增工号加一
		tch_in[tch_in_cnt].lock = 0; //判断是否输错三次密码锁定标志位清零
		strcpy(tch_in[tch_in_cnt].pwd,"123456");//初始化密码为“123456”
		tch_in_cnt++;//在职教师总人数加一
		show_msg("添加成功(1、继续添加\t0、返回主界面)\n输入指令：",0.5);
		stdin -> _IO_read_ptr = stdin -> _IO_read_end;//清理之前输入缓冲区
		char cmd;//判断是否继续添加或返回主界面
		scanf("%c",&cmd);
		if(cmd=='0') break;//如果输入为‘0’，退出死循环，返回主界面
	}
}
//删除老师
void del_tch(void)
{
	debug("%s\n",__func__);
	int id_1,id_2;
	for(;;)
	{
		system("clear");//清理屏幕
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
	for(int i = 0;i < tch_in_cnt;i++)//循环遍历在职教师
	{
		if(tch_in[i].sex && (tch_in[i].id == id_1))//判断性别不为空，且id相等
		{
			//存在要删除的教师
			strcpy(tch_out[tch_out_cnt].name,tch_in[i].name);
			tch_out[tch_out_cnt].sex = tch_in[i].sex;
			for(int j = i;j < tch_in_cnt-1;j++)
			{
				//把要删除的老师名字和密码清空
				memset(tch_in[j].name,0,sizeof(char)*20);
				memset(tch_in[j].pwd,0,sizeof(char)*20);
				//将后一位老师全部信息赋给上一位
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
			return;//返回校长界面
		}
	}
	//在循环中未找到该教师
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
	int id;//定义要输入的工号
	char pwd_1[20] = {},pwd_2[20] = {};//定义要输入的新密码、确认新密码
	for(;;)
	{
		system("clear");
		stdin -> _IO_read_ptr = stdin -> _IO_read_end;
		printf("请输入教师工号:");
		scanf("%d",&id);
		for(int i = 0;i < tch_in_cnt;i++)
		{
			//存在要修改密码的教师
			if(tch_in[i].sex && (tch_in[i].id == id))
			{
				printf("请输入6位以上，20位以下的密码！\n");
				printf("请输入新密码:");
				input_pwd(pwd_1);
				if(strlen(pwd_1) >= 20 || strlen(pwd_1)<6)	//判断新密码小于等于6位或大于等于20位
				{
					printf("输入的密码不符合要求，修改失败！\n");
					anykey_continue();
					return;
				}
				printf("请确认新密码:");
				input_pwd(pwd_2);
				if(strcmp(tch_in[i].pwd,pwd_1) == 0)	//判断输入的密码和之前的密码是否一致
				{
					show_msg("修改的密码与原密码相同，修改失败！\n",0.5);
					anykey_continue();
					return;
				}
				else if(strcmp(pwd_1,pwd_2) == 0)	//判断输入的两次密码是否一致
				{
					memset(tch_in[i].pwd,0,sizeof(char)*30);
					strcpy(tch_in[i].pwd,pwd_1);
					tch_in[i].lock = 0;
					show_msg("修改密码成功！\n",0.5);
					anykey_continue();
					return;
				}
				else		//输入的两次密码不一致
				{
					show_msg("两次密码不一致，修改失败\n",0.5);
					anykey_continue();
					return;
				}
			}
		}
		//循环遍历中未找到相对应的教师工号
		show_msg("您要修改的教师不存在！\n",0.5);
		anykey_continue();
		return;		//结束函数，返回校长界面
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
		input_pwd(pwd_1);
		if(strlen(pwd_1) >= 20 || strlen(pwd_1)<6)	//密码小于等于6位或大于等于20位
		{
			show_msg("请输入6位以上，20位以下的密码！",1.0);
			continue;
		}
		printf("请确认新密码:");
		input_pwd(pwd_2);
		if(strcmp(admin_pwd,pwd_1) == 0)		//判断输入的密码和之前的密码是否一致
		{
			show_msg("修改的密码与原密码相同，修改失败！\n",0.5);
			anykey_continue();
			return;
		}
		else if(strcmp(pwd_1,pwd_2) == 0)		//判断输入的两次密码是否一致
		{
			memset(admin_pwd,0,sizeof(char)*30);
			strcpy(admin_pwd,pwd_1);
			show_msg("修改密码成功！\n",0.5);
			anykey_continue();
			return;
		}
		else		//输入的两次密码不一致
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
			case '1':add_tch();break;				//按‘1’添加教师
			case '2':del_tch();break;				//按‘2’删除教师
			case '3':show_school_tch();break;	//按‘3’显示在职教师
			case '4':show_exit_tch();break;		//按‘4’显示离职教师
			case '5':tch_modify();break;			//按‘5’修改教师密码
			case '6':admin_modify();break;		//按‘6’修改校长密码
			case '0':return;						//按‘0’返回主界面
			default:printf("输入的数字有误，请重新输入\n");anykey_continue();
		}
	}
}
