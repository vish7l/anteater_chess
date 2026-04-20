#include "Rules.h"
#include "logManager.h"
#include "Board.h"
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

//check if king in check and if the squares between it and king is attacked by a enemy piece
int isSquareAttacked(int rank, int file, int attackColor, Board* b)
{
	for(int i = 0; i < 8; i++)
	{
		for(int j =0; j < 10; j++)
		{
			if(getPieceAt(i, j, b) == NULL)
			{
				continue;
			}
			else if( getPieceColor(getPieceAt(i,j,b)) != attackColor)
			{
				continue;
			}
			else
			{
				char* start = MakeCoordinateMove(i, j);
				char* end = MakeCoordinateMove(rank,file);
				if(IllegalMoveCheck(*getPieceAt(i,j,b), start, end, b) == 0)
				{
					free(start);
					free(end);
					return 1;
				}
				free(start);
				free(end);
			}
		}
	}
	return 0;
}
int CheckCastleConditionII(char a, Piece p, Board* b)
{
	if(IsCheck(b, getPieceColor(&p)))
	{
	return 0;
	}
	else
	{
		int correct_rank;
		int correct_color;
		if(getPieceColor(&p) == 1)
		{
			correct_rank = 7;
			correct_color = 0;
		}
		else
		{
			correct_rank = 0;
			correct_color = 1;
		}
		switch(a)
		{
			case 'a':
				{
					if(isSquareAttacked(correct_rank, 1,correct_color, b) == 1 || isSquareAttacked(correct_rank, 2,correct_color, b) == 1 || isSquareAttacked(correct_rank, 3,correct_color, b)==1 || isSquareAttacked(correct_rank, 4,correct_color, b) == 1)
					{
						return 0;
					}	
					break;
				}
			case 'j':
				{
	if(isSquareAttacked(correct_rank, 6,correct_color, b) == 1 || isSquareAttacked(correct_rank, 7,correct_color, b) == 1 || isSquareAttacked(correct_rank, 8,correct_color, b) == 1)
	{
		return 0;
	}
					break;
				}
		}
		return 1;
	}
}
//checks if kign not moved rook not moved and space not occupied
int CheckCastleConditionI(char control, Piece p, Board* b)
{
	int correct_rank;
	if(getPieceColor(&p) == 1)
	{
		correct_rank = 7;
	}
	else
	{
		correct_rank = 0;
	}
	if(KingMoved(getPieceColor(&p)) == 1)
	{
		return 0;
	}
	switch(control)
	{
		case('j'):
			{
				if(RookMoved('j', getPieceColor(&p)) == 1)
				{
					return 0;
				}
				else
				{
					//check if the position between them is empty
					if(getPieceAt(correct_rank, 6, b) != NULL || getPieceAt(correct_rank, 7, b) != NULL ||  getPieceAt(correct_rank, 8, b) != NULL )
					{
						return 0;
					}
					return 1;
				}
				break;
			}
		case('a'):
			{
				if(RookMoved('a', getPieceColor(&p)) == 1)
				{
					return 0;
				}
				else
				{
					//check if the position between them is empty
					if(getPieceAt(correct_rank, 1, b) != NULL || getPieceAt(correct_rank, 2, b) != NULL ||  getPieceAt(correct_rank, 3, b) != NULL ||    getPieceAt(correct_rank, 4, b) != NULL)
					{
						return 0;
					}
					return 1;
				}

				break;
			}
	}
	return 0;

}


