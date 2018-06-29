#include "LPC17xx.H"
#include "Keypad.H"
#include "GLCD.h"
#include "LPC1768_utility.h"

uint8_t array[9] = {1,2,3,4,5,6,7,8,9};		// array for 3x3 entries
uint8_t count = 0;		// play count

void changeTurn(int *turn)		// ASCII code of Player O is 79 and Player X is 88
{
	if(*turn == 79)		// change turn to PLAYER X
		{
			*turn = 88;
		}
		else if(*turn == 88)		// change turn to PLAYER O
			{
				*turn = 79;
			}
}

void printOX(int input, int x, int y, int *turn)		// print O and X at (x,y) coordinates
{
	if(array[input-1] == 79 || array[input-1] == 88 )		// if the array already has O or X (TO PREVENT DUPLICATE ENTRIES)
		{
			GLCD_displayStringLn(Line1, "*     TRY AGAIN    *");
			Delay(SEC_1);
		}
		else		// there are empty entries
			{
				array[input-1] = *turn;		// input O or X
				GLCD_displayChar(x, y, *turn);		// print O and X at (x,y) coordinates
				changeTurn(&*turn);
				count++;		// increment the count
			}
}

void inputArray(int *turn)		// Input values(O or X) to the array
{
	int input = 0;
	uint8_t Keypad_Value = 0;
	while(1){
		Keypad_Value = Keypad('C');
		if(Keypad_Value == 1){
			input = 1;
			printOX(1, 60, 70, &*turn);		// print O or X at the 1st entry
			break;
		}
		else if(Keypad_Value == 2){
			input = 2;
			printOX(2, 150, 70, &*turn);		// print O or X at the 2nd entry
			break;
		}
		else if(Keypad_Value == 3){
			input = 3;
			printOX(3, 245, 70, &*turn);		// print O or X at the 3nd entry
			break;
		}
		else if(Keypad_Value == 5){
			input = 4;
			printOX(4, 60, 125, &*turn);		// print O or X at the 4th entry
			break;
		}else if(Keypad_Value == 6){
			input = 5;
			printOX(5, 150, 125, &*turn);		// print O or X at the 5th entry
			break;
		}else if(Keypad_Value == 7){
			input = 6;
			printOX(6, 245, 125, &*turn);		// print O or X at the 6th entry
			break;
		}else if(Keypad_Value == 9){
			input = 7;
			printOX(7, 60, 180, &*turn);		// print O or X at the 7th entry
			break;
		}else if(Keypad_Value == 10){
			input = 8;
			printOX(8, 150, 180, &*turn);		// print O or X at the 8th entry
			break;
		}else if(Keypad_Value == 11){
			input = 9;
			printOX(9, 245, 180, &*turn);		// print O or X at the 9th entry
			break;
		}
	}
	Delay(SEC_1/2);
}

void drawRect( int x0, int y0, int width, int height)		// the draw function for lines
{
	int i;
	int j;
	for(i=0; i<height; i++)
	{
		for(j=0; j<width; j++)
		{
			GLCD_putPixel(x0+j, y0+i);
		}
	}
}

void gamedIsPlay()		// GUI for Game Display
{
	GLCD_clear(Black);
	GLCD_setBackColor(Black);
	GLCD_setTextColor(White);
	GLCD_displayStringLn(Line0, "***  TIC TAC TOE ***");
	GLCD_displayStringLn(Line1, "*   Player O turn  *");
	GLCD_displayStringLn(Line2, "*                  *");
	GLCD_displayStringLn(Line3, "*                  *");
	GLCD_displayStringLn(Line4, "*                  *");
	GLCD_displayStringLn(Line5, "*                  *");
	GLCD_displayStringLn(Line6, "*                  *");
	GLCD_displayStringLn(Line7, "*                  *");
	GLCD_displayStringLn(Line8, "*                  *");
	GLCD_displayStringLn(Line9, "********************");
	drawRect(30, 100 , 260 , 5);		// draw lines
	drawRect(30, 160 , 260 , 5);		// draw lines
	drawRect(110, 60 , 5 , 150);		// draw lines
	drawRect(205, 60 , 5 , 150);		// draw lines
}

