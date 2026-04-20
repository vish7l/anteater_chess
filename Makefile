#creating the variables
CC = gcc
DEBUG = -gc
CFLAGS = -Wall -std=c11 $(DEBUG)
LDFLAGS = -lm
TAR_NAME = AnteaterChess_Source.tar.gz

#creating the executable name
TARGET = AnteaterChess

all: $(TARGET)

#create an objs variables
OBJS = chess.o Board.o Piece.o AI.o Rules.o Space.o logManager.o

#link the target executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET) $(LDFLAGS)

#now the individual files
chess.o: chess.c Board.h AI.h Piece.h Space.h Rules.h logManager.h
	$(CC) $(CFLAGS) -c chess.c

Piece.o: Piece.c Piece.h
	$(CC) $(CFLAGS) -c Piece.c

AI.o: AI.c AI.h Rules.h Piece.h logManager.h
	$(CC) $(CFLAGS) -c AI.c

Board.o: Board.c Board.h Piece.h Space.h
	$(CC) $(CFLAGS) -c Board.c

logManager.o: logManager.c logManager.h
	$(CC) $(CFLAGS) -c logManager.c

Piece.o: Piece.c Piece.h
	$(CC) $(CFLAGS) -c Piece.c

Space.o: Space.c Space.h
	$(CC) $(CFLAGS) -c Space.c

Rules.o: Rules.c Rules.h logManager.h Board.h
	$(CC) $(CFLAGS) -c Rules.c

#if you want to run the game immediately
test: $(TARGET)
	./$(TARGET)


tar: 
	tar -cvzf $(TAR_NAME) *.c *.h Makefile

#make clean to remove binaries and files to start fresh
clean:
	rm -f *.o $(TARGET) $(TAR_NAME)

.PHONY: all test clean tar

