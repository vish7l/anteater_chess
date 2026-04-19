#include "Rules.h"
#include "Log.h"
#include <stdlib.h>
#include <math.h>
int checkifCapture(Piece p, int start_rank, int start_file, Board* b)
{
	int correct_rank;
	int l_correct_file = start_file - 1;
	int r_correct_file = start_file + 1;
	if(GetPieceColor(p) == 1)
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
		if(correct_rank > 8)
		{
			return 0;
		}
	}
	if(lcorrect_file < 0)
	{
		return 0;
	}
	if(rcorrect_file > 9)
	{
		return 0;
	}
	if(getPieceAt(correct_rank, lcorrect_file, b) != NULL)
	{
		return 1;
	}
	else if(getPieceAt(correct_rank, rcorrect_file, b) != NULL)
	{
		return 1;
	}	
	else
	{
		return 0;
	}

}
int CheckEnPassant(int start_rank, Piece p)
{
	char lastMove[] = GetLastMove();
	int lMove_file = LastMove[1] - 'A';
	int lMove_rank = 7 - (LastMove[2] - '1');
	int correct_rank;
	if(getPieceColor(p) == 1)
	{
		correct_rank = 4;

	}
	else
	{
		correct_rank = 5;
	}
	if(start_rank != correct_rank)
	{
		return 0;
	}
	if(lastMove[0] != 'p')
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
	// the starting index is at the top left corner of the chess board
	// convert the start and end character arrats to mathematical 2d array coordinates
	int start_file = start[0] - 'A';
	int start_rank = 7 - (start[1] - '1');
	int end_file = end[0] - 'A';
	int end_rank = 7 - (end[1] - '1');

	if(end_rank >= 8 || end_rank < 0 || start_file < 0 || start_file > 9)
	{
		return 0;
	}
if(GetPieceColor(b->Board[end_rank][end_file]->Piece) == GetPieceColor(p) )
		{
			return 0; //cant go to a space with a piece of same color
		}
if(start_file == end_file && start_rank == end_rank) //piece cant move to itself
{
	return 0;
}
//0 for pawn, 1 for anteater, 2 for king, 3 for queen, 4 for rook, 5 for bishop, 6 for knight
switch (piece.PieceType) {
    case 0: //pawn
	    //need to fix code because we had wrong initial coordinates
	    {
			    if(CheckEnPassant(p, start, end) == 1)
			    {
				char lastMove[] = GetLastMove();
				int lMove_file = LastMove[1] - 'A';
				int lMove_rank = 7 - (LastMove[2] - '1');
				if(end_file == lMove_file && end_rank == lMove_rank)
				{
					return 1;
				}
			    }
			    if(CheckIfCapture(p,start_rank, start_file, b ) == 1)
			    {
				    int correct_rank;
				    int rcorrect_file = start_file + 1;
				    int lcorrect_file = start_file - 1;
				    if(getPieceColor(p) == 1)
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
					    if(end_file == rcorrect_file && end_rank = correct_rank)
					    {
						    return 1;
					    }
				    }
				    else
				    {
					    if(end_file == lcorrect_file && end_rank = correct_rank)
					    {
						    return 1;
					    }
				    }
			    }



		    if(GetPieceColor(p) == 1)//its black
		    {
			    if(end_rank > start_rank)
			    {
				    return 0;
			    }
			    if(end_file != start_file)
			    {
				    return 0;
			    }
			    if(start_rank == 7)
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
			    if(start_rank == 2)
			    {
				    if( end_rank - start_rank != 2 &&  end_rank - start_rank != 1) 
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
		    
		    break;
	    }
    case 4:
	    //rook
	    {
		//similar to the knight, check if the rook's move is valid by checking for a straight path
		//The path between the starting and final position should be stragith vertically or horizontally
		//if the path is horizontal, there should be no vertical change
		//if the path is vertical, there should be no horizontal change
		
		//check for horizontal path
		if (abs(end_rank - start_rank) ==0) {
			if (abs(end_file -start_file) > 0) {
				checkStraightPathClear
				return 1; //valid move	
			}
			else {
				return 0; //invalid move
			}
		}

		//check for vertical path
		else if (abs(end_file - start_file) == 0) {
			if(abs(end_rank - start_rank) > 0) {
				return 1; //valid move
			}
			else {
				return 0; //invalid move
			}
		}
		else {
			return 0; //invalid move
		}
		    break;
	    }
    case 3:
	    //queen
	    {
		    break;
	    }
    case 2:
	    //king
	    //need to fix code because we had wrong initial coordintaes
	    {
		    if(CheckCastle())
		    {
			   // castlelogic + return 1 if true
		    }
		    if( abs(start_file - end_file) > 1 || abs(start_rank - end_rank) > 1 ) //making sure the square is 1 away 
		    {
			    return 0;
		    }
		    if()//end coordinate is attacked by a enemy piece return 0
		    {
			    return 0;
		    }
		    return 1;
		    break;
	    }
    case 1:
	    //anteater
	    {
		    break;
	    }
    default:
        
        break;
}
}


int IsCheck(Board *b, PieceColor color){
   
}

int IsCheckamte(Board *b, PieceColor color){

}

int IsDraw(Board *b, PieceColor color){

}