int checkifCapture(Piece p, int start_rank, int start_file, Board* b)
{
	int correct_rank;
	int l_correct_file = start_file - 1;
	int r_correct_file = start_file + 1;
	if(getPieceColor(&p) == 1)
	{
		correct_rank = start_rank -1;
		if(correct_rank < 0)
		{
			return 0;
		}
	}
	else
	{
		correct_rank = start_rank + 1;
		if(correct_rank > 7)
		{
			return 0;
		}
	}
	if(l_correct_file < 0)
	{
		return 0;
	}
	if(r_correct_file > 9)
	{
		return 0;
	}
	if(getPieceAt(correct_rank, l_correct_file, b) != NULL && getPieceColor(getPieceAt(correct_rank, l_correct_file, b) ) != getPieceColor(&p))
	{
		return 1;
	}
	else if(getPieceAt(correct_rank, r_correct_file, b) != NULL && getPieceColor(getPieceAt(correct_rank, r_correct_file, b)) != getPieceColor(&p)  )
	{
		return 1;
	}	
	else
	{
		return 0;
	}
}
//will be used for checking if the straight path of the rook or queen is clear
int checkStraightPathClear(char start[], char end[], Board *board) {
	 // the starting index is at the top left corner of the chess board
        // convert the start and end character arrats to mathematical 2d array coordinates
        int start_file = start[0] - 'A';
        int start_rank = 7 - (start[1] - '1');
        int end_file = end[0] - 'A';
        int end_rank = 7 - (end[1] - '1');

	int min, max;
	
		//check for clear horiontal path
	 	if (abs(end_rank - start_rank) == 0) {
                        if (abs(end_file - start_file) > 0) {

				//set the start and end values to iterate across the horizontal or vertical path
				if ( end_file > start_file) {
					min = start_file;
					max = end_file;
				}
				else {
					min = end_file;
					max = start_file;
				}

				// use a for loop to iterate across the horizontal path and starts on the square ahead of it's current square
                                for (int i = min + 1; i < max; i ++) {
					Space *currentElement = board->board[start_rank][i];
					if (currentElement -> piece != NULL) {
						return 0; // no clear path since there is a piece in the way and it is not null
					}						 
				}
				return 1; //clear path and all the pieces in the straight path are null
                        }
                        else {
                                return 0; //no clear path
                        }
                }

                //check for vertical path
                else if (abs(end_file - start_file) == 0) {
                        if(abs(end_rank - start_rank) > 0) {

				//set the start and end values to iterate acr	oss the horizontal or vertical path
                                if ( end_rank > start_rank) {
                                        min = start_rank;
                                        max = end_rank;
                                }
                                else {
                                        min = end_rank;
                                        max = start_rank;
                                }
				
				// use a for loop to iterate across the vertical path and starts on the square ahead of it's current square
				for (int i = min + 1; i < max; i ++) {
                                        Space *currentElement = board->board[i][start_file];
                                        if (currentElement -> piece != NULL) {
                                                return 0; // no clear path since there is a piece in the way and it is not null
                                        }
                                }
				return 1; //clear path and all the pieces in the straight path are null
                                
                        }
                        else {
                                return 0; //no clear path
                        }
                }
		else {
			return 0;
		}

}

//will be used for checking if the diagonal path of the queen or bishop is clear
int checkDiagonalPathClear(char start[], char end[], Board *board) {
	 // the starting index is at the top left corner of the chess board
        // convert the start and end character arrats to mathematical 2d array coordinates
        int start_file = start[0] - 'A';
        int start_rank = '8' - start[1];
        int end_file = end[0] - 'A';
        int end_rank = '8' - end[1];

	
	if(abs(end_rank - start_rank) != abs(end_file-start_file))
	{
		return 0;
	}
	int file_direction = (end_file - start_file)/abs(end_file - start_file);
	int rank_direction = (end_rank - start_rank)/abs(end_rank-start_rank);

	while(start_rank != end_rank || start_file != end_file)
	{
	start_rank = start_rank + rank_direction;
	start_file = start_file + file_direction;
	if(start_rank < 0  || start_rank > 7 || start_file < 0 || start_file > 9 )
	{
		return 0;
	}
	else
	{
		if(getPieceAt(start_rank, start_file, board) != NULL)
		{
			return 0;
		}
	}
	}
	return 1;

}

//have an array to tracked all the visited positions
//1 means the recursive function already visited that location
//0 means the recursive function is yet to go that position
//x and y correspondt to the indexes of the visited positoons array but also refer to the actual index positions of the game
int stayedAtPositions[8][10];
for (int x = 0; x < 8; x++) {
	for (int y = 0; y < 10; y++) {	
		stayedAtPositions[x][y] = 0;
       	}
}

