#ifndef TEACHER_H
#define TEACHER_H

extern int stu_in_cnt;//在校学生个数
extern int stu_out_cnt;//退学学生个数
extern int stu_id;

void add_stu(void);

void del_stu(void);

void show_school_stu(void);

void find_stu(void);

void change_stu_info(void);

void put_score(void);

void tch_stu_modify(void);

void show_exit_stu(void);

void run_teacher(void);

#endif//TEACHER_H
