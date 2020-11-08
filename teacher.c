#include "teacher.h"
#include "student.h"
#include "tools.h"
#include "struct.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

Student stu_in[STUDENT_MAX];
Student stu_out[STUDENT_MAX];

Teacher tch_in[TEACHER_MAX];
Teacher tch_out[TEACHER_MAX];

int stu_in_cnt = 0;//在校学生个数
int stu_out_cnt = 0;//退学学生个数
int stu_id = 100;

//添加学生
void add_stu(void)
	{
	printf("请输入你想添加学生的个数：");
	int n;
	scanf("%d", &n);
	if (n - STUDENT_MAX <= 0)
	{
		for (int i = 0; i < n; i++)
		{
			printf("请分别输入学生姓名和性别:");
			scanf("%s %c", stu_in[stu_in_cnt].name,&stu_in[stu_in_cnt].sex);
			stu_in[stu_in_cnt].id = ++stu_id;
			strcpy(stu_in[stu_in_cnt].pwd,"123456");
			stu_in_cnt++;//在校学生个数++
			printf("添加学生成功\n");
		}
		anykey_continue();
	}
	else if (STUDENT_MAX - stu_in_cnt < n)
	{
		int m = STUDENT_MAX - stu_in_cnt;
		printf("学校不足以添加你想要添加的学生个数，现在只能添加最多%d个学生", m);
		printf("您是否还想继续添加？\n1.继续\n2.返回菜单\n");
		int if_continue=0;
		scanf("%d", &if_continue);
		if (if_continue == 1)
		{
			printf("输入您想添加学生的个数:\n");
			int count=0;
			scanf("%d",&count);
			for (int i = 0; i < count; i++)
			{
				printf("请分别输入学生姓名和性别:");
				scanf("%s %c", stu_in[stu_in_cnt].name,&stu_in[stu_in_cnt].sex);
				stu_in[stu_in_cnt].id = ++stu_id;
				strcpy(stu_in[stu_in_cnt].pwd,"123456");
				stu_in_cnt++;//在校学生个数++
				printf("添加学生成功\n");
				
			}
			anykey_continue();
		}
		else
			return;
	}
	
}


//删除学生信息
void del_stu(void)
{
	for(;;)
	{
		printf("请输入你想删除学生的学号：\n");
		int a,b;
		scanf("%d",&a);
		printf("请再次输入学号：\n");
		scanf("%d",&b); 
		if(a!=b)
		{
			printf("学号不一致，请重新输入\n");
			continue;
		}
		else
		{
			for(int i=0;i<stu_in_cnt;i++)
			{
				if(a==stu_in[i].id)
				{
					stu_out[stu_out_cnt]=stu_in[i];
					for(int j=i;j<stu_in_cnt-1;j++)//删除的学生得到后一个所有值赋给被删除的那个学生，并制空最后一名学生的除了性别和姓名的值
					{
						stu_in[j]=stu_in[j+1];
					}
					memset(stu_in[stu_in_cnt-1].pwd,0,30*sizeof(char));//初始化密码
					stu_in[stu_in_cnt-1].math = 0;
					stu_in[stu_in_cnt-1].chinese = 0;
					stu_in[stu_in_cnt-1].english = 0;
					stu_in[stu_in_cnt-1].sum = 0;
					stu_in[stu_in_cnt-1].rank = 0;
					stu_in_cnt--;//在校学生++
					stu_out_cnt++;//退学人数++
					printf("删除成功\n");
					anykey_continue();
					return;
				}
				else
					continue;
			}
			printf("查无此人！是否想重新输入？\n1.继续输入\n2.退出\n");
			int if_continue=0;
			scanf("%d",&if_continue); 
			if(if_continue==2)
				return;
		} 
	} 
} 

//显示在校学生
void show_school_stu(void)
{
	for (int i = 0; i < stu_in_cnt; i++)
	{
		printf("学号：%d  姓名：%s  性别：%s  数学成绩：%d  语文成绩：%d  英语成绩：%d  总分：%d\n 总排名：%d\n", stu_in[i].id, stu_in[i].name, (stu_in[i].sex =='m'? "男":"女"), stu_in[i].math, stu_in[i].chinese, stu_in[i].english, stu_in[i].sum,stu_in[i].rank);
	}
	anykey_continue();

	system("clear");
}


