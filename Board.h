#ifndef BOARD_H
#define BOARD_H

#include "Piece.h"
#include "Space.h"

/* the movie structure */
typedef struct {
	Space board[8][10];
} Board;

Board* CreateBoard(void); //creates the board

void DeleteBoard(Board* board); //deletes the board

void GetBoardWidth(Board *board);//returns width of board

void GetBoardHeight(Board *board); //returns height of board

void PrintBoard(Board* board); //prints the board...

int MovePiece(Piece p, char start[], char end[], Board* b);
//returns 1 if piece was moved returns 0 if piece cant move because its illegal
#endif