//only run or use this functon if the target positon contains an anteater or to check if adjacent positions have anteater for anteating consecutive ants
//this is a recursive function
int validAnteating(int currentX, int currentY, int endX, int endY, Board *board, int anteaterColor) {
	
	//only checks for valid anteating trails on positions that were not visited yet
	if (stayedAtPositions[currentX][currentY] == 0) {
		//because the position will checked, that element will be declared to 1
		stayedAtPositions[currentX][currentY] = 1;

		//base cases of either reach target location after capturing all pawns or hitting a space where there is no pawn anymore to capture
		if ((currentX == endX) && (currentY == endY)) {
			//only returns 1 if it keeps going and reaches base case
			//this means the valid anteating processing is correct and only returns 1 under this case
			
			if (board[currentX][currentY] -> piece -> PieceType == 0) {
                        	return 1;
                	}
			//has reached target location but target location has no pawn, so it is not a valid move
			else {
				return 0;
			}
		}

		//adjacent space is 1 space up
		if (board[currentX-1][currentY]->piece != NULL && (board[currentX - 1][currentY]) -> piece -> PieceType == 0 && currentX - 1 >= 0 &&
				board[currentX - 1][currentY]->piece->color != anteaterColor) {
			//decrement the currentX value by 1 to check top space
                        //check 4 directions of that adjacent piece
			if (validAnteating(currentX - 1, currentY, endX, endY, board, anteaterColor) == 1) {
				return 1;
			}

                }
		//adjacent space is 1 space down
		if (board[currentX + 1][currentY]->piece != NULL && (board[currentX + 1][currentY]) -> piece -> PieceType == 0 && currentX + 1 < 8 &&
				board[currentX + 1][currentY]->piece->color != anteaterColor) {
                        //increment the currentX by 1 to check bottom square
			//check 4 directions of that adjacent piece
                        if (validAnteating(currentX + 1, currentY, endX, endY, board, anteaterColor) == 1) {
                                return 1;
                        }

                }

		//adjacent space is 1 space right
		if (board[currentX][currentY + 1]->piece != NULL && (board[currentX][currentY + 1]) -> piece -> PieceType == 0 && currentY + 1 < 10 && 
				board[currentX][currentY + 1]->piece->color != anteaterColor) {
                        //increment currentY to check right space
                        //check 4 directions of that adjacent piece
                        if (validAnteating(currentX, currentY + 1, endX, endY, board, anteaterColor) == 1) {
                                return 1;
                        }
                }
		//adjacent space is 1 space left
		if (board[currentX][currentY - 1]->piece != NULL && (board[currentX][currentY - 1]) -> piece -> PieceType == 0 && currentY - 1 >= 0 && 
				board[currentX][currentY - 1]->piece->color != anteaterColor) {
                        //decrement currentY by 1 to check left space
                        //check 4 directions of that adjacent piece
			if (validAnteating(currentX, currentY - 1, endX, endY, board, anteaterColor) == 1) {
                                return 1;
                        }               
                }
	} 
		return 0;
}

}
int CheckEnPassant(int start_rank,int start_file, Piece p)
{
	const char* lastMove = GetLastMove();
	int lMove_file = lastMove[0] - 'A';
	int lMove_rank = '8' - lastMove[1];
	int correct_rank;
	if(getPieceColor(&p) == 1)
	{
		correct_rank = 3;

	}
	else
	{
		correct_rank = 4;
	}
	if(start_rank != correct_rank)
	{
		return 0;
	}
	if(lastMove[2] != 'p')
	{
		return 0;
	}
	else
	{
		if( lMove_file != (start_file + 1) && lMove_file != (start_file - 1)  )
		{
			return 0;
		}
		if( lMove_rank != correct_rank)
		{
			return 0;
		}
		return 1;

	}

}


