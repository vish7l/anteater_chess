#include "Rules.h"
#include <stdlib.h>


int IllegalMoveCheck(Piece p, char start[], char end[], Board* b)
{
	int start_file = start[0] - 'A';
	int start_rank = start[2] - 1;
	int end_file = end[0] - 'A';
	int end_rank = end[2] - 1;
if(GetPieceColor(b->Board[end_rank][end_file]->Piece) == GetPieceColor(p) )
		{
			return 0; //cant go to a space with a piece of same color
		}
if(start_file == end_file && start_rank == end_rank) //piece cant move to itself
{
	return 0;
}
switch (piece.PieceType) {
    case PAWN:
	    {
		    if(GetPieceColor(p) == 1)//its black
		    {
			    if(CheckEnPassant())
			    {
				    //enpassant logic reutrn 1 
			    }
			    if(CheckIfCapture())
			    {
				    //capture logic for diagonal return 1 

			    }
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
			    //copy black logic for white with tweaks
		    }
		    break;
	    }
    case KNIGHT:
	    {
		    break;
	    }
    case BISHOP:
	    {
		    
		    break;
	    }
    case ROOK:
	    {
		    break;
	    }
    case QUEEN:
	    {
		    break;
	    }
    case KING:
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
    case ANTEATER:
	    {
		    break;
	    }
    default:
        
        break;
}
}
