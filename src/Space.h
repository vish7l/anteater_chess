#ifndef SPACE_H
#define SPACE_H


typedef enum{
	WhiteSpace, BlackSpace
} SpaceColor;

typedef struct{
	int row;
	int col;
	SpaceColor color;
	Piece *piece;
} Space;

void initSpace(Space *space, int row, int col);
void getCoordinate(Space *space, char coord[]);
Piece *getPiece(Space *space);
SpaceColor getColor(Space *space);
void setPiece(Space *space, Piece *piece);

#endif