//查找学生信息
void find_stu(void)
{
	printf("请选择你想要的功能：\n1.按姓名查找\n2.按学号查找\n3.返回上一级\n");
	int n;
	scanf("%d",&n);
	for(;;)
	{
		if(n==1)//姓名查找
		{
			printf("请输入学生姓名：");
			char name[20];
			scanf("%s",name); 
			for(int i=0;i<stu_in_cnt;i++)
			{
				if(0==strcmp(name,stu_in[i].name))
				{
					printf("学号：%d  姓名：%s  性别：%s  数学成绩：%d  语文成绩：%d  英语成绩：%d  总分：%d 总排名：%d\n", stu_in[i].id, stu_in[i].name, (stu_in[i].sex =='m'? "男":"女"), stu_in[i].math, stu_in[i].chinese, stu_in[i].english, stu_in[i].sum,stu_in[i].rank);
					anykey_continue();
					return;
				}
			}
				printf("查无此人,是否想重新输入？\n1.重新输入\n2.退出\n");
				int if_continue=0;
				scanf("%d",&if_continue);
				if(if_continue==1)
					continue;
				else
					return;
		}
		else if(n==2)//学号查找
		{
			printf("请输入学生学号：");
			int id=0;
			scanf("%d",&id);
			for(int i=0;i<stu_in_cnt;i++)
			{
				if(id==stu_in[i].id)
				{
					printf("学号：%d  姓名：%s  性别：%s  数学成绩：%d  语文成绩：%d  英语成绩：%d  总分：%d 总排名：%d\n", stu_in[i].id, stu_in[i].name, (stu_in[i].sex =='m'? "男":"女"), stu_in[i].math, stu_in[i].chinese, stu_in[i].english, stu_in[i].sum,stu_in[i].rank);
					anykey_continue();
					return;
				}
			}
			printf("查无此人,是否想重新输入？\n1.重新输入\n2.退出\n");
			int if_continue=0;
			scanf("%d",&if_continue);
			if(if_continue==1)
				continue;
			else
				return;
		}
		else// 返回主界面
			return;
	} 
}


//修改学生个人信息
void change_stu_info(void)
{
	int flag=0;
	for(;;)
	{
		printf("请输入你想修改的学生姓名：\n");
		char name[20];
		scanf("%s",name); 
		for(int i=0;i<stu_in_cnt;i++)
		{
			if(0==strcmp(name,stu_in[i].name))
			{
				printf("学号：%d  姓名：%s  性别：%s  数学成绩：%d  语文成绩：%d  英语成绩：%d  总分：%d 总排名：%d\n", stu_in[i].id, stu_in[i].name, (stu_in[i].sex =='m'? "男":"女"), stu_in[i].math, stu_in[i].chinese, stu_in[i].english, stu_in[i].sum,stu_in[i].rank);
				flag=i;
				for(;;)
				{
					printf("请选择你想修改的内容\n1.学生的基本信息\n2.学生的成绩\n3.退出\n");
					int n=0;
					scanf("%d",&n);
					if(n==1)//修改学生基本信息
					{
						printf("请选择修改的内容\n1.姓名\n2.性别\n3.我都想改\n4.返回上一级\n");
						int n1;
						scanf("%d",&n1);
						if(n1==1)
						{
							printf("请输入姓名：");
							char name[20];
							scanf("%s",name);
							strcpy(stu_in[flag].name,name);
						}
						else if(n1==2)//修改性别
						{
							printf("修改后的学生信息：\n");
							if(stu_in[flag].sex=='m')
							{
								stu_in[flag].sex='w';
							}
							else
							{
								stu_in[flag].sex='m';
							}
						}
						else if(n1==3)
						{
							printf("请输入姓名：");
							char name[20];
							scanf("%s",name);
							strcpy(stu_in[flag].name,name);
							if(stu_in[flag].sex=='m')
							{
								stu_in[flag].sex='w';
							}
							else
							{
								stu_in[flag].sex='m';
							}
						}
						else
							continue;
						printf("修改后的学生信息：\n");
						printf("学号：%d  姓名：%s  性别：%s  数学成绩：%d  语文成绩：%d  英语成绩：%d  总分：%d 总排名：%d\n", stu_in[flag].id, stu_in[flag].name, (stu_in[flag].sex =='m'? "男":"女"), stu_in[flag].math, stu_in[flag].chinese, stu_in[flag].english, stu_in[flag].sum,stu_in[flag].rank);
						anykey_continue();
						return;
					} 	
					if(n==2)//修改成绩
					{
						printf("请选择修改的内容\n1.数学成绩\n2.语文成绩\n3.英语成绩\n4.我都想改\n5.返回上一级\n");
						int n1=0;
						scanf("%d",&n1);
						if(n1==1)
						{
							printf("请输入新成绩：");
							int math=0;
							scanf("%d",&math);
							stu_in[flag].math=math;
						}
						else if(n1==2)
						{
							printf("请输入新成绩：");
							int chinese=0;
							scanf("%d",&chinese);
							stu_in[flag].chinese=chinese;
						}
						else if(n1==3)
						{
							printf("请输入新成绩：");
							int english=0;
							scanf("%d",&english);
							stu_in[flag].english=english;
						}
						else if(n1==4)
						{
							printf("请输入数学、语文、英语成绩：\n");
							int english=0,math=0,chinese=0;
							scanf("%d %d %d",&math,&chinese,&english);
							stu_in[flag].math=math;
							stu_in[flag].chinese=chinese;
							stu_in[flag].english=english;
						}
						else
							continue;
						stu_in[flag].sum=stu_in[flag].math+stu_in[flag].chinese+stu_in[flag].english;
						printf("修改后的学生信息：\n");
						printf("学号：%d  姓名：%s  性别：%s  数学成绩：%d  语文成绩：%d  英语成绩：%d  总分：%d 总排名：%d\n", stu_in[flag].id, stu_in[flag].name, (stu_in[flag].sex =='m'? "男":"女"), stu_in[flag].math, stu_in[flag].chinese, stu_in[flag].english, stu_in[flag].sum,stu_in[flag].rank);
						anykey_continue();
						return;
					}	
			else return;
				}
			}
		}
		printf("查无此人,是否想重新输入？\n1.重新输入\n2.退出\n");
		int if_continue=0;
		scanf("%d",&if_continue);
		if(if_continue==1)
			continue;
		else
			return;
	}	
}

