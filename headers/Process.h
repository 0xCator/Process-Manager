#ifndef PROCESS_H
#define PROCESS_H


int ProcessPrint();
int PrintSignals();
int ProcessKill(int pid, int sigNO);
int ProcessKillall(char * name , int sigNO);

#endif  