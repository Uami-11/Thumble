#ifndef FUNCTIONS_H
#define FUNCTIONS_H

// functions function
void Heal(int full, int* health);
int RemoveValue(int * arr, int removeVal, int * size);
void PrintText(const char *filename, const char *sectionKey);
void LevelUp(int* max);
void PrintHealth(int health);
void BattleScreen(int PlayerHealth, int EnemyHealth, char PlayerName[], char EnemyName[]);
int BattleMode(int *PlayerHealth, int EnemyHealth, int PlayerPower, int EnemyPower, char PlayerName[], char EnemyName[]);

// utils functions
void InputString(char * TheString, int size);
int ChoiceInput(int);
void Akward();
void Sleeps(int mili);
void ClearScreen();

#endif