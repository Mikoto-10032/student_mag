#ifndef ADMIN_H
#define ADMIN_H

extern int tch_in_cnt;//在校教师
extern int tch_out_cnt;//离职教师
extern int tch_id;//教师id
extern char admin_pwd[30];//校长密码

void add_tch(void);//添加老师

void del_tch(void);//删除老师

void show_school_tch(void);//显示在校老师

void show_exit_tch(void);//显示离校老师

void tch_modify(void);//重置教师密码

void admin_modify(void);//修改校长密码

void run_admin(void);//运行校长系统

#endif//ADMIN_H
