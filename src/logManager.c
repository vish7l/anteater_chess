#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "logManager.h"

/* head is the first move, tail is the recent move, we are stacking the moves and by undoing we are removing the last move*/

static LogNode *head = NULL;
static LogNode *tail = NULL;

/*initializing logs, lists set to empty*/

void InitLogManager(void){
	head = NULL;
	tail = NULL;
}

void DeleteLog(void){
	LogNode *current = head;
	LogNode *temp;

	while (current != NULL){
		temp = current;
		current = current->next;
		free(temp);
	}
	head = NULL;
	tail = NULL;
}

/* add moves to log, parameters include start and end space, moved piece and the piece caputed, creates node and attaches it*/
void AddMoveToLog(const char start[3], const char end[3], Piece *movedPiece, Piece *capturedPiece)
{
    /* allocate memory*/
    LogNode *newNode = (LogNode *)malloc(sizeof(LogNode));

    if (newNode == NULL) {
        printf("Failed to allocate memory for log node.\n");
        return;
    }

    /*  coordinates */
    strcpy(newNode->start, start);
    strcpy(newNode->end, end);

    /* store string of moves */
    snprintf(newNode->move, LENGTH, "%s %s", start, end);

    /* piece pointers */
    newNode->movedPiece = movedPiece;
    newNode->capturedPiece = capturedPiece;

    /* doubly linked list connections */
    newNode->prev = tail;
    newNode->next = NULL;

    /* if list is not empty, link old tail to new node */
    if (tail != NULL) {
        tail->next = newNode;
    } else {
        head = newNode;
    }

    tail = newNode;
}


/* remove last move but only applies to log, gameengine will also need implementation*/
void UndoLog(void)
{
    LogNode *temp;

    if (tail == NULL) {
        printf("No moves to undo.\n");
        return;
    }

    temp = tail;

    if (tail->prev != NULL) {
        /*move tail back one step*/
        tail = tail->prev;
        tail->next = NULL;
    } else {
        head = NULL;
        tail = NULL;
    }

    free(temp);  // free removed node
}


/* print all moves in log on terminal */
void PrintLog(const char filename[LENGTH])
{
    LogNode *current = head;
    int moveNum = 1;

    /* avoid comipler warning */
    (void)filename;

    if (current == NULL) {
        printf("Log is empty.\n");
        return;
    }

    while (current != NULL) {
        printf("%d. %s\n", moveNum, current->move);
        current = current->next;
        moveNum++;
    }
}


/* save log to file, will be used for saving game*/
void SaveLog(const char filename[LENGTH])
{
    FILE *fp = fopen(filename, "w");
    LogNode *current = head;
    int moveNum = 1;

    if (fp == NULL) {
        printf("Could not open log file.\n");
        return;
    }

    while (current != NULL) {
        fprintf(fp, "%d. %s\n", moveNum, current->move);
        current = current->next;
        moveNum++;
    }

    fclose(fp);
}


/* return last move as string */
const char *GetLastMove(void)
{
    if (tail == NULL) {
        return NULL;
    }
    return tail->move;
}


/* returns pointer to last node will be useful for undo in GameEngine*/
LogNode *GetLastLogNode(void)
{
    return tail;
}

int HasPieceMoved(Piece p, char startPos[3])
{

}
