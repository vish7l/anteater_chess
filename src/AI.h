#ifndef AI_H
#define AI_H

#include "Board.h"
#include "Piece.h"

/*
This is the main AI function for the game engine.
it evaluates the board and returns a string representing the coordinate for the chosen move
random for right now
for example Bf3, for bishop to f3

the paramaters include:
    - board: the current state of the board
    - the color of the ai

returns null if no legal moves exist

*/

char* CalculateMove(Board *board, Color color);

#endif
