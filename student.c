#include "student.h"
#include "teacher.h"
#include "struct.h"
#include "tools.h"

#include <stdio.h>
#include <stdlib.h>
#include <getch.h>
#include <stdbool.h>
#include <string.h>

int opt = 0;//当前操作的学生的位数

//按总成绩从高到低排序
int score_cmp(const void *a ,const void *b) 
{ 
	return ((struct Student *)a)->sum < ((struct Student *)b)->sum ? 1 : -1; 
} 

//按学号从低到高排名
int id_cmp(const void *a,const void *b)
{
	return ((struct Student *)a)->id > ((struct Student *)b)->id ? 1 : -1;
}

//显示个人信息
void stu_show_info(void)
{
	printf("%s %s %d\n",stu_in[opt].name,'w' == stu_in[opt].sex?"女":"男",stu_in[opt].id);
	anykey_continue();
}

//查询成绩
void stu_find_score(void)
{
	float score_sum = 0;
	int score_max = 0;	//最高分
	int score_min = 0;	//最低分
	//从高到低排序学生成绩
	qsort(stu_in,stu_in_cnt,sizeof(stu_in[0]),score_cmp);
	for(int i=0;i<stu_in_cnt;i++)
	{
		stu_in[i].rank = i+1;
		score_sum += stu_in[i].sum;
	}
	score_min = stu_in[stu_in_cnt-1].sum;
	score_max = stu_in[0].sum;
	//按学号从低到高排序，使学生结构体数组按学号排列
	qsort(stu_in,stu_in_cnt-1,sizeof(stu_in[0]),id_cmp);
	
	printf("     语文  数学  英语  总分  总分排名\n");
	printf("成绩： %d    %d   %d   %d      %d\n",
			stu_in[opt].chinese,stu_in[opt].math,stu_in[opt].english,stu_in[opt].sum,stu_in[opt].rank);
	printf("平均分：%.2f\n",score_sum/stu_in_cnt);
	printf("最高分：%d\n",score_max);
	printf("最低分：%d\n",score_min);
	anykey_continue();
}

//修改密码
void stu_modify(void)
{
	char pwd_1[30]={},pwd_2[30]={};
	for(;;)
	{	
		system("clear");
		printf("请输入新密码：");
		input_pwd(pwd_1);
		if(strlen(pwd_1) >= 20 || strlen(pwd_1)<6)
		{
			show_msg("请输入6位以上，20位以下的密码！",1.0);
			continue;
		}
		printf("请再次输入密码：");
		input_pwd(pwd_2);
		if(strcmp(stu_in[opt].pwd,pwd_2) == 0)					//判断输入的密码和之前的密码是否一致
		{
			show_msg("修改的密码与原密码相同，修改失败！",1.0);
			break;
		}
		else if(strcmp(pwd_1,pwd_2) == 0)						//判断输入的两次密码是否一致
		{
			//将原密码置空，新密码赋值给原密码
			memset(stu_in[opt].pwd,0,sizeof(char)*30);
			strcpy(stu_in[opt].pwd,pwd_1);
			show_msg("修改密码成功！",1.0);
			break;
		}
		else															//输入的两次密码不一致
		{
			show_msg("两次密码不一致，请重新输入",1.0);
		}
	}
}

//运行学生系统
void run_student(void)
{
	for(;;)
	{
		//显示学生目录
		switch(stu_show())
		{
			case '1':stu_show_info();break;
			case '2':stu_find_score();break;
			case '3':stu_modify();break;
			case '0':return;
			default:printf("输入的数字有误，请重新输入\n");anykey_continue();
		}
	}
}
