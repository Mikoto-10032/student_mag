#include <stdio.h>
#include "sys.h"
#include "tools.h"
#include "student.h"
#include "teacher.h"
#include "admin.h"
#include "struct.h"
//写入在校学生信息
void stu_in_write(void)
{
	FILE *fwp = fopen("stu_in.txt","w");
	if(fwp == NULL)
	{
		printf("Cannot open file!\n");
		return;
	}
	fprintf(fwp,"%d %d\n",stu_in_cnt,stu_in[stu_in_cnt-1].id);//写入在校学生人数
	for(int i=0;i<stu_in_cnt;i++)
	{
		fprintf(fwp,"%s %c %d %d %d %d %d %d %s %d\n",stu_in[i].name,stu_in[i].sex,stu_in[i].id,stu_in[i].chinese,stu_in[i].math,stu_in[i].english,stu_in[i].sum,stu_in[i].rank,stu_in[i].pwd,stu_in[i].lock);
	}
	fclose(fwp);
}
//读取在校学生信息
void stu_in_read(void)
{
	//打开文件
	FILE *frp = fopen("stu_in.txt","r");
	if(frp == NULL)
	{
		printf("Cannot open file!\n");
		return;
	}
	fscanf(frp,"%d %d",&stu_in_cnt,&stu_id);//读取在校学生人数
	for(int i = 0; i<stu_in_cnt;i++)
	{
		fscanf(frp,"%s %c %d %d %d %d %d %d %s %d\n",stu_in[i].name,&stu_in[i].sex,&stu_in[i].id,&stu_in[i].chinese,&stu_in[i].math,&stu_in[i].english,&stu_in[i].sum,&stu_in[i].rank,stu_in[i].pwd,&stu_in[i].lock);
	}
	fclose(frp);
}
//写入退出学生信息
void stu_out_write(void)
{
	FILE *fwp = fopen("stu_out.txt","w");
	if(fwp == NULL)
	{
		printf("Cannot open file!\n");
		return;
	}
	fprintf(fwp,"%d\n",stu_out_cnt);//写入在校学生人数
	for(int i=0;i<stu_out_cnt;i++)
	{
		fprintf(fwp,"%s %c %d\n",stu_out[i].name,stu_out[i].sex,stu_out[i].id);
	}
	fclose(fwp);
}
//读取退出学生信息
void stu_out_read(void)
{
	//打开文件
	FILE *frp = fopen("stu_out.txt","r");
	if(frp == NULL)
	{
		printf("Cannot open file!\n");
		return;
	}
	fscanf(frp,"%d",&stu_out_cnt);//读取退出学生人数
	for(int i = 0; i<stu_out_cnt;i++)
	{
		fscanf(frp,"%s %c %d\n",stu_out[i].name,&stu_out[i].sex,&stu_out[i].id);
	}
	fclose(frp);
}
//读取在校老师信息
void tch_in_read(void)
{
	//打开文件
	FILE *frp = fopen("tch_in.txt","r");
	if(frp == NULL)
	{
		printf("Cannot open file!\n");
		return;
	}
	fscanf(frp,"%d %d",&tch_in_cnt,&tch_id);//读取在校教师人数
	for(int i = 0; i<tch_in_cnt;i++)
	{
		fscanf(frp,"%s %c %d %s %d\n",tch_in[i].name,&tch_in[i].sex,&tch_in[i].id,tch_in[i].pwd,&tch_in[i].lock);
	}
	fclose(frp);
}
//写入在校老师信息
void tch_in_write(void)
{
	FILE *fwp = fopen("tch_in.txt","w");
	if(fwp == NULL)
	{
		printf("Cannot open file!\n");
		return;
	}
	fprintf(fwp,"%d %d\n",tch_in_cnt,tch_in[tch_in_cnt-1].id);//写入在校教师人数和最后一人id
	for(int i=0;i<tch_in_cnt;i++)
	{
		fprintf(fwp,"%s %c %d %s %d\n",tch_in[i].name,tch_in[i].sex,tch_in[i].id,tch_in[i].pwd,tch_in[i].lock);
	}
	fclose(fwp);
}

//读取离职老师信息
void tch_out_read(void)
{
	//打开文件
	FILE *frp = fopen("tch_out.txt","r");
	if(frp == NULL)
	{
		printf("Cannot open file!\n");
		return;
	}
	fscanf(frp,"%d",&tch_out_cnt);//读取离职教师人数
	for(int i = 0; i<tch_out_cnt;i++)
	{
		fscanf(frp,"%s %c\n",tch_out[i].name,&tch_out[i].sex);
	}
	fclose(frp);
}

//写入离职老师信息
void tch_out_write(void)
{
	FILE *fwp = fopen("tch_out.txt","w");
	if(fwp == NULL)
	{
		printf("Cannot open file!\n");
		return;
	}
	fprintf(fwp,"%d\n",tch_out_cnt);//写入离职教师人数
	for(int i=0;i<tch_out_cnt;i++)
	{
		fprintf(fwp,"%s %c\n",tch_out[i].name,tch_out[i].sex);
	}
	fclose(fwp);
}

//取读校长信息
void admin_read(void)
{
	//打开文件
	FILE *frp = fopen("admin.txt","r");
	if(frp == NULL)
	{
		printf("Cannot open file!\n");
		return;
	}
	fscanf(frp,"%s",admin_pwd);
	fclose(frp);
}

//写入校长信息
void admin_write(void)
{
	FILE *fwp = fopen("admin.txt","w");
	if(fwp == NULL)
	{
		printf("Cannot open file!\n");
		return;
	}
	fprintf(fwp,"%s\n",admin_pwd);
	fclose(fwp);
}

//运行系统
void run_sys(void)
{
	for(;;)
	{   
		switch(menu())
		{
			case '1':if(stu_input_pwd()) run_student();break;
			case '2':if(tch_input_pwd()) run_teacher();break;
			case '3':if(admin_input_pwd()) run_admin();break;
			case '0':return;
			default:printf("输入的数字有误，请重新输入\n");anykey_continue();
		}

	}
}
