#include "Space.h"
#include <stddef.h>

void initSpace(Space *space, int row, int col){
	space->row = row;
	space->col = col;
	space->piece = NULL;

	if((row+col) % 2 == 0)
		space->color = WhiteSpace;
	else
		space->color = BlackSpace;
}

void getCoordinate(Space *space, char coord[]){
	coord[0] = 'A' + space->col;
	coord[1] = '1' + space->row;
	coord[2] = '\0';
}

Piece *getPiece(Space *space){
	return space->piece;
}

SpaceColor getColor(Space *space){
	return space->color;
}

void setPiece(Space *space, Piece *piece){
	space->piece = piece;
}