//录入学生成绩
void put_score(void)
{
	printf("可以批量录入，输入0结束\n");
	for(;;)
	{
		printf("输入学生学号：\n");
		int id=0;
		int flag=0;
		scanf("%d",&id);
		for(int i=0;i<stu_in_cnt;i++)
		{
			if(id==0) return;
			else if(id==stu_in[i].id)
			{
				flag=1;
				printf("请分别输入数学、语文、英语成绩：");
				int math=0,chinese=0,english=0;
				scanf("%d %d %d",&math,&chinese,&english);
				stu_in[i].math=math;
				stu_in[i].chinese=chinese;
				stu_in[i].english=english;
				stu_in[i].sum=stu_in[i].math+stu_in[i].chinese+stu_in[i].english;

				printf("修改后该生成绩：\n");
				printf("学号：%d 姓名：%s 数学：%d 语文：%d 英语：%d 总分：%d\n",stu_in[i].id,stu_in[i].name,stu_in[i].math,stu_in[i].chinese,stu_in[i].english,stu_in[i].sum);
				anykey_continue();
				break;
			}
		}
		if(flag==0){
			printf("查无此人,是否想重新输入？\n1.重新输入\n2.退出\n");
			int if_continue=0;
			scanf("%d",&if_continue);
			if(if_continue==1){
				continue;
			}
			else
				return;
		}
	}
}


//老师修改学生密码
void tch_stu_modify(void)
{
	printf("请输入学生学号：\n");
	int id=0;
	int flag=0;
	for(;;)
	{
		char new_pwd[20];
		scanf("%d",&id);
		for(int i=0;i<stu_in_cnt;i++)
		{
			if(id!=stu_in[i].id)//找人
			{
				continue;
			}
			else//找到了
			{
				printf("请输入7~20位新密码：\n"); 
				scanf("%s",new_pwd);
				flag=1;
				if(strlen(new_pwd)>20||strlen(new_pwd)<7)
				{
					printf("输入密码有误请重新输入\n") ;
					break;
				}
				else
				{
					strcpy(stu_in[i].pwd,new_pwd);
					printf("您已修改成功！修改后的密码为：\n");
					printf("%s\n",stu_in[i].pwd);
					stu_in[i].lock = 0;//帐号解锁
					//printf("lock==%d\n",stu_in[i].lock);
					anykey_continue();
					return ;
				}
			}
		}
		if(flag==0){
			printf("查无此人,是否想重新输入？\n1.重新输入\n2.退出\n");
			int if_continue=0;
			scanf("%d",&if_continue);
			if(if_continue==1){
				printf("请输入学生学号：\n");
				continue;
			}
			else
				return;
		}
	}
}


//显示退学学生
void show_exit_stu(void)
{
	for (int i = 0; i < stu_out_cnt; i++)
	{
		printf("学号：%d  姓名：%s  性别：%s\n", stu_out[i].id, stu_out[i].name, (stu_out[i].sex =='m'? "男":"女"));
	}
	anykey_continue();
	system("clear");
}

//运行老师系统
void run_teacher(void)
{
	for(;;)
	{
		tch_show();
		int n;
		scanf("%d", &n);
		switch (n)
		{
			case 1:add_stu();break;
			case 2:del_stu();break;
			case 3:change_stu_info();break;
			case 4:find_stu();break;
			case 5:put_score();break;
			case 6:tch_stu_modify();break;
			case 7:show_school_stu();break;
			case 8:show_exit_stu();break;
			case 0:
				printf("欢迎下次使用\n");
				anykey_continue();
				return;
		}
	}
}



