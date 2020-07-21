/****************************************************************
* Project: Lab1 - B						
* Author: Marcus Giarrusso					
* Student ID:          						
* Semester: Oswego Spring 2018					
* Course: Csc322 - Systems Programming				
* Section: 800							
* Date: 02/16/18						
*****************************************************************/

************************
*     Description      *
************************

In this first lab, we will develop a program which includes two games using C. It must be an errorless program, in which user chooses a game, play it, and ends it anytime when he or she wants to quit. It should run on Linux machine at cs.oswego.edu. Once it is compiled and performed, it draws user to its own computing environment by showing prompt following the format: your_loginID> $. It will consist of 3 modes:
	
————————————————
I. Command_Mode
————————————————

This system program provides three basic commands shown in the below table. Each one is 4-character command, and the program runs a game or quits when a user correctly enters a command as seen in Figure 1. Misspelled command should be handled as an exception, and the program must show an error message. Note that program must be in running and shows the next prompt.

————————————————
II. FIME_Mode
————————————————

In the game FIME, you will find a number selected by a computer. First, the computer randomly chooses any number in the certain range of numbers. For simplicity, the minimum number is 1 and the maximum number will be assigned by you. In order to find the number, you will ask the computer by entering any number. Every trial of guess, computer answers in three different way according to your number:
	1) Greater than your_number
	2) Equal to your_number (Win)
	3) Less than your_number

————————————————
III. NUBA_Mode
————————————————

In NUBA mode, you are playing as a pitcher and trying to pitch three strikes. The difference between NUMA and baseball game is that you will play NUBA with 3 numbers! In NUBA, computer randomly chooses three distinct numbers from 1 to 9, and you guess the numbers. There are two main rules in playing baseball with numbers:
	1) If your_number is equal to computer in equal positions -> its a STRIKE
	2) If your_number is equal to computer but different positions -> its a BALL




************************
*       Commands       *
************************

—————————————
Command_Mode
—————————————
 • help: offers user additional help/instruction if stuck
 • fime: starts the Find-Me game
 • nuba: starts the Number-Baseball game
 • quit: allows user to exit the system program all together


—————————————
Find-Me_Mode
—————————————

 • difficulty : user can choose difficulty level 
	   [0]: a random number between 1 - 10
	   [1]: a random number between 1 - 100
	   [2]: a random number between 1 - 1000
	   [3]: a custom random number between 1 - (user choice)
 • guess      : user enters 1-digit number to guess computer random number [e.g. 5]
 • f_help     : gives user instructions to game
 • bye        : allows user to exit game & return to Command_Mode
 • y/n	      : allows user to replay same game or exit to Command_Mode


—————————————
Num-Ball_Mode
—————————————

 • pitch  : user enters 3 numbers between 1 - 9 [e.g. 1 2 3]
 • n_help : gives user instructions to game
 • bye	: allows user to exit game & return to Command_Mode
 • y/n	: allows user to replay same game or exit to Command_Mode


************************
*      Exceptions      *
************************

—————————————
Command_Mode
—————————————

 • Misspelled/command other than: help | fime | nuba | quit

—————————————
Find-Me_Mode
—————————————

 • entering non-numeric values (alphabet characters)
 • entering numbers out of 1 to the maximum number
 • entering more than one number

—————————————
Num-Ball_Mode
—————————————
 • entering non-numeric values (alphabet characters)
 • entering numbers out of 1 to 9
 • entering more than or less than 3 numbers


************************
*     Run in Linux     *
************************

 • gcc -o [name] fileName.c
 • ./[name]
