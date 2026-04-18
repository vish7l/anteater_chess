#include <stdio.h>
#include <Board.h>
#include <Piece.h>
#include <Space.h>
#include <stdlib.h>

Board *CreateBoard(void) {
	Board *newBoard = (Board*) malloc(sizeof(Board));

	if (newBoard == NULL) {
        	printf("Creation of chess board failed\n");
        	return NULL;
    	}

	return newBoard;
       		
}

//deltes the board using malloc()
void DeleteBoard(Board *board) {
	free(board);
}

void GetBoardHeight(Board *board) {
	return board -> height;	
}

void GetBoardWidth(Board *board) {
	return board -> width;
}

/*
   +----+----+----+----+----+----+----+----+----+----+ index: 0
8 | bR | bN | bB | bA | bQ | bK | bA | bB | bN | bR | index: 1
  +----+----+----+----+----+----+----+----+----+----+ index: 2
7 | bP | bP | bP | bP | bP | bP | bP | bP | bP | bP |index: 3
  +----+----+----+----+----+----+----+----+----+----+index: 4
6 |    |    |    |    |    |    |    |    |    |    |index: 5
  +----+----+----+----+----+----+----+----+----+----+
5 |    |    |    |    |    |    |    |    |    |    |
  +----+----+----+----+----+----+----+----+----+----+
4 |    |    |    |    | wP|    |    |    |    |    |
  +----+----+----+----+----+----+----+----+----+----+
3 |    |    |    |    |    |    |    |    |    |    |
  +----+----+----+----+----+----+----+----+----+----+
2 | wP | wP | wP | wP |    | wP | wP | wP | wP | wP |
  +----+----+----+----+----+----+----+----+----+----+
1 | wR | wN | wB | wA | wQ | wK | wA | wB | wN | wR |
  +----+----+----+----+----+----+----+----+----+----+
    A    B    C    D    E    F    G    H    I    J   

 * */
void printBoard(Board *board) {
	for (int i = 0; i < board -> height; i++) {
		//the lines are at even indexes
                if (i %2 == 0) {
                        printf(" +----+----+----+----+----+----+----+----+----+----+");
                }
		//treat **board as board[i][j]
                if (i%2 == 1){
			for (int j = 0; j < board -> width; j ++ ) {
				Space currenElement = board[i][j];
				//prints empty space if the piece of the space is null
	                	if ((currentElement -> p) == NULL) {
					printf("    ");
				}
				else {
					
				}
        		}			

                }
		
		printf("\n");
        }
}

//returns 1 if piece was moved returns 0 if piece cant move because its illegal
int MovePiece(Piece p, char start[], char end[], Board* b) {
	
}

