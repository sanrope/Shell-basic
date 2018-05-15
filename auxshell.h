#ifndef __AUXSHELL__
#define __AUXSHELL__

void discrimand(char command_args[80], char** reference);
void outToFile(char ** argss);
void divArray(char ** arrayToDiv, char*** first, char*** second);
int existPipe(char** commands);
void piper(char ** arguments);
#endif