void intro()		// GUI for Intro Display
{
	GLCD_clear(Black);
	GLCD_setBackColor(Black);
	GLCD_setTextColor(White);
	GLCD_displayStringLn(Line0,"********************");
	GLCD_displayStringLn(Line1,"*                  *");
	GLCD_displayStringLn(Line2,"*                  *");
	GLCD_displayStringLn(Line3,"*    TIC TAC TOE   *");		// Game Name
	GLCD_displayStringLn(Line4,"*                  *");
	GLCD_displayStringLn(Line5,"*                  *");
    GLCD_displayStringLn(Line6,"*       BMHS       *");		// Project Team Name: BMHS("Byoung Mock Hyun Sang" which means BOTTLE NECK"
	GLCD_displayStringLn(Line7,"*                  *");
	GLCD_displayStringLn(Line8,"*                  *");
	GLCD_displayStringLn(Line9,"********************");
	Delay(SEC_2);
}

void checkWinner(int *winFlag, int *turn){		// Check who the winner is!
	int i;
		if(*turn == 88)		// when PLAYER X turn
			{
			GLCD_displayStringLn(Line1, "*   Player X turn  *");
			}
			else if(*turn == 79){		// when PLAYER O turn
				GLCD_displayStringLn(Line1, "*   Player O turn  *");
			}
		
		for(i=0; i<10;){		// Check horizontal lines
			if( (array[i] == array[i+1]) && (array[i+1] == array[i+2]) ){
				if(array[i] == 79){
					*winFlag = 1;
				}else if(array[i] == 88){
					*winFlag = 1;
				}
			}
			i += 3;
		}
		
		for(i=0; i<3;){		// Check vertical lines
			if( (array[i] == array[i+3]) && (array[i+3] == array[i+6]) ){
				if(array[i] == 79){
					*winFlag = 1;
				}else if(array[i] == 88){
					*winFlag = 1;
				}
			}
			i += 1;
		}
		
		if( (array[0] == array[4]) && (array[4] == array[8]) ){		// Check diagonal lines
			if(array[0] == 79){
				*winFlag = 1;
			}else if(array[0] == 88){
				*winFlag = 1;
			}
		}
		if( (array[2] == array[4]) && (array[4] == array[6]) ){		// Check diagonal lines
			if(array[2] == 79){
				*winFlag = 1;
			}else if (array[2] == 88){
				*winFlag = 1;
			}
		}
}

int main(void){
	int winFlag = 0;		// init the win flag as 0
    int turn = 79;		// init the turn variable as 79(Player O; the first turn)
	
	SystemInit();		// System Init
	EXT_IO_init();
	Keypad_DIR_Input();
	GLCD_init();
	
	intro();		// Intro Display
	gamedIsPlay();		// Game Display
	
	while(1){
		inputArray(&turn);
		checkWinner(&winFlag, &turn);		// Check who is the winner
		
		if(count == 9){		// if the entries are full
			break;		// Game End
		}
		if(winFlag == 1){		// if there is a winner
			break;		// Game End
		}
	}
	
	GLCD_clear(Black);
	changeTurn(&turn);
	
    if(winFlag == 0 )		// there are no winners; GAME DRAW
		{
			GLCD_displayStringLn(Line0, "********************");
			GLCD_displayStringLn(Line1, "*                  *");
			GLCD_displayStringLn(Line2, "*                  *");
			GLCD_displayStringLn(Line3, "*       DRAW       *");
			GLCD_displayStringLn(Line4, "*                  *");
			GLCD_displayStringLn(Line5, "*                  *");
			GLCD_displayStringLn(Line6, "*                  *");
			GLCD_displayStringLn(Line7, "*    Press reset   *");
			GLCD_displayStringLn(Line8, "*                  *");
			GLCD_displayStringLn(Line9, "********************");
    }
		else{		// there is the winner
			GLCD_displayStringLn(Line0, "********************");
			GLCD_displayStringLn(Line1, "*                  *");
			GLCD_displayStringLn(Line2, "*  CONGRATURATION  *");
			GLCD_displayStringLn(Line3, "*                  *");
			GLCD_displayStringLn(Line4, "*   Player   Win   *");
			GLCD_displayChar(173, Line4, turn);
			GLCD_displayStringLn(Line5, "*                  *");
			GLCD_displayStringLn(Line6, "*                  *");
			GLCD_displayStringLn(Line7, "*    Press reset   *");
			GLCD_displayStringLn(Line8, "*                  *");
			GLCD_displayStringLn(Line9, "********************");
		}
}
