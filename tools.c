#include "tools.h"
#include "student.h"
#include "teacher.h"
#include "admin.h"
#include "struct.h"
//主登陆界面
int menu(void)
{
		system("clear");
		printf("******登陆界面********\n");
		printf("****1.学生登陆********\n");
		printf("****2.老师登陆********\n");
		printf("****3.校长登陆********\n");
		printf("****0.退出************\n");
		printf("请输入功能数字：");
		stdin -> _IO_read_ptr = stdin -> _IO_read_end;
		char n;
		scanf("%c",&n);
		return n;
}

char admin_show(void)
{
	debug("%s\n",__func__);
	system("clear");
	printf("******欢迎校长********\n");
	printf("****1.添加老师********\n");
	printf("****2.删除老师********\n");
	printf("****3.显示在校教师****\n");
	printf("****4.显示离职教师****\n");
	printf("****5.修改教师密码****\n");
	printf("****6.修改密码********\n");
	printf("****0.退出************\n");
	printf("请输入指令:");
	stdin -> _IO_read_ptr = stdin -> _IO_read_end;
	char cmd;
	scanf("%c",&cmd);
	return cmd;
}


//显示老师界面
void tch_show(void){
	system("clear");
	printf("欢迎来到老师管理界面,请用数字选择你想要的功能\n");
	printf("1.添加学生\n");
	printf("2.删除学生\n");
	printf("3.修改学生信息\n");
	printf("4.查找学生\n");
	printf("5.录入成绩\n");
	printf("6.重置学生密码\n");
	printf("7.显示在校学生名单\n");
	printf("8.显示退学学生名单\n");
	printf("0.退出\n");
}


//显示学生登录界面
char stu_show(void)
{
	system("clear");
	printf("******欢迎学生********\n");
	printf("****1.查看个人信息****\n");
	printf("****2.查询成绩********\n");
	printf("****3.修改密码********\n");
	printf("****0.退出************\n");
	printf("请输入指令:");
	stdin -> _IO_read_ptr = stdin -> _IO_read_end;
	char cmd;
	scanf("%c",&cmd);
	return cmd;
}


//打印提示信息
void show_msg(const char* msg,float sec)
{
	printf("%s",msg);
	fflush(stdout);		//如果msg没有换行符，就手动刷新
	usleep(sec*1000000);
}

//按任意键继续..
void anykey_continue(void)
{
	puts("按任意键继续");
	//防止输入缓冲区中有残留的字符,导致getch()直接输出
	stdin -> _IO_read_ptr = stdin -> _IO_read_end;
	getch();
}
//隐藏输入密码
void input_pwd(char pwd[30])
{
	int i = 0;
	while(1)
	{
		stdin -> _IO_read_ptr = stdin -> _IO_read_end;
		pwd[i] = getch();
		fflush(stdin);
		if(i > 20)
		{
			system("clear");
			memset(pwd,0,sizeof(char)*30);
			i=0;
			show_msg("请输入20位以下的密码！",1.0);
			anykey_continue();
			printf("请输入新密码：");
			continue;
		}
		if(pwd[i] == 127)
		{
			if(i > 0)
			{
				printf("\b \b");
				i--;
				pwd[i] = '\0';
				continue;
			}
			else
			{
				continue;
			}
		}
		else if(pwd[i] == 10)
		{
			pwd[i] = '\0';
			if(i < 6)
			{
				system("clear");
				memset(pwd,0,sizeof(char)*30);
				i=0;
				show_msg("请输入6位或6位以上的密码！",1.0);
				anykey_continue();
				printf("请重新输入密码：");
				continue;
			}
			break;
		}
		else
		{
			printf("*");
		}
		i++;
	}
	printf("\n");
}

//判断学生登陆
int stu_input_pwd(void)
{
	int flag = 0;	//判断学生帐号输入是否正确
	int id;
	char pwd[30];
	system("clear");
	printf("欢迎学生登陆\n");
	printf("请输入学号：");
	scanf("%d",&id);
	stdin -> _IO_read_ptr = stdin -> _IO_read_end;
	printf("请输入密码：");
	input_pwd(pwd);
	
	for(int j=0;j<stu_in_cnt;j++)//进入循环
	{	
		//学生帐号输入正确
		if(id == stu_in[j].id)
		{	
			//此帐号已经三次输错密码
			if(stu_in[j].lock == 3)
			{
				printf("此帐号已经锁死，请找老师解锁\n");
				anykey_continue();//调用按任意键继续..函数
				return 0;		//帐号锁住，登陆失败，返回主界面
			}
			flag = 1;
			//学生第一次登陆，强制修改密码
			if((strcmp(stu_in[j].pwd,"123456")==0) && (strcmp(pwd,"123456")==0))
			{
				opt = j;				//表示是第opt个学生在操作
				stu_modify();		//修改密码
				return 1;				//登陆成功，进入学生界面
			}
			//非第一次登陆成功
			else if(strcmp(pwd,stu_in[j].pwd)==0)
			{
				opt = j;
				stu_in[j].lock = 0;		//登陆成功，将锁判定重置
				return 1;
			}
			//登陆失败，且密码错误
			else if(strcmp(pwd,stu_in[j].pwd)!=0)
			{
				stu_in[j].lock++;
				if(stu_in[j].lock<3)
				{
					printf("密码错误，请重新输入(此帐号还有%d次机会)\n",3-stu_in[j].lock);
				}
				else if(stu_in[j].lock == 3)
				{
					printf("此帐号已经锁死，请找老师解锁\n");
				}
				anykey_continue();//按任意键继续
				return 0;
			}
		}
	}
	//学生帐号输入错误
	if(flag==0)
	{
		printf("学号错误，请重新登陆");
		anykey_continue();
		return 0;
	}
	return 0;
}

