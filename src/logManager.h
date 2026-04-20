#ifndef LOGMANAGER_H
#define LOGMANAGER_H
#define LENGTH 80

typedef struct Piece Piece;

typedef struct LogNode{
	char move[LENGTH];
	char start[3];
	char end[3];
	Piece *movedPiece;
	Piece *capturedPiece;
	struct LogNode *prev;
	struct LogNode *next;
} LogNode;

/* initializing and cleanup*/
void InitLogManager(void);
void DeleteLog(void);

/* Add and remove move from doubly linked list*/
void AddMoveToLog(const char start[], const char end[3], Piece *movedPiece, Piece *capturedPiece);
void UndoLog(void);

/* output and loop*/
void PrintLog(const char filename[LENGTH]);
void SaveLog(const char filename[LENGTH]);

/* accessing last move*/
const char *GetLastMove(void);
LogNode *GetLastLogNode(void);

int HasPieceMoved(Piece p, char startPos[3]);


int KingMoved(int color);

int RookMoved(char file, int color);
#endif