int IllegalMoveCheck(Piece p, char start[], char end[], Board* b)
{
	//makes sure the piece in the target location is not a piece of the same side
	int start_file = start[0] - 'A';
	int start_rank = '8' - start[1];
	int end_file = end[0] - 'A';
	int end_rank = '8' - end[1];

	if(end_rank >= 8 || end_rank < 0 || start_file < 0 || start_file > 9)
	{
		return 0;
	}

	if(start_file == end_file && start_rank == end_rank) //piece cant move to itself
	{
		return 0;
	}

	if(b->board[end_rank][end_file]->piece != NULL && getPieceColor(b->board[end_rank][end_file]->piece) == getPieceColor(&p))
	{
		return 0;
	}
//0 for pawn, 1 for anteater, 2 for king, 3 for queen, 4 for rook, 5 for bishop, 6 for knight
switch (p.type) {
    case 0: //pawn
	    //need to fix code because we had wrong initial coordinates
	    {
			    if(CheckEnPassant(start_rank, start_file, p) == 1)
			    {
				const char* lastMove = GetLastMove();
				int lMove_file = lastMove[0] - 'A';
				int lMove_rank = '8' - lastMove[1];
				if(end_file == lMove_file && end_rank == lMove_rank)
				{
					return 1;
				}
			    }
			    if(checkifCapture(p,start_rank, start_file, b ) == 1)
			    {
				    int correct_rank;
				    int rcorrect_file = start_file + 1;
				    int lcorrect_file = start_file - 1;
				    if(getPieceColor(&p) == 1)
				    {
					    correct_rank = start_rank -1;
				    }
				    else
				    {
					    correct_rank = start_rank + 1;
				    }
				    if(rcorrect_file > 9)
				    {
					    rcorrect_file = -1;
				    }
				    if(lcorrect_file < 0)
				    {
					    lcorrect_file = -1;
				    }
				    if(rcorrect_file != -1)
				    {
					    if(end_file == rcorrect_file && end_rank == correct_rank)
					    {
						    return 1;
					    }
				    }
				    if(lcorrect_file != -1)
				    {
					    if(end_file == lcorrect_file && end_rank == correct_rank)
					    {
						    return 1;
					    }
				    }
			    }



		    if(getPieceColor(&p) == 1)//its black
		    {
			    if(end_rank > start_rank)
			    {
				    return 0;
			    }
			    if(end_file != start_file)
			    {
				    return 0;
			    }
			    if(start_rank == 1)
			    {
				    if(start_rank - end_rank != 2 && start_rank - end_rank != 1) 
				    {
					    return 0;
				    }
			    }
			    else
			    {
				    if(start_rank - end_rank != 1) 
				    {
					    return 0;
				    }
			    }
			    return 1;

		    }
		    else//its white
		    {

				 if(end_rank < start_rank)
			    {
				    return 0;
			    }
			    if(end_file != start_file)
			    {
				    return 0;
			    }
			    if(start_rank == 6)
			    {
				    if( end_rank - start_rank != 2 &&  end_rank - start_rank != 1) 
				    {
					    return 0;
				    }
			    }
			    else
			    {
				    if(end_rank - start_rank != 1) 
				    {
					    return 0;
				    }
			    }
			    return 1;
		    }
		    break;
	    }
    case 6:
	    //knight
	    //1 possible way: check all possible 8 L paths from its current position
	    //2nd way: find difference between start and end position coordinates and check if the path is in L pattern of 2 by 3 or 3 by 2
	    //using the 2nd way by checking differences in postions
	    {
		    //Path 1 of checking if the path is a 3 by 2 with vertical change of 3 and horizontal change of 2
		    if (abs(end_rank - start_rank) == 3) {
		    	if (abs(end_file - start_file) == 2) {
				return 1; //valid path
			}
			else{
				return 0; //invalid path
			}
		    }
		    //Path 2 of checking if the path is a 2 by 3 with vertical change of 2 and horizontal change of 3
		    else if (abs(end_rank - start_rank) == 2) {
			    if (abs(end_file - start_file) == 3 ) {
			    	return 1; //valid path
			    }
			    else {
			    	return 0; //invalid path
			    }
		    }
		    //the end position is invalid
		    else {
		    	return 0; //invalid path
		    }


		    break;
	    }
    case 5:
	    //bishop
	    {
	    		return checkDiagonalPathClear(start, end, b);	    
		    break;
	    }
    case 4:
	    //rook
	    {
		//similar to the knight, check if the rook's move is valid by checking for a straight path
		//The path between the starting and final position should be stragith vertically or horizontally
		//if the path is horizontal, there should be no vertical change
		//if the path is vertical, there should be no horizontal change
		
		 //call this function directly to check for either a clear horizontal or clear vertical path
    		return checkStraightPathClear(start, end, b);
		
	    }
		    
    case 3:
	    //queen
	    {
		    //use similar logic for rook if the queen wants to move in a straight path
		    //have to check for both diagonal and straight paths
		
		//check for clear straight path
		 if ( (abs(end_rank - start_rank) == 0) || (abs(end_file - start_file) > 0) ) {
		 	return checkStraightPathClear(start, end, b);	 
		 }
		 //
		 else {
			return  checkDiagonalPathClear(start, end, b);
		 		
		 } 

	    }
    case 2:
	    //king
	    //need to fix code because we had wrong initial coordintaes
	    {
		   if(CheckCastleConditionI('a', p, b) == 1)
            {
                if(CheckCastleConditionII('a', p, b) == 1)
                {
                    if(end_file == start_file - 2)
                        return 1;
                }
            }
            if(CheckCastleConditionI('j', p, b) == 1)  
            {
                if(CheckCastleConditionII('j', p, b) == 1)
                {
                    if(end_file == start_file + 2)
                        return 1;
                }
            }
            if(abs(start_file - end_file) > 1 || abs(start_rank - end_rank) > 1)
                return 0;
            if(isSquareAttacked(end_rank, end_file, getPieceColor(&p) == 1 ? 0 : 1, b) == 1) 
                return 0;
            return 1;
            break;
        }
	    }
    case 1:
	    //anteater
	    {
		    //can either move one space anywhere or or kill pawns adjecent to itself
		    //if there are no pawns adjacent to the anteater, it can only move one space in any direction

		    Space *targetSpace = b[end_rank][end_file];
		    
		    int targetColor = -1;
		
		    if (targetSpace->piece != NULL) {
    			targetColor = targetSpace->piece->color;
		    }
		   
		   //checking adjacent spaces
		    //can only move to adjacent spaces only if the spaces are empty or have an ant
		    //target 1 space down
		    if ( (end_rank - start_rank  == 1) && (end_file == start_file)) {
		    	if(targetSpace -> piece == NULL) {
				return 1;
			}
			//is valid if the piece is an ant
			else if ((targetSpace -> piece) -> PieceType == 0 && targetColor != p -> color) {
				return 1;
			}
		    }
		    //target is 1 space up
		    else if ((start_rank - end_rank == 1) && (end_file == start_file)) {
			if(targetSpace -> piece == NULL) {
                                return 1;
                        }
                        //is valid if the piece is an ant
                        else if ((targetSpace -> piece) -> PieceType == 0 && targetColor != p -> color) {
                                return 1;
                        }
		    
		    }
		    //target is 1 space right
		    else if ((start_rank == end_rank) && (end_file - start_file == 1)){
                        if(targetSpace -> piece == NULL) {
                                return 1;
                        }
                        //is valid if the piece is an ant
                        else if ((targetSpace -> piece) -> PieceType == 0 && targetColor != p -> color) {
                                return 1;
                        }

		    }
		    //target is 1 space left
		    else if ((start_rank == end_rank) && (start_file - end_file == 1)) {
                        if(targetSpace -> piece == NULL) {
                                return 1;
                        }
                        //is valid if the piece is an ant
                        else if ((targetSpace -> piece) -> PieceType == 0 && targetColor != p -> color) {
                                return 1;
                        }
		    
		    }
		    //now consider another case where the target space is not adjacent and instead is occupied by an ant(pawn)
		    else if ((targetSpace -> piece) -> PieceType == 0 && targetColor != p -> color ) {
	    	        //will compare the opponent's color to the anteater's color using the variable anteaterColor
		        int anteaterColor = b[start_rank][start_file] -> piece -> color;
			
			for (int x = 0; x < 8; x++) {
        			for (int y = 0; y < 10; y++) {
                			stayedAtPositions[x][y] = 0;
             				}
			}

			return validAnteating(start_rank, start_file, end_rank, end_file, b, anteaterColor);

		    }
		    else {return 0;}

		    break;
	    }
    default:
        
        break;
}
}
static int FindKing(Board *b, Color color, int *king_rank, int *king_file){
    for (int r = 0; r < 8; r++)
        {
            for (int c = 0; c < 10; c++)
            {
                Piece *p = b->board[r][c]->piece;
                if (p != NULL && p->type == KING && getPieceColor(p) == color)
                {
                    *king_rank = r;
                    *king_file = c;
                    return 1;
                }
            }
        }
    return 0;
       
}


