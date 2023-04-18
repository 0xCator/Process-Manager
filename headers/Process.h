#ifndef PROCESS_H
#define PROCESS_H

int ProcessOpen(char * path);
int ProcessPrintAll();
int ProcessPrint();
int PrintSignals();
int ProcessKill(int pid, int sigNO);
int ProcessKillall(char * name , int sigNO);
int ProcessInteractive();
int ProcessInteractiveAll();

#endif  
