#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

#ifdef _WIN32
#include <windows.h> //  to use the Sleep function
#else
#include <unistd.h> // for linux and mac to use the sLeep function
#endif

int ChoiceInput(int max)
{
    int num;
    char ch;

    while(1){
        printf("Enter: ");
        // check if scanf reads one integer and nothing else
        if(scanf("%d%c", &num, &ch) == 2 && ch == '\n'){
            if (num > max || num < 1){
                printf("Invalid choice.\n");
            }
            else{
                return num;
            }
        }
        else{
            printf("Invalid input.\n");

            // clear invalid input from buffer
            while ((ch = getchar()) != '\n' && ch != EOF);
        }
    }
}

void InputString(char * TheString, int size)
// Remove trailing newline from fgets
{
    printf("Enter: ");
    if (fgets(TheString, size, stdin)) {
        
        TheString[strcspn(TheString, "\n")] = '\0'; // this function looks for any instances of a new line 
                                                    // and replaces it with null
    }
}

void Sleeps(int mili) // sleep function for all operating systems
{
    #ifdef _WIN32
        Sleep(mili);
    #else
        usleep(mili);
    #endif
}

void ClearScreen() // system clear for all operating systems
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void Akward()
// function to print akward periods at the end of sentences, there are intervals between them
{
    for (int i = 0; i<4;i++){
        printf(".");
        Sleeps(300);
    }
}