int IsCheck(Board *b, Color color){
    //find location of king
    //make coordinate
    int king_rank, king_file;

    if (!FindKing(b, color, &king_rank, &king_file))
        return 0;

    char king_coord[3];
    king_coord[0] = 'A' + king_file;
    king_coord[1] = '1' + king_rank;
    king_coord[2] = '\0';

    Color enemyColor = (color == White) ? Black : White;

    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 10; c++) {
            Piece *p = b->board[r][c]->piece;
            if (p == NULL) continue;
            if (getPieceColor(&p) != enemyColor) continue;

            char from[3];
            from[0] = 'A' + c;
            from[1] = '1' + r;
            from[2] = '\0';

            if (IllegalMoveCheck(*p, from, king_coord, b))
                return 1;
        }
    }
    return 0;
}

int IsCheckmate(Board *b, Color color){
    if (!IsCheck(b, color)) return 0;

    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 10; c++) {
            Piece *p = b->board[r][c]->piece;
            if (p == NULL) continue;
            if (getPieceColor(p) != color) continue;

            char from[3];
            from[0] = 'A' + c;
            from[1] = '1' + r;
            from[2] = '\0';

            for (int tr = 0; tr < 8; tr++) {
                for (int tc = 0; tc < 10; tc++) {
                    char to[3];
                    to[0] = 'A' + tc;
                    to[1] = '1' + tr;
                    to[2] = '\0';

                    if (!IllegalMoveCheck(*p, from, to, b))
                        continue;

                    Piece *captured = b->board[tr][tc]->piece;
                    b->board[tr][tc]->piece = p;
                    b->board[r][c]->piece = NULL;

                    int stillInCheck = IsCheck(b, color);

                    b->board[r][c]->piece = p;
                    b->board[tr][tc]->piece = captured;

                    if (!stillInCheck)
                        return 0;
                }
            }
        }
    }

    return 1;
}

