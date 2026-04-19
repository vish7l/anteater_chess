#ifndef BOARD_H
#define BOARD_H

#include "Piece.h"
#include "Space.h"

/* the movie structure */
typedef struct {
	Space *board[8][10];
	int height;
	int width;

} Board;

Board* CreateBoard(void); //creates the board

void DeleteBoard(Board* board); //deletes the board

void GetBoardWidth(Board *board);//returns width of board

void GetBoardHeight(Board *board); //returns height of board

void PrintBoard(Board* board); //prints the board...

void MovePiece(Piece p, char start[], char end[], Board* b);
#endif
