#ifndef PERMUT_H
#define PERMUT_H

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>  
#include<stdlib.h>  
#include<string.h>


#define ABC_WO_UC_CHARS_NUM 26
#define ABC_W_UC_CHARS_NUM ABC_WO_UC_CHARS_NUM * 2

int getCharMatchingInd(char ch);
int printPermutations(FILE* pFile, const char* fileName, const char* searchStr);

#endif
