#ifndef STRUCT_H
#define STRUCT_H

#define  STUDENT_MAX 50
#define  TEACHER_MAX 50

//学生结构体
typedef struct Student
{
	char name[20];//姓名
	char sex;//学号
	int id;
	int chinese;
	int math;
	int english;
	int sum;
	int rank;
	char pwd[30];
	int lock;

}Student;

//老师结构体
typedef struct Teacher {
	char name[20];//姓名
	char sex;//
	int id;//工号
	char pwd[20];
	int lock;//是否锁定 0 没锁  1锁了
}Teacher;

extern Student stu_out[STUDENT_MAX];
extern Student stu_in[STUDENT_MAX];

extern Teacher tch_in[TEACHER_MAX];
extern Teacher tch_out[TEACHER_MAX];

#endif//STRUCT_H
