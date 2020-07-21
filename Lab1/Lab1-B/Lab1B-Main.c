#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <stdbool.h>

void fime(void);
void nuba(void);
int randomizer(int gameID, int difficultyLevel);
int comparePitches(int ballNumber, int userPitch, int computerPitch);
void quit(int programQuitValue);

char input[275];
char fimeInput[275];
char customNumber[275];
char fime_Guess[275];
char nubaInput[275];
const char tokenIndex[16] = " ";
char *commandInput, *fime_Difficulty, *nuba_PitchOne, *nuba_PitchTwo, *nuba_PitchThree, *nuba_ExtraInputError;

int nuba_Computer_Rand1, nuba_Computer_Rand2, nuba_Computer_Rand3;
int max_Num = 0;
int randomizerCall = 0;
int fimeScore = 0;
int nuba_Innings = 0;

int compareNumbers_TrueFalse = false;
int result1 = false;
int result2 = false;
int result3 = false;


int main(int argc, const char * argv[])
{
    while (1)
    {
        printf("\n***********************************************\n");
        printf("*                Welcome!                     *");
        printf("\n***********************************************\n");
        printf("cmdPrompt>$ ");
        fgets(input, sizeof(input), stdin);
        
        commandInput = strtok(input, tokenIndex);
        
        if (strcmp("fime\n", commandInput) == 0)
        {
            fime();
        }
        else if (strcmp("nuba\n", commandInput) == 0)
        {
            nuba();
        }
        else if (strcmp("help\n", commandInput) == 0)
        {
            printf("\n***********************************************\n");
            printf("        ~ About System Program ~\n");
            printf("\nYou are in Command_Mode... \n");
            printf("\nPossible Commands: \n");
            printf("  - fime : will take you to Find-Me game \n");
            printf("  - nuba : will take you to Number-Baseball game \n");
            printf("  - help : will take you to, well.. this screen \n");
            printf("  - quit : will exit system program \n");
            printf("\n***********************************************\n");
        }
        else if (strcmp("quit\n", commandInput) == 0)
        {
            quit(0);
        }
        else
        {
            printf("Command Not Recognized. Try Again or Enter 'help' \n");
        }
    }
    return 0;
}

void fime()
{
    max_Num = 0;
    fimeScore = 0;
    printf("\n***********************************************\n");
    printf("      ~ Welcome to Find-Me Game ~ \n");
    printf("\n- 1. Choose difficulty \n- 2. Computer picks number within that range \n- 3. Guess that random number\n");
    printf("\n- Easy: 1 - 10 \n- Medium: 1 - 100 \n- Hard: 1 - 1000 \n- Custom: 1 - your_Choice\n");
    printf("\n- Enter 'bye' to exit game \n");
    printf("***********************************************\n");
    
    printf("\nDifficulty level [easy(0) medium(1) hard(2) custom(3)]: ");
    fgets(fimeInput, sizeof(fimeInput), stdin);
    fime_Difficulty = strtok(fimeInput, tokenIndex);
    
    randomizerCall = randomizer(1,atoi(fime_Difficulty));

    if ((int)atoi(fime_Difficulty) == 0)
    {
        max_Num = 10;
    }
    else if ((int)atoi(fime_Difficulty) == 1)
    {
        max_Num = 100;
    }
    else if ((int)atoi(fime_Difficulty) == 2)
    {
        max_Num = 1000;
    }
    else if ((int)atoi(fime_Difficulty) == 3)
    {
        max_Num = (int)atoi(customNumber);
    }
    else
    {
        max_Num = 100000;
    }
    
    while (1)
    {
        printf("Guess : ");
        fgets(fime_Guess, sizeof(fime_Guess), stdin);
        fimeScore++;

        if (strcmp("bye\n", fime_Guess) == 0)
        {
            printf("Thanks for playing! \n");
            break;
        }
        else if (strcmp("f_help\n", fime_Guess) == 0)
        {
            printf("\n***********************************************\n");
            printf("    ~ FIND-ME INSTRUCTIONS ~\n");
            printf("\n 1. Choose difficulty \n 2. Computer picks number within that range \n 3. Guess that random number");
            printf("\n***********************************************\n");
        }
        if ((*fime_Guess>='a'&& *fime_Guess<= 'z'))
        {
            printf("[Error] Guesses must be numeric. \n");
            fimeScore--;
        }
        else if ((int) atoi(fime_Guess) <= 0 || (int) atoi(fime_Guess) > max_Num)
        {
            printf("[Error] Commands must be between 1 - %d \n", max_Num);
            fimeScore--;
        }
        else if ((int) atoi(fime_Guess) == randomizerCall)
        {
            printf("COngrats! \n");
            printf("You got that in %d attempts \n", fimeScore);
            printf("Would you like to play Find-Me again? (y/n) \n");
            fgets(fimeInput, sizeof(fimeInput), stdin);
            
            if (strcmp("y\n", fimeInput) == 0)
            {
                fime();
            }
            else if (strcmp("n\n", fimeInput) == 0)
            {
                break;
            }
            else
            {
                printf("[Error] Invalid command, enter 'fime' to play again. \n");
            }
            break;
        }
        else if ((int) atoi(fime_Guess) > randomizerCall)
        {
            printf("[Attempt %d] Less Than %d \n", fimeScore, (int) atoi(fime_Guess));
        }
        else if ((int) atoi(fime_Guess) < randomizerCall)
        {
            printf("[Attempt %d] Greater Than %d \n", fimeScore, (int) atoi(fime_Guess));
        }
        else
        {
            printf("[Error] Command Not Recognized. Try Again or Enter 'f_help' \n");
        }
    }
}

