#include "sys.h"

int main(int argc,char* argv[])
{
	//从文件中读取老师、学生信息
	stu_in_read();
	
	stu_out_read();
	
	tch_in_read();
	
	tch_out_read();
	
	admin_read();
	//运行系统
	run_sys();
	//系统结束后写入老师、学生信息到文件中
	stu_in_write();
	
	stu_out_write();
	
	tch_in_write();
	
	tch_out_write();
	
	admin_write();
	return 0;
}
