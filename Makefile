CC=gcc
BIN=work.out
STD=-std=gnu99
FLAG=-Wall -Werror
OBJ=main.o sys.o student.o teacher.o admin.o tools.o 

all:$(OBJ)
	$(CC) -o $(BIN) $(OBJ)
main.o:main.c sys.h
	$(CC) $(STD) $(FLAG) -c main.c
sys.o:sys.c sys.h teacher.h student.h admin.h tools.h struct.h
	$(CC) $(STD) $(FLAG) -c sys.c
student.o:student.c student.h struct.h tools.h
	$(CC) $(STD) $(FLAG) -c student.c
teacher.o:teacher.c teacher.h struct.h tools.h student.h
	$(CC) $(STD) $(FLAG) -c teacher.c
admin.o:admin.c admin.h teacher.h struct.h tools.h 
	$(CC) $(STD) $(FLAG) -c admin.c
tools.o:tools.c tools.h student.h teacher.h admin.h struct.h 
	$(CC) $(STD) $(FLAG) -c tools.c
clean:
	rm -rf $(BIN) $(OBJ)
