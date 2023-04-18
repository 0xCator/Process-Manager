#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../headers/Process.h"
int validMenuChoice(int maxChoice)
{
    int input = -1;
    char text[3];
    do
    {
        fgets(text, sizeof(text), stdin);
        if (text[0] != '\n' && text[0] >= '0' && text[0] <= '9')
        {
            input = text[0] - '0';
            if (text[1] >= '0' && text[1] <= '9')
                input = (input * 10) + (text[1] - '0');
            break;
        }
    } while (1);
    
    fflush(stdin);
    if (input >= 1 && input <= maxChoice)
        return input;
    else return 0;
}

int readInt()
{
    int number = 0, i;
    char input[25];
    do
    {
        fgets(input, sizeof(input), stdin);
    } while (input[0] == '\n');
    
    for (i = 0; i < 25; i++)
    {
        if (input[i] >= '0' && input[i] <= '9')
        {
            number = (number * 10) + (input[i] - '0');
        } else if (input[i] == '\n')
            break;
    }
    

    return number;
}

void errorInput()
{
    printf("Invalid input, press enter to continue..\n");
    int c = getchar();
    fflush(stdin);
}

void waitInput()
{
    printf("Press enter to continue..\n");
    int c = getchar();
    fflush(stdin);
}

void printMainMenu()
{
    system("clear");
    printf("Process Manager\nSelect an option:\n");
    printf("1- List all system processes\n");
    printf("2- List user processes\n");
    printf("3- Run a process\n");
    printf("4- Stop a process\n");
    printf("5- Send a signal to a process\n");
    printf("6- Exit\n");
}

void stopProcessMenu()
{
    do
    {
        system("clear");
        printf("Stop a process:\n1- Stop by pID\n2- Stop by process name\n3- Go back\n");
        switch (validMenuChoice(3))
        {
            case 1:
                system("clear");
                printf("Stop a process:\n");
                printf("Process list:\n");
                ProcessPrintAll();
                printf("Enter process ID: ");
                int pID = readInt();
                ProcessKill(pID, 9);
                waitInput();
                return;
            break;
            case 2:
                system("clear");
                printf("Stop a process:\n");
                printf("Process list:\n");
                ProcessPrintAll();
                printf("Enter process name: ");
                char processName[256];
                do
                {
                    fgets(processName, sizeof(processName), stdin);
                    processName[strlen(processName)  -1] = '\0';
                } while (processName[0] == '\n');
                ProcessKillall(processName, 9);
                waitInput();
                return;
            break;
            case 3:
                return;
            break;
            case 0:
                errorInput();
            break;
        }
    } while (1);
}

void signalMenu()
{
    int signal = -1;
    do
    {
        system("clear");
        printf("Send a signal to a process:\n");
        PrintSignals();
        printf("\nEnter signal number: ");
        signal = validMenuChoice(64);
    } while (signal == 0);
    
    system("clear");
    printf("Process list:\n");
    ProcessPrintAll();
    printf("Enter process name: ");
    char processName[256];
    do {
        fgets(processName, sizeof(processName), stdin);
        processName[strlen(processName) -1 ] = '\0';
    }
    while (processName[0] == '\n');
    ProcessKillall(processName, signal);
    waitInput();
    return;
}

int main(int argc, char *argv[])
{
    while (1)
    {
        printMainMenu();
        switch(validMenuChoice(6)) 
        {
            case 1: //List all system processes
                system("clear");
                printf("All system processes: \n");
                ProcessPrintAll();
                waitInput();
            break;
            case 2: //List user processes
                system("clear");
                printf("User process: \n");
                ProcessPrint();
                waitInput();
            break;
            case 3: //Run a process
                system("clear");
                char processPath[256];
                printf("Run a process:\nEnter a process' path/name: ");
                do {
                    fgets(processPath, sizeof(processPath), stdin);
                    processPath[strlen(processPath) - 1 ]= '\0';
                }
                while (processPath[0] == '\n');
                ProcessOpen(processPath);
                waitInput();
            break;
            case 4: //Stop a process
                stopProcessMenu();
            break;
            case 5: //Send a signal to a process
                signalMenu();
            break;
            case 6: //Exit
                return 0;
            break;
            case 0:
                errorInput();
            break;
        }
    }
    return 0;
}