//教师第一次登陆,修改密码
void tch_modify_first(int num)
{
	debug("%s\n",__func__);
	char pwd_1[20] = {},pwd_2[20] = {};
	for(;;)
	{
		system("clear");
		printf("第一次登陆，请修改密码：\n");
		stdin -> _IO_read_ptr = stdin -> _IO_read_end;
		printf("请输入新密码:");
		input_pwd(pwd_1);
		//判断密码是否设定在6到20位
		if(strlen(pwd_1) >= 20 || strlen(pwd_1)<=6)
		{
			show_msg("请输入6位以上，20位以下的密码！",0.5);
			continue;		//跳出本次循环
		}
		printf("请确认新密码:");
		input_pwd(pwd_2);
		//判断两次输入密码是否一致
		if(strcmp(pwd_1,pwd_2) == 0)
		{
			memset(tch_in[num].pwd,0,sizeof(char)*30);
			strcpy(tch_in[num].pwd,pwd_1);
			show_msg("修改密码成功！\n",0.5);
			anykey_continue();
			return;
		}
		else
		{
			show_msg("两次密码不一致，请重新输入\n",0.5);
			anykey_continue();
			continue;
		}
	}
}
//判断老师登陆
int tch_input_pwd(void)
{
	int flag = 0;//判断教师帐号是否输入正确
	int id;
	char pwd[30];
	system("clear");
	printf("欢迎老师登陆\n");
	printf("请输入工号：");
	scanf("%d",&id);
	stdin -> _IO_read_ptr = stdin -> _IO_read_end;
	printf("请输入密码：");
	input_pwd(pwd);
	for(int j=0;j<tch_in_cnt;j++)
	{	
		//帐号输入正确
		if(id == tch_in[j].id)
		{
			if(tch_in[j].lock == 3)
			{
				printf("此帐号已经锁死，请找老师解锁\n");
				anykey_continue();
				return 0;
			}
			flag = 1;
			//教师第一次登陆成功
			if((strcmp(tch_in[j].pwd,"123456")==0) && (strcmp(pwd,"123456")==0))
			{
				tch_modify_first(j);
				return 1;
			}
			//教师非第一次登陆成功
			else if(strcmp(pwd,tch_in[j].pwd)==0)
			{
				tch_in[j].lock = 0;
				return 1;
			}
			//登陆失败，且密码错误
			else if(strcmp(pwd,tch_in[j].pwd)!=0)
			{
				tch_in[j].lock++;
				if(tch_in[j].lock<3)
				{
					printf("密码错误，请重新输入(此帐号还有%d次机会)\n",3-tch_in[j].lock);
				}
				else if(tch_in[j].lock == 3)//输错三次锁定帐号
				{
					printf("此帐号已经锁死，请找老师解锁\n");
				}
				anykey_continue();
				return 0;
			}
		}
	}
	//帐号输入错误
	if(flag==0)
	{
		printf("工号错误，请重新登陆");
		anykey_continue();
		return 0;
	}
	return 0;
}
//判断校长登陆
int admin_input_pwd(void)
{
	int flag = 0;
	char admin_id[30];
	char pwd[30];
	system("clear");
	printf("欢迎校长登陆\n");
	printf("请输入用户名：");
	scanf("%s",admin_id);
	stdin -> _IO_read_ptr = stdin -> _IO_read_end;
	printf("请输入密码：");
	input_pwd(pwd);
	if(strcmp(admin_id,"admin")==0)//用户名正确
	{
		flag = 1;//标记用户名正确
		if((strcmp(admin_pwd,"123456")==0) && (strcmp(pwd,"123456")==0) )//第一次登陆
		{
			//修改校长密码
			admin_modify();
			return 1;
		}
		else if(strcmp(admin_pwd,pwd)==0)//不是第一次登陆
		{
			return 1;
		}
		else if(strcmp(admin_pwd,pwd)!=0)//密码错误
		{
			printf("密码错误，请重新登陆\n");
			anykey_continue();
			return 0;
		}
	}
	//用户名输入错误
	if(flag==0)
	{
		printf("用户名错误，请重新登陆");
		anykey_continue();
		return 0;
	}
	return 0;
}

