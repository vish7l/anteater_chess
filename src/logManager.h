#ifndef logManager
#define logManager
#define LENGTH 80

// Adds most recent move to logs
void AddMoveToLog();

// Remove move made from logs
void UndoMove(char filename[LENGHT]);

// Prints game log history
void PrintLog(char filename[LENGTH]);

char[] getLastMove(void); 

#endif
