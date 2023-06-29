#include "permut.h"

 /*gets a char and returns its matching index in the frequency array. */
int getCharMatchingInd(char ch)
{
	if (ch >= 'a' && ch <= 'z')
	{
		return ch - 'a';
	}
	else if (ch >= 'A' && ch <= 'Z')
	{
		return ch - 'A' + ABC_WO_UC_CHARS_NUM;
	}

	return -1;
}


 /*gets a pointer to an opened text file and a string (key).
 	prints all of the substrings that are in the text file
 	that are a permutatation of that key. */
 
 /*algorithm: we create a helper array that holds how many times each letter (english letter. upper or lower) 
	appears in the key.  we then go over the text file one char at a time and 
 	if we see that the current char is one of the key's letters (by using the helper array) 
 	- we go and check whether the next n-1 letters (n is key's length) of the text are one of the key's letters as well.
 	this is done by decrementing the helper array's cells' values according to the letter we see in the text
 	(for each char we find its matching index in the helper array).
 	if the  helper array's values are all 0 then this means we saw a permutation of the key in the text file.
 	in such case we print it. else (this wasn't a valid permutation), we go back to the letter that started
 	the check in order to not miss permutations that start after that letter.
 	if the text file is empty, then error is printed.
 	if no permutations of were found, a message is displayed to the user. */
int printPermutations(FILE* pFile, const char* fileName, const char* searchStr)
{
	int i;
	int ch;
	int noPermsFound = 1;
	int isFileEmpty = 0;
	int isGoodPerm;
	int curPermCheckFreq[ABC_W_UC_CHARS_NUM];
	int searchStrFreq[ABC_W_UC_CHARS_NUM];
	int matchingInd;
	char* curPermInText;
	int curPermInTextInd;
	int searchStrLen;
	fpos_t curPermCheckStartPos;

	for (i = 0; i < ABC_W_UC_CHARS_NUM; i++)
	{
		searchStrFreq[i] = 0;
	}

	searchStrLen = strlen(searchStr);
	for (i = 0; i < searchStrLen; i++)
	{
		matchingInd = getCharMatchingInd(searchStr[i]);
		if (matchingInd != -1)
		{
			searchStrFreq[matchingInd]++;
		}
	}

	while ((ch = fgetc(pFile)) != -1)
	{
		isFileEmpty = 1;
		matchingInd = getCharMatchingInd(ch);
		if (matchingInd != -1 && searchStrFreq[matchingInd] > 0)
		{
			fgetpos(pFile, &curPermCheckStartPos);
			curPermInText = calloc((searchStrLen + 1), sizeof(char));
			curPermInTextInd = 0;
			curPermInText[curPermInTextInd] = ch;
			curPermInTextInd++;

			for (i = 0; i < ABC_W_UC_CHARS_NUM; i++)
			{
				curPermCheckFreq[i] = searchStrFreq[i];
			}

			curPermCheckFreq[matchingInd]--;

			for (i = 0; i < searchStrLen - 1 && (ch = fgetc(pFile)) != EOF; i++)
			{
				matchingInd = getCharMatchingInd(ch);
				if (matchingInd != -1)
				{
					curPermInText[curPermInTextInd] = ch;
					curPermInTextInd++;
					curPermCheckFreq[matchingInd]--;
				}
			}
			curPermInText[curPermInTextInd] = '\0';

			isGoodPerm = 1;
			for (i = 0; i < ABC_W_UC_CHARS_NUM; i++)
			{
				if (curPermCheckFreq[i] != 0)
				{
					isGoodPerm = 0;
					break;
				}
			}

			if (isGoodPerm == 1)
			{
				noPermsFound = 0;
				printf("%s\n", curPermInText);
			}
			else
			{
				fsetpos(pFile, &curPermCheckStartPos);
			}

			free(curPermInText);
		}
	}
	if (isFileEmpty == 0)
	{
		fprintf(stderr, "text file %s was empty\n", fileName);
		return 1;
	}
	if (noPermsFound == 1)
	{
		printf("no permutations of %s were found\n", searchStr);
	}
	return 0;
}


 /*program that gets the name of a text file and a search string (key) in the main's areguments.
	if the argumrnts are valid, it opens the text file and calls the printPermutations function
	we prints all of the substrings that are in the text file
	that are a permutatation of that key. */
int main(int argc, char* argv[])
{
	const char* fileName;
	const char* searchStr;
	int res;
	FILE* pFile;

	if (argc != 3)
	{
		fprintf(stderr, "error. expected 3 arguments. got %d arguments\n", argc);
		return 1;
	}

	fileName = argv[1];
	searchStr = argv[2];

	pFile = fopen(fileName, "r");
	if (pFile == NULL)
	{
		fprintf(stderr, "error opening file %s\n", fileName);
		return 1;
	}

	res = printPermutations(pFile, fileName, searchStr);
	fclose(pFile);
	return res;
}

