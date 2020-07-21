/*******************************************************************
* Project: Lab1 - A
* Author: Marcus Giarrusso
* Student ID:
* Semester: Oswego Fall 2017
* Course: Csc322 - Systems Programming
* Section: 800
* Date: 09/21/17
********************************************************************/

———————————
Description
———————————

In this first lab, we will develop a system program which provides four basic mathematical commands using C language. It will be a system program, in which user starts the program, enter commands, see the desired result, and finishes it if he or she wants to quit. Each command presents an operator, and requires one, two, or zero operands as parameters. For example - when a user enters "sum 4 2", the program returns the result "6" on the next line. 

Combinations of commands user can enter: operator operand operand
	     				 operator operand
	   			         command

————————
Commands
————————

sum : summation of parameters 				[Example - (sum 4 2) calculates 4 + 2]
mul : multiplication of parameters 			[Example - (mul 4 2) calculates 4 * 2]
sub : subtraction of parameters 			[Example - (sub 4 2) calculates 4 - 2]
div : divides the first parameter by the second 	[Example - (div 4 2) calculates 4 / 2]
col : finding collate conjecture of parameter 		[Example - (col 8) calculates 8 4 2 1]
bye : ends / terminates program 			[Example - (bye)]

——————————
Exceptions
——————————

The program must handle exceptions listed:

operator operand operand operand : "Too many operands, only two required"
operand operand operator         : "Incorrect"
operand operator operand	 : "Incorrect"
operator operand char(a-z)	 : "Operands must be numeric"
div operand zero		 : "Cannot divide by 0"
col char(a-z) operand		 : "Col needs only single numeric operand"

————————————
Run in Linux
————————————

gcc -o [name] fileName.c
./[name]
