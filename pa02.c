/*=============================================================================
| Assignment: pa02 - Calculating an 8, 16, or 32 bit
| checksum on an ASCII input file
|
| Author: Axel Alvarado
| Language: c
|
| To Compile: gcc -o pa02 pa02.c
|
| To Execute: c -> ./pa02 inputFile.txt 8
| where inputFile.txt is an ASCII input file
| and the number 8 could also be 16 or 32
| which are the valid checksum sizes, all
| other values are rejected with an error message
| and program termination
|
| Note: All input files are simple 8 bit ASCII input
|
| Class: CIS3360 - Security in Computing - Spring 2023
| Instructor: McAlpin
| Due Date: April 23, 2023
|
+=============================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

void output(char array[], int size, unsigned int answer, int checksum);

int main(int argc, char **argv)
{
    char array[10000];
    int size = 0;
    char *firstFile = argv[1];
    char *bit = argv[2];

    FILE *file = fopen(firstFile, "r");

    // Opening the First File
    if (file == NULL)
    {
        printf("Could not open File\n");
        return 1;
    }
    else
    {
        char c;
        int i = 0;

        while ((c = fgetc(file)) != EOF)
        {
            array[i] = c;
            size++;
            i++;
        }
        fclose(file);
    }

    // Making sure the correct checksum is inputted
    int checksum = atoi(bit);

    if (checksum == 8 || checksum == 16 || checksum == 32)
    {
    }
    else
    {
        fprintf(stderr, "Valid checksum sizes are 8, 16, or 32\n");
        return 1;
    }
  
    int num = checksum / 8;

    unsigned int answer = 0;
    int remainder = size % num;

    while((size % num) != 0)
    {
        array[size++] = 'X';
    }

    for (int x = 0; x < size; x += num)
    {
        int current = 0;
        for (int i = 0; i < num; i++)
        {
            current = current << 8;
            current += array[x+i];
        }
        answer += current;
    }

    int x = 1;
    for (int j = 0; j < 64; j++)
    {
        if(j >= checksum)
        {
            if((answer & x) != 0)
            {
                answer = answer ^ x;
            }
        }
        x *= 2;
    }

    output(array, size, answer, checksum);
}

void output(char array[], int size, unsigned int answer, int checksum)
{
    for (int j = 0; j < size; j++)
    {
        if (j % 80 == 0)
        {
            printf("\n");
        }
        printf("%c", array[j]);
    }

    printf("\n%2d bit checksum is %8x for all %4d chars\n",checksum, answer, size);
}

/*=============================================================================
| I Axel Alvarado (ax682172) affirm that this program is
| entirely my own work and that I have neither developed my code together with
| any another person, nor copied any code from any other person, nor permitted
| my code to be copied or otherwise used by any other person, nor have I
| copied, modified, or otherwise used programs created by others. I acknowledge
| that any violation of the above terms will be treated as academic dishonesty.
+============================================================================*/