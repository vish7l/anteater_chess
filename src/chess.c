#include <stdio.h>
#include <math.h>
#include "Board.h"
#include "Rules.h"
#include "logManager.h"
#include <stdlib.h>

int initPieces(Board *board) {
    PieceType backRank[10] = {Rook, Knight, Bishop, Anteater, Queen, King,
    				Anteater, Bishop, Knight, Rook};
    for (int c = 0; c < 10; c++) {
    	Piece *wp = (Piece *)malloc(sizeof(Piece));
	wp->color = White;
	wp->type = backRank[c];
	wp->moveSet = NULL;
	board->board[0][c].piece = wp;

	Piece *wpawn = (Piece *)malloc(sizeof(Piece));
	wpawn->color = White;
	wpawn->type = Pawn;
	wpawn->moveSet = NULL;
	board->board[1][c].piece = wpawn;

	Piece *wpawn = 
    }
}

int main()
{

    int gameType = 0;
    int colorChoice = -1;
    int Player1;
    int Player2;
    
    printf("Welcome to Anteater Chess!\n");

    /* Game mode selection */
    printf("Select the type of game you want to play:\n");
    printf("1. Player vs Player\n");
    printf("2. Player vs Computer\n");
    scanf("%d", &gameType);

    while (gameType != 1 && gameType != 2)
    {
	printf("\nInvalid choice. Enter 1 or 2: ");
	scanf("%d", &gameType);	
    }

    if (gameType == 2) 
    {
    	/* Side selection for PvC */
	printf("\nChoose color, 0 for white, 1 for black: ");
	scanf("%d", &colorChoice)
	while (colorChoice != 0 && colorChoice != 1)
	{
	    printf("\nInvalid color. Enter 0 (white) or 1 (black): ");
	    scanf("%d\n", &colorChoice);
	}
    }

    /* Create and initialize board */
    Board *chessBoard = CreateBoard();
    if (chessBoard == NULL) {
	return 1;
    }
    initPieces(chessBoard);
    PrintBoard(chessBoard);

    bool gameDone = false;
    int currentTurn = 0; /* 0=White, 1=Black */
    int moveNumber = 1;

    while (!gameDone) {
	Color currentColor = (currentTurn == 0) ? White : Black;
	Color opponentColor = (currentTurn == 0) ? Black : White;

	bool isHuman;
	if (gameType == 1) {
	    isHuman = true;
	} else {
	    isHuman = (currentTurn == colorChoice);
	}

	char startPos[3];
	char endPos[3];

	if (isHuman) {
	    bool validMove = false;
	    while (!validmove) {
		printf("\n%s's turn (move %d). Enter move (e.g. E2 E4): ",
			currentTurn == 0 ? "White": "Black", moveNumber);
		scanf("%s %s", startPos, endPos);

		/* Bounds checking */
		int sr = startPos[1] - '1';
		int sc = startPos[0] - 'A';
		int er = endPos[1] - '1';
		int ec = endPos[1] - 'A';
		
		if (sr < 0 || sr > 7 || sc < 0 || sc > 9 ||
                    er < 0 || er > 7 || ec < 0 || ec > 9) {
                    printf("Invalid coordinates. Try again.\n");
                    continue;
                }

		/* Check for piece at the start position */
		Piece *selected = chessBoard->board[sr][sc].piece;
		if (selected == NULL) {
		    printf("No piece at %s. Try again.\n", startPos);
		    continue;
		}

		/* Check if piece belongs to current player */
		if (selected->color != currentColor) {
		    printf("That's not your piece. Try again.\n");
		    continue;
		}

		/* Use Rules.c legality check */
		if (IllegalMoveCheck(*selected, starPos, endPos, chessBoard)) {
		    validMove = true;
		} else {
		    printf("Illegal move. Try again.\n");
		}
	    }
	} else {
	    printf("Computer is thinking...\n");
	    /* TODO: CalculateMove(chessBoard, startPos, endPos); */
	}

	/* Get piece info before moving */
	int sr = startPos[1] - '1';
	int sc = startPos[0] - 'A';
	Piece *movingPiece = chessBoard->board[sr][sc].piece;
	char pieceChar = getPieceChar(movingPiece);

	/* Execute the move */
	MovePiece(*movingPiece, startPos, endPos, chessBoard);

	/* Log the move */
	AddMoveToLog(startPos, endPos, pieceChar, moveNumber);

	/* Display updated board */
	PrintBoard(chessBoard);

	/* Check game state for the opponent after our move */
	if (isCheckMate(chessBoard, opponentColor)) {
	    printf("Checkmate! %s wins!\n", currentTurn == 0 ? "White" : "Black");
	    gameDone = true;
	} else if (isDraw(chessBoard, opponentColor)) {
	    printf("Stalemate! The game is a draw. \n");
	    gameDone = true;
	} else if (isCheck(chessBoard, opponentColor)) {
	    printf("%s is in check!\n", currentTurn == 0 ? "Black" : "White");
	}

	/* Switch turns */
	if (currentTurn == 0) {
	    currentTurn = 1;
	} else {
	    currentTurn = 0;
	    moveNumber++;
	}
    }

    /* Save and print the game log */
    PrintLog("game_log.txt");

    /* Clean up */
    DeleteBoard(chessBoard);
    return 0;
}
