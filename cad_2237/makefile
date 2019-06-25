CC = gcc
CFLAGS = -Wall -g
LIB = -ltcl -lreadline

all: main_shell.o tcl_api.o readline_api.o aux_functions.o
	$(CC) $(CFLAGS) main_shell.o tcl_api.o readline_api.o aux_functions.o -o main_shell $(LIB)
	
main_shell.o: main_shell.c tcl_api.h readline_api.h
	$(CC) $(CFLAGS) -c main_shell.c $(LIB)
	
tcl_api.o: tcl_api.c tcl_api.h aux_functions.h
	$(CC) $(CFLAGS) -c tcl_api.c $(LIB)
	
readline_api.o: readline_api.c readline_api.h
	$(CC) $(CFLAGS) -c readline_api.c $(LIB)

#functions.o: functions.c functions.h aux_functions.h #aux_functions.c
#	$(CC) $(CFLAGS) -c functions.c $(LIB)

aux_functions.o: aux_functions.c aux_functions.h
	$(CC) $(CFLAGS) -c aux_functions.c $(LIB)

clean:
	rm -f *.o main_shell
