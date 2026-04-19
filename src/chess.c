#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "Board.h"
#include "Piece.h"
#include "Space.h"
#include "Rules.h"
#include "logManager.h"
#include "AI.h"

int initPieces(Board *board) {
    PieceType backRank[10] = {ROOK, KNIGHT, BISHOP, ANTEATER, QUEEN, KING,
    				ANTEATER, BISHOP, KNIGHT, ROOK};
    for (int c = 0; c < 10; c++) {
    	Piece *wp = (Piece *)malloc(sizeof(Piece));
	wp->color = White;
	wp->type = backRank[c];
	board->board[0][c].piece = wp;

	Piece *wpawn = (Piece *)malloc(sizeof(Piece));
	wpawn->color = White;
	wpawn->type = Pawn;
	board->board[1][c].piece = wpawn;

	Piece *bp = (Piece *)mallc(sizeof(Piece));
	bp->color = Black;
	bp->type = Pawn;
	board->board[6][c].piece = bpawn;

	Piece *bpawn = (Piece *)malloc(sizeof(Piece));
	bpawn->color = Black;
	bpawn->type = backRank[c];
	board->board[7][c].piece = bp;
    }
}

char getPieceChar(Piece *p) {
    switch (p->type) {
	case PAWN:	return 'P';
	case ANTEATER:  return 'A';
	case KING:	return 'K';
	case QUEEN:	return 'Q';
	case ROOK:	return 'R';
	case BISHOP:	return 'B';
	case KNIGHT:	return 'N';
	default:	return '?';
    }	
}

int main()
{
    int gameType = 0;
    int colorChoice = -1;
    
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

    /* Initialize the log */
    initLogManager();

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
	bool moveMade = false;

	if (isHuman) {
	    while (!moveMade) {
		printf("\n%s's turn (move %d). Enter starting position 
							(e.g. E2): ",
			currentTurn == 0 ? "White": "Black", moveNumber);
		scanf("%s", startPos);

		/* Bounds checking */
		int sr = startPos[1] - '1';
		int sc = startPos[0] - 'A';
		
		if (sr < 0 || sr > 7 || sc < 0 || sc > 9) {
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

		/* Get destination */
		printf("Enter destination (e.g. D3): ");
		scanf("%s", endPos);
	
		int er = endPos[1] - '1';
		int ec = endPos[1] - 'A';

		if (er < 0 || er > 7 || ec < 0 || ec > 9) {
		    printf("Invalid coordinates. Try again.\n");
	
		/* Handles all pieces including anteater */
		if (!IllegalMoveCheck(*selected, starPos, endPos, chessBoard)) {
		    printf("Illegel move. Try again.\n");
		    continue;
		}

		/* Capture info before moving */
		Piece *captured = chessBoard->board[er][ec].piece;

                /* Execute the move and add to log */
                MovePiece(*selected, startPos, endPos, chessBoard);
                AddMoveToLog(startPos, endPos, selected, captured);

                /*
                 * If the piece is an anteater and it just ate an ant,
                 * ask the player if they want to continue eating adjacent ants.
                 */
                if (selected->type == Anteater) {
                    char currentPos[3];
                    strcpy(currentPos, endPos);

                    while (1) {
                        PrintBoard(chessBoard);

                        char choice;
                        printf("Anteater moved to %s. 
					Continue eating an adjacent ant? (y/n): ",
                               currentPos);
                        scanf(" %c", &choice);

                        if (choice != 'y' && choice != 'Y') {
                            printf("Anteater stops.\n");
                            break;
                        }

                        char nextPos[3];
                        printf("Enter next position to eat (e.g. F5): ");
                        scanf("%s", nextPos);

                        int nr = nextPos[1] - '1';
                        int nc = nextPos[0] - 'A';

                        if (nr < 0 || nr > 7 || nc < 0 || nc > 9) {
                            printf("Invalid coordinates. Try again.\n");
                            continue;
                        }

                        /*
                         * IllegalMoveCheck validates the chain eat:
                         * - target is adjacent
                         * - target is an opponent ant
                         * - eating is along same file or rank
                         */
                        if (!IllegalMoveCheck(*selected, currentPos, 
						nextPos, chessBoard)) {
                            printf("Cannot eat there. Try again.\n");
                            continue;
                        }

			/* Capture the ant */
			Piece *eatenAnt = chessBoard[nr][nc].piece;

                        /* Execute the chain eat */
                        MovePiece(*selected, currentPos, nextPos, chessBoard);
                        AddMoveToLog(currentPos, nextPos, selected, eatenAnt);

                        strcpy(currentPos, nextPos);
                    }
                }

                moveMade = true;

	    }
	} else {
	    printf("Computer is thinking...\n");
	    
	    char *aiMove = CalculateMove(chessBoard, currentColor);

            if (aiMove == NULL) {
                /* AI has no legal moves — checkmate or stalemate */
                printf("Computer has no legal moves.\n");
                gameDone = true;
                continue;
            }

            /*
             * CalculateMove returns a string like "E2 to E4"
             * Parse it to extract start and end positions
             */
            if (sscanf(aiMove, "%2s to %2s", startPos, endPos) != 2) {
                printf("Error parsing AI move: %s\n", aiMove);
                free(aiMove);
                gameDone = true;
                continue;
            }

            int sr = startPos[1] - '1';
            int sc = startPos[0] - 'A';
            int er = endPos[1] - '1';
            int ec = endPos[0] - 'A';

            Piece *aiPiece = chessBoard->board[sr][sc].piece;
            Piece *captured = chessBoard->board[er][ec].piece;

            printf("Computer moves: %s -> %s\n", startPos, endPos);

            MovePiece(*aiPiece, startPos, endPos, chessBoard);
            AddMoveToLog(startPos, endPos, aiPiece, captured);
	    
	    free(aiMove);
            moveMade = true;
	}

	/* Display updated board */
	PrintBoard(chessBoard);

	/* Check game state for the opponent after our move */
	if (isCheckMate(chessBoard, opponentColor)) {
	    printf("Checkmate! %s wins!\n", currentTurn == 0 ? 
			    "White" : "Black");
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
    SaveLog("game_log.txt");
    PrintLog("game_log.txt");

    /* Clean up */
    DeleteLog();
    DeleteBoard(chessBoard);
    return 0;
}
