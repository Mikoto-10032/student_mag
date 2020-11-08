#ifndef TEACHER_H
#define TEACHER_H

extern int stu_in_cnt;//在校学生个数
extern int stu_out_cnt;//退学学生个数
extern int stu_id;

void add_stu(void);//添加学生

void del_stu(void);//删除学生信息

void show_school_stu(void);//显示在校学生

void find_stu(void);//查找学生信息

void change_stu_info(void);//修改学生个人信息

void put_score(void);//录入学生成绩

void tch_stu_modify(void);//老师修改学生密码

void show_exit_stu(void);//显示退学学生

void run_teacher(void);//运行老师系统

#endif//TEACHER_H
