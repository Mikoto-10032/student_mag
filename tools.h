#ifndef TOOLS_H
#define TOOLS_H

#ifdef DEBUG
	#define debug(...) printf(__VA_ARGS__)
#else
	#define debug(...)
#endif

#include <stdio.h>
#include <stdlib.h>
#include <getch.h>
#include <string.h>

int menu(void);	//显示登陆界面

char stu_show(void);//显示学生登录界面

void tch_show(void);//显示老师界面

char admin_show(void);//显示校长界面

void show_msg(const char* msg,float sec); //如果msg没有换行符，就手动刷新

void anykey_continue(void);//按任意键继续

void input_pwd(char pwd[30]);//隐藏输入密码

int stu_input_pwd(void);//判断学生登陆

int tch_input_pwd(void);//判断老师登陆

int admin_input_pwd(void);//判断校长登陆
#endif//TOOLS_H
