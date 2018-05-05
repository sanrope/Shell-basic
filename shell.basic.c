#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
// author :  Santiago Rodriguez : rodriguez.santiago@correounivalles.edu.co
// date : May 5, 2018.
int main(int argc, char *argv[]){
	while(1){
		char command[80];
		scanf("%s", command);
		if( ! strcmp(command, "exit")){
			break;
		}else{

			int rc = fork();
			if (rc < 0) {// fork failed; exit
				fprintf(stderr, "fork failed\n");
				exit(1);
			} else if (rc == 0) { // child: redirect standard output to a file // not yet.
				//close(STDOUT_FILENO);
				//open("./p4.output", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
			   // now exec command...
				char *myargs[2];
				myargs[0] = strdup(command);   // program: command with out arguments
				//myargs[1] = strdup("p4.c"); // argument: file to count // not yet.
				myargs[1] = NULL;           // marks end of array
				execvp(myargs[0], myargs);  // runs command
			} else {// parent goes down this path (main)
				int wc = wait(NULL);
			}
		}
	}
	return 0;
}