void nuba()
{
    nuba_Innings = 0;
    printf("\n*********************************************************\n");
    printf("         ~ Welcome to Number-Baseball Game ~ \n");
    printf("\n- Computer generates 3 random numbers 1 - 9 [e.g. 3 5 9] \n");
    printf("- Match your 3 numbers to win\n");
    printf("\nRules:\n");
    printf("- your_number = computer in same positions: STRIKE \n");
    printf("- your_number = computer in different positions: BALL \n");
    printf("- 9 innings: Your OUT \n");
    printf("- 3 strikes: You WIN \n");
    printf("\nEnter 'bye' to exit game \n");
    printf("*********************************************************\n");
    nuba_Computer_Rand1 = randomizer(2, 0);
    nuba_Computer_Rand2 = randomizer(2, 1);
    nuba_Computer_Rand3 = randomizer(2, 2);

    printf("\nComputer has set 3 random number-balls between 1 - 9 \n");

    while (1)
    {
        printf("Pitch your 3 number-balls: ");
        fgets(nubaInput, sizeof(nubaInput), stdin);
        
        nuba_PitchOne = strtok(nubaInput, tokenIndex);
        nuba_PitchTwo = strtok(NULL, tokenIndex);
        nuba_PitchThree = strtok(NULL, tokenIndex);
        nuba_ExtraInputError = strtok(NULL, tokenIndex);
        nuba_Innings++;
        
        if ((*nuba_PitchOne>='a'&& *nuba_PitchOne<= 'z')||(*nuba_PitchTwo>='a'&&*nuba_PitchTwo<= 'z')||(*nuba_PitchThree >= 'a'&& *nuba_PitchThree<='z'))
        {
            if (strcmp("bye\n", nubaInput) == 0)
            {
                printf("Thank you for playing the Number-Baseball Game! \n");
                break;
            }
            else
            {
                printf("[Error] Pitches must be 3 numbers between 1 - 9, No characters. \n");
                nuba_Innings--;
                continue;
            }
        }
        else if ((int)atoi(nuba_PitchOne) == 0 || (int)atoi(nuba_PitchTwo) == 0 || (int)atoi(nuba_PitchThree) == 0 ||
                 (int)atoi(nuba_PitchOne) >= 10 || (int)atoi(nuba_PitchTwo) >= 10 || (int)atoi(nuba_PitchThree) >= 10)
        {
            printf("[Error] Numbers cannot be 0 or below nor 10 or above, only 1 - 9 \n");
            nuba_Innings--;
            continue;
        }
        else if (nuba_Innings > 9)
        {
            printf("[%d Innings] Sorry, you lose \n", nuba_Innings);
            printf("Would you like to play Number-Baseball again? (y/n) \n");
            fgets(nubaInput, sizeof(nubaInput), stdin);
            
            if (strcmp("y\n", nubaInput) == 0)
            {
                nuba();
            }
            else if (strcmp("n\n", nubaInput) == 0)
            {
                break;
            }
            else
            {
                printf("[Error] Invalid command, enter 'nuba' to play again. \n");
            }
            break;
        }
        else
        {
            result1 = comparePitches(1, (int)atoi(nuba_PitchOne),nuba_Computer_Rand1);
            result2 = comparePitches(2, (int)atoi(nuba_PitchTwo),nuba_Computer_Rand2);
            result3 = comparePitches(3, (int)atoi(nuba_PitchThree),nuba_Computer_Rand3);
        }
        
        if (strcmp("bye\n", nubaInput) == 0)
        {
            printf("Thank you for playing the Number-Baseball Game! \n");
            break;
        }
        else if (nuba_ExtraInputError != NULL && nuba_ExtraInputError > 0)
        {
            printf("[Error] Too many Number-Balls, only 3 required. \n");
            nuba_Innings--;
        }
        else if (result1 == true && result2 == true && result3 == true)
        {
            printf("[%d Innings] 3 Strikes! You Win in %d inning(s) \n", nuba_Innings, nuba_Innings);
            printf("Would you like to play Number-Baseball again? (y/n) \n");
            fgets(nubaInput, sizeof(nubaInput), stdin);
            
            if (strcmp("y\n", nubaInput) == 0)
            {
                nuba();
            }
            else if (strcmp("n\n", nubaInput) == 0)
            {
                break;
            }
            else
            {
                printf("[Error] Invalid command, enter 'nuba' to play again. \n");
            }
            break;
        }
        else if (result1 == true && result2 == false && result3 == false)
        {
            printf("[%d Inning] Strike on ball_1 \n", nuba_Innings);
        }
        else if (result1 == true && result2 == true && result3 == false)
        {
            printf("[%d Inning] Strike on ball_1 & ball_2 \n", nuba_Innings);
        }
        else if (result1 == true && result2 == false && result3 == true)
        {
            printf("[%d Inning] Strike on ball_1 & ball_3 \n", nuba_Innings);
        }
        else if (result1 == false && result2 == true && result3 == false)
        {
            printf("[%d Inning] Strike on ball_2 \n", nuba_Innings);
        }
        else if (result1 == false && result2 == true && result3 == true)
        {
            printf("[%d Inning] Strike on ball_2 & ball_3 \n", nuba_Innings);
        }
        else if (result1 == false && result2 == false && result3 == true)
        {
            printf("[%d Inning] Strike on ball_3 \n", nuba_Innings);
        }
        else if (result1 == false && result2 == false && result3 == false)
        {
            if ((int)atoi(nuba_PitchOne) == nuba_Computer_Rand2 || (int)atoi(nuba_PitchOne) == nuba_Computer_Rand3 ||
                (int)atoi(nuba_PitchTwo) == nuba_Computer_Rand1 || (int)atoi(nuba_PitchTwo) == nuba_Computer_Rand3 ||
                (int)atoi(nuba_PitchThree) == nuba_Computer_Rand1 || (int)atoi(nuba_PitchThree) == nuba_Computer_Rand2)
            {
                printf("[%d Inning] BALL -> o \n", nuba_Innings);
            }
            else if ((int)atoi(nuba_PitchOne) != nuba_Computer_Rand2 || (int)atoi(nuba_PitchOne) != nuba_Computer_Rand3 ||
                     (int)atoi(nuba_PitchTwo) != nuba_Computer_Rand1 || (int)atoi(nuba_PitchTwo) != nuba_Computer_Rand3 ||
                     (int)atoi(nuba_PitchThree) != nuba_Computer_Rand1 || (int)atoi(nuba_PitchThree) != nuba_Computer_Rand2)
            {
                printf("[%d Inning] Swing and a Miss \n", nuba_Innings);
            }
        }
        else
        {
            printf("[Error] Invalid...\n");
            nuba_Innings--;
        }
    }
}