int IsStalemate(Board *b, Color color)
{
    /* Stalemate = not in check AND no legal moves */
    if (IsCheck(b, color)) return 0;

    for (int sr = 0; sr < BOARD_HEIGHT; sr++) {
        for (int sf = 0; sf < BOARD_WIDTH; sf++) {
            Piece *p = b->board[sr][sf]->piece;
            if (p == NULL) continue;
            if (getPieceColor(p) != color) continue;

            char start[3];
            MakeCoordinateMove(sr, sf, start);

            for (int er = 0; er < BOARD_HEIGHT; er++) {
                for (int ef = 0; ef < BOARD_WIDTH; ef++) {
                    char end[3];
                    MakeCoordinateMove(er, ef, end);

                    if (!IllegalMoveCheck(*p, start, end, b)) continue;

                    /* Temporarily apply the move */
                    Piece *captured         = b->board[er][ef]->piece;
                    b->board[er][ef]->piece = p;
                    b->board[sr][sf]->piece = NULL;

                    int stillInCheck = IsCheck(b, color);

                    /* Always restore the board */
                    b->board[sr][sf]->piece = p;
                    b->board[er][ef]->piece = captured;

                    if (!stillInCheck) return 0;
                }
            }
        }
    }
    return 1;
}

int IsDraw(Board *b)
{
    int whiteBishops   = 0, blackBishops   = 0;
    int whiteKnights   = 0, blackKnights   = 0;
    int whiteAnteaters = 0, blackAnteaters = 0;
    int whiteOther     = 0, blackOther     = 0;
    int whiteBishopSquare = -1, blackBishopSquare = -1;

    for (int r = 0; r < BOARD_HEIGHT; r++) {
        for (int f = 0; f < BOARD_WIDTH; f++) {
            Piece *p = b->board[r][f]->piece;
            if (p == NULL) continue;

            PieceType t = getPieceType(p);
            Color     c = getPieceColor(p);

            if (t == KING) continue;

            switch (t) {
                case BISHOP:
                    if (c == White) { whiteBishops++; whiteBishopSquare = (r + f) % 2; }
                    else            { blackBishops++; blackBishopSquare = (r + f) % 2; }
                    break;
                case KNIGHT:
                    if (c == White) whiteKnights++;
                    else            blackKnights++;
                    break;
                case ANTEATER:
                    if (c == White) whiteAnteaters++;
                    else            blackAnteaters++;
                    break;
                default:
                    if (c == White) whiteOther++;
                    else            blackOther++;
                    break;
            }
        }
    }

    if (whiteOther > 0 || blackOther > 0) return 0;

    int whitePieces = whiteBishops + whiteKnights + whiteAnteaters;
    int blackPieces = blackBishops + blackKnights + blackAnteaters;

    /* K vs K */
    if (whitePieces == 0 && blackPieces == 0) return 1;

    /* K+N vs K  or  K vs K+N */
    if ((whitePieces == 1 && whiteKnights == 1 && blackPieces == 0) ||
        (blackPieces == 1 && blackKnights == 1 && whitePieces == 0)) return 1;

    /* K+B vs K  or  K vs K+B */
    if ((whitePieces == 1 && whiteBishops == 1 && blackPieces == 0) ||
        (blackPieces == 1 && blackBishops == 1 && whitePieces == 0)) return 1;

    /* K+A vs K  or  K vs K+A */
    if ((whitePieces == 1 && whiteAnteaters == 1 && blackPieces == 0) ||
        (blackPieces == 1 && blackAnteaters == 1 && whitePieces == 0)) return 1;

    /* K+B vs K+B same square color */
    if (whitePieces == 1 && whiteBishops == 1 &&
        blackPieces == 1 && blackBishops == 1 &&
        whiteBishopSquare == blackBishopSquare) return 1;

    return 0;
}
