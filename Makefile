
main: libauxshell.a
	gcc -L. -o shell.basic shell.basic.c -lauxshell 
libauxshell.a: auxshell.o
	ar -cvq libauxshell.a auxshell.o
auxshell.o: 
	gcc -c auxshell.c
clean:
	rm -f main a.out lib*.a *.o 