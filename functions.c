#include <stdio.h>
#include "functions.h"
#include <time.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h> // unicode
#else
#include <unistd.h> 
#endif


int RemoveValue(int * arr, int removeVal, int * size)
// function to remove a value from a function, updating its size as well
{
    int j = 0, found = 0;
    // only adds values that isn't the remove value, but only it's first instance
    // sometimes there are multiple encounters in an area, and removing all occurences would remove those encounters
    for (int i = 0; i < *size; i++) {
        if (!found && arr[i] == removeVal) {
            found = 1; // skip this occurrence
            continue;
        }
        arr[j++] = arr[i];
    }

    if (found) {
        *size = *size - 1; // reduce size by one
    }

    return found;
}

void Heal(int full, int* health)
{
    *health = full; // Sets health to full, essentially healing
}

void PrintHealth(int health)
// function to display health bar
{
    #ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8); // forces console to use unicode
    #endif
    for (int i = 0; i<health;i++){
        printf("♥ "); // this is the unicode heart i wanted to use
    }
}

void BattleScreen(int PlayerHealth, int EnemyHealth, char PlayerName[], char EnemyName[])
// function to display the status of a battle (Health of both combatants)
{
    ClearScreen();
    printf("%s's health: ", EnemyName);
    PrintHealth(EnemyHealth);
    printf("\n\n%s's health: ", PlayerName);
    PrintHealth(PlayerHealth);
    printf("\n\n");
}

int BattleMode(int *PlayerHealth, int EnemyHealth, int PlayerPower, int EnemyPower, char PlayerName[], char EnemyName[]) 
// battle loop, returns if they player wins or not
{
    // Using the pointer of the players health so that it updates in the function without having to return the value
    int choice, won = 0;
    // Epicly declares the matchup before beginning
    printf("Battle between %s and %s!", PlayerName, EnemyName);
    Sleeps(2000);
    do {
        BattleScreen(*PlayerHealth, EnemyHealth, PlayerName, EnemyName);
        // Shows the players options
        printf("1. Attack\n");
        choice = ChoiceInput(1);
        BattleScreen(*PlayerHealth, EnemyHealth, PlayerName, EnemyName);
        printf("%s's attack!\n", PlayerName);
        Sleeps(1000);

        BattleScreen(*PlayerHealth, EnemyHealth, PlayerName, EnemyName);
        printf("%s did %d damage!\n", PlayerName, PlayerPower);
        Sleeps(1000);

        EnemyHealth -= PlayerPower;// updates health
        BattleScreen(*PlayerHealth, EnemyHealth, PlayerName, EnemyName);

        if (EnemyHealth > 0){
            // Enemy attacks if alive
            printf("%s's attack!\n", EnemyName);
            Sleeps(2000);
            BattleScreen(*PlayerHealth, EnemyHealth, PlayerName, EnemyName);
            printf("%s did %d damage!\n", EnemyName, EnemyPower);
            Sleeps(1000);
            *PlayerHealth -= EnemyPower;
        }

        else{
            // Battle ends if enemy is defeated
            Sleeps(3000);
            ClearScreen();
            won = 1;
        }

    } while (*PlayerHealth > 0 && EnemyHealth > 0);
    return won; // returns if they won or not

}

void PrintText(const char *filename, const char *sectionKey)
{
// function to print a specific section of a text file
// my text files are seperated by sections in big brackets []

    FILE *file = fopen(filename, "r");
    if (!file){
        printf("Failed to open dialogue file: %s\n", filename);
        return;
    }

    char line[256];
    int inSection = 0;
    char sectionHeader[64];
    snprintf(sectionHeader, sizeof(sectionHeader), "[%s]", sectionKey); // builds [INTRO1], etc.

    while (fgets(line, sizeof(line), file)){
        // remove trailing newline
        line[strcspn(line, "\n")] = 0;

        // check for section start
        if (strncmp(line, "[", 1) == 0){
            if (inSection){
                // We've reached the next section — stop printing
                break;
            }
            if (strcmp(line, sectionHeader) == 0){
                inSection = 1;
                continue; // Skip printing the section header itself
            }
        }

        if(inSection){
            printf("%s\n", line);
        }
    }

    fclose(file);
}

void LevelUp(int* max)
// leveling up increased health maximum
{
    printf("Leveled up! Health maximum increased.\n");
    *max = *max + 1;
}

