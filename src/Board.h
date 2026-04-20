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

int GetBoardWidth(Board *board);//returns width of board

int GetBoardHeight(Board *board); //returns height of board

void PrintBoard(Board* board); //prints the board...

void MovePiece(Piece p, char start[], char end[], Board* b);

Piece* getPieceAt(int rank, int file, Board* b);

int SpaceIsAttacked(int rank, int file, Board *b);

char[] MakeCoordinateMove(int rank, int file);
#endif
