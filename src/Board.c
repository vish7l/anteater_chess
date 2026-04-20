#include <stdio.h>
#include "Board.h"
#include "Piece.h"
#include "Space.h"
#include <stdlib.h>

Board *CreateBoard(void) {
	Board *newBoard = (Board *)malloc(sizeof(Board));
	newBoard -> width = 10;
	newBoard -> height = 8;

	if (newBoard == NULL) {
        	printf("Creation of chess board failed\n");
        	return NULL;
	}
	for (int r = 0; r < 8; r++) {
	    for (int c = 0; c < 10; c++) {
		newBoard->board[r][c] = (Space *)malloc(sizeof(Space));
        	newBoard->board[r][c]->piece = NULL;
        	newBoard->board[r][c]-> row = r;
        	newBoard->board[r][c]-> col = c;
	    }
	}
	return newBoard;
}

//deltes the board using malloc()
void DeleteBoard(Board *board) {
	for (int i = 0; i < 8; i ++) {
		for (int j = 0; j < 10; j++) 
		{
			free(board -> board[i][j] -> piece);
			free(board -> board[i][j]);
		}
	}
	free(board);
}

int GetBoardHeight(Board *board) {
	return board->height;	
}

int GetBoardWidth(Board *board) {
	return board->width;
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
4 |    |    |    |    | wP |    |    |    |    |    |
  +----+----+----+----+----+----+----+----+----+----+
3 |    |    |    |    |    |    |    |    |    |    |
  +----+----+----+----+----+----+----+----+----+----+
2 | wP | wP | wP | wP |    | wP | wP | wP | wP | wP |
  +----+----+----+----+----+----+----+----+----+----+
1 | wR | wN | wB | wA | wQ | wK | wA | wB | wN | wR |
  +----+----+----+----+----+----+----+----+----+----+
    A    B    C    D    E    F    G    H    I    J   

 * */
void PrintBoard(Board *board) {
	//intialiaze string
	char value[6] = "";
	value[0] = ' ';
	value[3] = ' ';
	value[4] = '|';
	value[5] = '\0';
	for (int i = 0; i < board -> height * 2 + 1; i++) {
		//the lines are at even indexes
                if (i %2 == 0) {
                        printf(" +----+----+----+----+----+----+----+----+----+----+");
                }
		//treat **board as board[i][j]
                if (i%2 == 1){
			printf("|");
			for (int j = 0; j < board -> width; j ++ ) {
				Space *currentElement = board -> board[i/2][j];
				//prints empty space if the piece of the space is null
	                	if ((currentElement -> piece) == NULL) {
					printf("    |");
				}
				//pawn for 0, anteater for 1, king for 2, queen for 3, rook for 4, bishop for 5, knight for 6
				else { 
					Piece *currentPiece = (board -> board[i/2][j]) -> piece;
					//0 for black and 1 for white
					if ( currentPiece -> color == 0) {
						value[1] = 'b';
					}
					else {
						value[1] = 'w';
					}

					//deciding which letter to place in the space to represent a specific chess piece
					switch(currentPiece -> type) {
						case 0: //ant(pawn)
							value[2] = 'P';
							break;
						case 1: //anteater
							value[2] = 'A';
                                                        break;
						case 2: //king
							value[2] = 'K';
                                                        break;
						case 3: //queen
							value[2] = 'Q';
                                                        break;
						case 4: //rook
							value[2] = 'R';
                                                        break;
						case 5: //bishop
							value[2] = 'B';
                                                        break;
							case 6: //knight
							value[2] = 'N';
                                                        break;
					}
					
					//prints out the piece if the piece is not null
					printf("%s",value);
				}	
        		}

                }

		printf("\n");	
        }
}}

//returns 1 if piece was moved returns 0 if piece cant move because its illegal
void MovePiece(Piece p, char start[], char end[], Board* b) {
	//as you mentioned previously you said that illegal move check will be done before giving the piece
	int start_file = start[0] - 'A';
	int start_rank = '8' - start[1];
	int end_file = end[0] - 'A';
	int end_rank = '8' - end[1];
	if(b->Board[end_rank][end_file]->Piece == NULL)//destination space is null
	{
		b->Board[end_rank][end_file]->Piece = &p;
		b->Board[start_rank][start_file]->Piece = NULL;
	}
	else
	{
		b->Board[end_rank][end_file]->Piece = &p;
		b->Board[start_rank][start_file]->Piece = NULL;
	}
}
Piece* getPieceAt(int rank, int file, Board* b)
{
	return b->board[rank][file]->Piece;
}

char* MakeCoordinateMove(int rank, int file)
{
	char *a = malloc(3* sizeof(char));
	a[0]= (char)(file + 'A') ;
	a[1] = (char)('8' - rank);
	a[2] = '\0';
	return a;      //caller need to free
}

