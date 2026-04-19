#include <stdio.h>
#include <stdlib.h>
#include "piece.h" // the header file

PieceType getPieceType(Piece *p){
	if(p == NULL){
		return -1
	}
	return p->type;
}

//function to get color of piece from pointer, for deterimining whos turn
Color getPieceColor(Piece *p){
	if(p == NULL){
		return -1;
	}
	return p->color;
}

//function to return posible moves for a piece
char* getMoveSet(Piece *p){
	if(p == NULL){
		return NULL;
	}
	return p->moveSet;
}

Piece storePiece(Piece piece){
	Piece newPiece;
	newPiece.type = piece.type;
	newPiece.color = piece.color;
	newPiece.moveSet = piece.moveSet;
	return newPiece;
}

