#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <ctype.h>


void discrimand(char command_args[80], char** reference){//comprobaded. 
	char *aux;
	int i=0;
	aux = strtok(command_args, " "); // strtrok, divide los valores perados por " ".
	while(aux != NULL){// mientras no llegue a el final del la cadena null-terminated. 
		reference[i]=strdup(aux);// se construlle el arreglo.
		reference[i+1]= NULL;// se asegura de que en la ultima posicion haya un NULL
		aux = strtok(NULL, " ");//siguiente llamado de strtok, para leer el siguiente string.
		i++; // incremento del ciclo.
	}
}

void outToFile(char ** argss){ // comprobaded.
	char here[3]="./";
	char aux[3]= ">";
	int j=0;
	while(argss[j]!=NULL){// mientras no llegue al final del los datos donde habra un NULL

		if(! strcmp(argss[j], aux)){//si encuentra un redireccionamiento
			close(STDOUT_FILENO);// cierro la salida estandar.
			open(strcat(here, argss[j+1]), O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);//abro el file descriptor con el archivo.
			argss[j]= NULL;// termino el ciclo. y me aseguro de que los argumentos esten termiados por un NULL.
		}
		j++;// incremento del ciclo.
	}
}

void divArray (char ** arrayToDiv, char*** first, char*** second) {	//comprobaded. 
	char aux[3]= "|";
	int flag=0;
	int i=0;
	while(arrayToDiv[i] != NULL){//mientras no llegue al final de los datos donde hay un NULL
		if(!strcmp(arrayToDiv[i], aux)){//si encuentra un | (pipe).
			*second = arrayToDiv + i + 1;// sumar i +1 posiciones al puntero para tener esa secciond del arreglo
			arrayToDiv[i]=NULL;// | se convierte en NULL para delimitar los argumentos
			*first = arrayToDiv;// asigna la primera parte del arreglo.
		}
		i++;// incremento del cilo.
	}

}

int existPipe(char** commands){ // comprobaded.
	int j=0;
	char aux[3]="|";
	while(commands[j] != NULL){// 
		if(!strcmp(commands[j], aux)){
			return 1;
		}
		j++;
	}
	return 0;
}

void piper(char ** arguments){// comprobaded.
	
	int fd[2], estado;
	pid_t hijo;
	char** argumento1; //argumentos comando 1
	char** argumento2;// arguenttos comando 2.
	divArray(arguments, &argumento1, &argumento2);

	hijo=fork();
	if (hijo==-1) printf("ERROR Creacion de proceso"); 
	else if (hijo==0) {
			   pipe(&fd[0]); // Funcion pipe encargada de crear la tuberia  // llamado a sistema
			   if (fork()!=0) {
	      				close(fd[0]); // cerramos el lado de lectura del pipe *
	      				close(1);
	      				dup(fd[1]); // STDOUT = extremo de salida del pipe *
	      				close(fd[1]);// cerramos el descriptor de fichero que sobra tras el dup(fd[1])*
	      				execvp(argumento1[0],argumento1);
	      			}
	      			else {
	      				close(fd[1]);//cerramos el lado de escritura del pipe *
	      				close(0);
	      				dup(fd[0]);// STDOUT = extremo de salida del pipe *
	      				close(fd[0]);// cerramos el descriptor de fichero que sobra tras el dup(fd[0])*
					outToFile(argumento2);
	      				execvp(argumento2[0],argumento2);// llamado a sistema

	      			}
	      		}
	      		else  hijo=wait(&estado); //
	      	}

