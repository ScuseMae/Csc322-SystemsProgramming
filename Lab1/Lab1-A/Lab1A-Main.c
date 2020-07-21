#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void parseInput(char *input, char *opX, char *opY);
void sum(char *opX, char *opY);
void mul(char *opX, char *opY);
void sub(char *opX, char *opY);
void divs(char *opX, char *opY);
void col(char *opX, char *opY);
void bye(int x);
void stringCompare(char *input);

int main()
{
    char input[80];
    const char index[16] = " ";
    char *cmd, *opX, *opY, *opExtra;
    
    while (1)
    {
        printf("\n***********************************************\n");
        printf("*                Welcome!                     *");
        printf("\n***********************************************\n");
        printf("cmdPrompt>$ ");
        fgets(input, 80, stdin);
        
        cmd = strtok(input, index);
        opX = strtok(NULL, index);
        opY = strtok(NULL, index);
        opExtra = strtok(NULL, index);
        
        if (opExtra != NULL && opExtra > 0)
        {
            printf("Too many operands, only two required. \n");
        }
        else if (atoi(cmd) != 0)
        {
            printf("Incorrect \n");
        }
        else if (strlen(cmd) > 5)
        {
            if (strcmp("compare", cmd) == 0)
            {
                parseInput(cmd, opX, opY);
            }
            else
            {
                printf("Command has too many characters, all operators are 3 character words \n");
            }
        }
        else if (strcmp("bye\n", cmd) == 0 && opX == NULL && opY == NULL)
        {
            bye(0);
        }
        else
        {
            parseInput(cmd, opX, opY);
        }
    }
    
    return 0;
}

void parseInput(char *input, char *opX, char *opY)
{
    if (strcmp("sum", input) == 0)
    {
        sum(opX, opY);
    }
    else if (strcmp("mul", input) == 0)
    {
        mul(opX, opY);
    }
    else if (strcmp("sub", input) == 0)
    {
        sub(opX, opY);
    }
    else if (strcmp("div", input) == 0)
    {
        divs(opX, opY);
    }
    else if (strcmp("compare", input) == 0)
    {
        stringCompare(input);
    }
    else if(strcmp("col", input) == 0)
    {
        if (opX != NULL && opY == NULL)
        {
            col(opX, NULL);
        }
        else
        {
            printf("Col needs only single numeric operand \n");
        }
    }
    else
    {
        printf("Command not recognized, try again \n");
    }
}

void sum(char *opX, char *opY)
{
    if ((*opX >= 'a' && *opX <= 'z') || (*opY >= 'a' && *opY <= 'z'))
    {
        printf("Operands must be numeric \n");
    }
    else
    {
        int result;
        result = atoi(opX) + atoi(opY);
        printf("%i \n", result);
    }
}

void mul(char *opX, char *opY)
{
    if ((*opX >= 'a' && *opX <= 'z') || (*opY >= 'a' && *opY <= 'z'))
    {
        printf("Operands must be numeric \n");
    }
    else
    {
        int result;
        result = atoi(opX) * atoi(opY);
        printf("%i \n", result);
    }
}

void sub(char *opX, char *opY)
{
    if ((*opX >= 'a' && *opX <= 'z') || (*opY >= 'a' && *opY <= 'z'))
    {
        printf("Operands must be numeric \n");
    }
    else
    {
        int result;
        result = atoi(opX) - atoi(opY);
        printf("%i \n", result);
    }
}

void divs(char *opX, char *opY)
{
    if ((*opX >= 'a' && *opX <= 'z') || (*opY >= 'a' && *opY <= 'z'))
    {
        printf("Operands must be numeric \n");
    }
    else if (atoi(opY) == 0)
    {
        printf("Cannot divide by 0 \n");
    }
    else
    {
        float result;
        result = (float)atoi(opX) / (float)atoi(opY);
        printf("%f \n", result);
    }
}

void col(char *opX, char *opY)
{
    int result = atoi(opX);
    
    while (result > 1)
    {
        printf("%i ", result);
        
        if (result % 2 == 0)
        {
            result = result / 2;
        }
        else
        {
            result = (result * 3) + 1;
        }
    }
    
    printf("%i \n", 1);
}

void stringCompare(char *input)
{
    printf("Input String: %i \n", input); //Fix Warning
}

void bye(int x)
{
    printf("GoodBye \n");
    exit(x);
}
