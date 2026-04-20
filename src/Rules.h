#ifndef RULES_H
#define RULES_H

#include "Piece.h"
#include "Space.h"
#include "Board.h"

<<<<<<< HEAD
=======
int checkStraightPathClear(char start[], char end[]);


>>>>>>> ea315946a453cd8f7ab3743777c17010542fcf4e
int IllegalMoveCheck(Piece p, char start[], char end[], Board* b);
int IsCheck(Board *b, Color color);
int IsCheckamte(Board *b, Color color);
int IsDraw(Board *b);

#endif
