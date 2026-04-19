#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "AI.h"
#include "Rules.h"
#include "Piece.h"
#include "logManager.h"

//returns a randomly selected legal move from the AI
char *CalculateMove(Board *b, Color aiColor){
    // creating a list that has all the squares that have the AI pieces
    Space *myPieces[80];
    char *myCoords[80];
    int count = 0;

    for(int r = 0; r < 8; r++){
        for(int f = 0; f < 10; f++){
            // change the array index into chess type string
            sprintf(pos, "%c%d" 'A' + f, r + 1);

            Space *s = b->Board[r][f]; 
            if(s -> piece != NULL && getPieceColor(s -> piece) == aiColor){
                char *pos = malloc(3);

                sprintf(pos, "%c%d" 'A' + f, r + 1);

                myPieces[count] = s;
                myCoords[count] = pos;
                count++;
            }
        }
    }

    //now to pick a random piece from the list
    srand(time(NULL));
    int moveFound = 0;
    char *finalMove = malloc(10);

    int attempts = 0;
    while(!moveFound && count > 0 && attempts < 500){
        //attempts is here in case a piece is chosen that isn't able to move
        attempts ++;
        int idx = rand() % count
        Piece *p = myPieces[idx]->piece;
        char *startPos = myCoords[idx];

        //tries doing a random destination
        int targetR = rand() % 8;
        int targetF = rand() % 10;
        char endPos[3];
        sprintf(endPos,"%c%d", 'A' + targetF, targetR + 1);

        //check if the move is legal next
        if(IllegalMoveCheck(*p, startPos, endPos, b)){
            sprintf(finalMove, "%s to %s", startPos, endPos);
            moveFound = 1;
        }

        // We must free all the 'pos' strings we malloc'd in the loop above
        for(int i = 0; i < count; i++) {
            free(myCoords[i]); 
        }

        // If no move was found, we should free finalMove and return NULL 
        // so the game engine knows the AI is stuck (Checkmate/Stalemate)
        if (!moveFound) {
            free(finalMove);
            return NULL;
        }

    }

    return finalMove;
}