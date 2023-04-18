#include <stdio.h>
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
    

    if (input >= 1 && input <= maxChoice)
        return input;
    else return 0;
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
                //ProcessPrintAll();
                waitInput();
            break;
            case 2: //List user processes
                system("clear");
                printf("User process: \n");
                //ProcessPrint();
                waitInput();
            break;
            case 3: //Run a process
                system("clear");
                char processPath[256];
                printf("Run a process:\nEnter a process' path/name: ");
                fgets(processPath, sizeof(processPath), stdin);
                //ProcessOpen(processPath);
                waitInput();
            break;
            case 4: //Stop a process
                system("clear");

            break;
            case 5: //Send a signal to a process
                system("clear");

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
