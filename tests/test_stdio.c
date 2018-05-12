#include <stdio.h>
#include <string.h>

int main(){
	while(1){
	char comando[30];
	
	printf("digite un comando\n");
	scanf(" %[^\n]s", comando);
	printf("el comando es: %s \n", comando);

	if( ! strcmp(comando, "ls") ){
		printf("no hay directorios.\n");
		
	}
}

return 0;
}