int randomizer(int gameID, int difficultyLevel)
{
    srand((unsigned int)time(NULL));
    int sRandValue1 = rand();
    int sRandValue2 = rand();
    int sRandValue3 = rand();

    switch (gameID)
    {
        case 1 :
            switch (difficultyLevel)
            {
                case 0 :
                    difficultyLevel = 1 + rand() % 10;
                    break;
                case 1 :
                    difficultyLevel = 1 + rand() % 100;
                    break;
                case 2 :
                    difficultyLevel = 1 + rand() % 1000;
                    break;
                case 3 :
                    printf("Choose maximum number: ");
                    fgets(customNumber, sizeof(customNumber), stdin);
                    difficultyLevel = 1 + rand() % (int)atoi(customNumber);
                    break;
                default :
                    printf("Difficulty invalid. \n");
                    break;
            }
            break;
        case 2 :
            switch (difficultyLevel)
            {
                case 0 :
                    srand(sRandValue1);
                    difficultyLevel = 1 + rand() % 9;
                    break;
                case 1 :
                    srand(sRandValue2);
                    difficultyLevel = 1 + rand() % 9;
                    break;
                case 2 :
                    srand(sRandValue3);
                    difficultyLevel = 1 + rand() % 9;
                    break;
                default :
                    printf("Nuba balls not randomized... \n");
                    break;
            }
            break;
        default:
            printf("Difficulty level invalid. \n");
            break;
    }
    return difficultyLevel;
}

int comparePitches(int ballNumber, int userPitch, int computerPitch)
{
    compareNumbers_TrueFalse = false;
    
    switch (ballNumber)
    {
        case 1 :
            if (userPitch == computerPitch)
            {
                compareNumbers_TrueFalse = true;
            }
            else if (userPitch != computerPitch)
            {
                compareNumbers_TrueFalse = false;
            }
            break;
        case 2 :
            if (userPitch == computerPitch)
            {
                compareNumbers_TrueFalse = true;
            }
            else if (userPitch != computerPitch)
            {
                compareNumbers_TrueFalse = false;
            }
            break;
        case 3 :
            if (userPitch == computerPitch)
            {
                compareNumbers_TrueFalse = true;
            }
            else if (userPitch != computerPitch)
            {
                compareNumbers_TrueFalse = false;
            }
            break;
        default:
            printf("Something went wrong...\n");
            break;
    }
    return compareNumbers_TrueFalse;
}

void quit(int programQuitValue)
{
    printf("GoodBye! \n");
    exit(programQuitValue);
}
