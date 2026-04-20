#ifndef RULES_H
#define RULES_H

#include "Piece.h"
#include "Space.h"
#include "Board.h"

int checkStraightPathClear(char start[], char end[]);


int IllegalMoveCheck(Piece p, char start[], char end[], Board* b);
int IsCheck(Board *b, Color color);
int IsCheckamte(Board *b, Color color);
int IsDraw(Board *b);

#endif
