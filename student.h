#ifndef STUDENT_H
#define STUDENT_H

extern int opt;//当前操作者的位数

int score_cmp(const void *a ,const void *b);//按总成绩从高到低排序

int id_cmp(const void *a,const void *b);//学号排名

void stu_show_info(void);//显示学生信息

void stu_find_score(void);//查询学生成绩

void stu_modify(void);//修改密码

void run_student(void);//运行学生系统

#endif//STUDENT_H
