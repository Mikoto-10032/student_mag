#ifndef SYS_H
#define SYS_H

void stu_in_read(void);//写入在校学生信息

void stu_in_write(void);//读取在校学生信息

void stu_out_write(void);//写入退出学生信息

void stu_out_read(void);//读取退出学生信息

void tch_in_read(void);//读取在校老师信息

void tch_in_write(void);//写入在校老师信息

void tch_out_read(void);//读取离职老师信息

void tch_out_write(void);//写入离职老师信息

void admin_read(void);

void admin_write(void);
	
void run_sys(void);//运行系统

#endif//SYS_H
