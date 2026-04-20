#ifndef PIECE_H
#define PIECE_H

//first the enum definitions:

//defines the 2 colors
typedef enum{
    Black,
    White
}Color;

//defines the all 7 of the piecetypes
typedef enum{PAWN, ANTEATER, KING, QUEEN, ROOK, BISHOP, KNIGHT} PieceType;

//defines the 8 rows
<<<<<<< HEAD
typedef enum{R1, R2, R3, R4, R5, R6, R7, R8} Rank;
=======
typedef enum{
    1,
    2,
    3,
    4,
    5,
    6,
    7,
    8
}Rank;
>>>>>>> 94cf34dbbf4d4c68b2c445fd6946d2e50f627748

//defines the 10 columns
typedef enum{A, B, C, D, E, F, G, H, I, J} File;

//Next the structs

//stores the identity and the behavior of the piece
typedef struct{
    Color color;
    PieceType type;
} Piece;

PieceType getPieceType(Piece *p);
Color getPieceColor(Piece *p);
Piece storePiece(Piece p);

#endif
