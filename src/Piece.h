#ifndef PIECE_H
#define PIECE_H

//first the enum definitions:

//defines the 2 colors
typedef enum{
    Black,
    White

}Color;

//defines the all 7 of the piecetypes
typedef enum{
    PAWN,
    ANTEATER,
    KING,
    QUEEN,
    ROOK,
    BISHOP,
    KNIGHT


}PieceType;

//defines the 8 rows
typedef enum{
    R1,
    R2,
    R3,
    R4,
    R5,
    R6,
    R7,
    R8
}Rank;

//defines the 10 columns
typedef enum{
    A,
    B,
    C,
    D,
    E,
    F,
    G,
    H,
    I,
    J
}File;

//Next the structs

//stores the identity and the behavior of the piece
typedef struct{
    Color color;
    PieceType type;
    //pointer to the function that calculates the legal moves
    char* moveSet;

} Piece;

PieceType getPieceType(Piece *p);
Color getPieceColor(Piece p);
char* getMoveSet(Piece *p);
Piece storePiece(Piece p);

#endif
