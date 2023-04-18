#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>
#include <string.h>
#include "../headers/Process.h"


pid_t pid1;
pid_t pid2;
int fd[2];
// -- fd[0] read
// -- fd[1] write



int ProcessOpen(char * path){
    pid_t pid;
    if((pid = fork()) == -1)
        return -1;
    //child process
    if(pid == 0){
      execlp(path,path,NULL);
      exit(0);
    }
    return 0;
}

int ProcessPrintAll(){
    return execlp("ps","ps","aux",NULL);
}
int ProcessPrint(){
    if(pipe(fd) == -1) // create pipe
        return -1; // error code for broken  pipe 
    if((pid1 = fork()) == -1) // fork for 'ps'
        return -2; // error code for fork 
    
    // child process 'ps'
    if (pid1 == 0) {
        dup2(fd[1], STDOUT_FILENO); // make stdout of pipe point to stdout of child process
        
        // close unused file descriptor
        close(fd[1]);
        close(fd[0]);

        execlp("ps","ps","axo","fname,pid,user",NULL);

    }


    if((pid2 = fork()) == -1) // fork for 'grep'
        return -2; // error code for fork
    
    // child process "grep"
    if(pid2 ==0){
        dup2(fd[0],STDIN_FILENO); // make stdin of pipe point to stdin of child process
        //close unsed file descriptor
        close(fd[0]);
        close(fd[1]);
        const char * user = getenv("USER"); // get user name 
        execlp("grep","grep","--color=none",user,NULL);
    }

    // close file descriptor of parent process
    // to privint chiled  process to read from parent
    close(fd[0]);
    close(fd[1]);
    
    //wait untill process to finish
    waitpid(pid1,NULL,0);
    waitpid(pid2,NULL,0);

   return 0; // success code 
}

int PrintSignals(){
    int fd = open("../files//signals.txt", O_RDWR);
    if(fd == -1)
        return -3; // file not found error code
    char c[840];
    read(fd,c,840);
    printf("%s",c);
    close(fd);
    return 0;
}
int ProcessKill(int pid, int sigNO){
  return kill(pid, sigNO);
 
}
int ProcessKillall(char * name , int sigNO){
    char tmp[2];
    char sig[3] = "-";
    int i =0;
    while(sigNO != 0){
        int rem =sigNO % 10;
        tmp[i++] = (rem > 9) ? (rem - 10) + 'a' : rem +'0';
        sigNO/= 10;
    }
    strcat(sig,tmp);
    return execlp("killall","killall",sig,name,NULL);
}
