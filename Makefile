#creating the variables
CC = gcc
DEBUG = -g
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
chess.o: src/chess.c src/Board.h src/AI.h src/Piece.h src/Space.h src/Rules.h src/logManager.h
	$(CC) $(CFLAGS) -c src/chess.c

Piece.o: src/Piece.c src/Piece.h
	$(CC) $(CFLAGS) -c src/Piece.c

AI.o: src/AI.c src/AI.h src/Rules.h src/Piece.h src/logManager.h
	$(CC) $(CFLAGS) -c src/AI.c

Board.o: src/Board.c src/Board.h src/Piece.h src/Space.h
	$(CC) $(CFLAGS) -c src/Board.c

logManager.o: src/logManager.c src/logManager.h
	$(CC) $(CFLAGS) -c src/logManager.c

Space.o: src/Space.c src/Space.h
	$(CC) $(CFLAGS) -c src/Space.c

Rules.o: src/Rules.c src/Rules.h src/logManager.h src/Board.h
	$(CC) $(CFLAGS) -c src/Rules.c

#if you want to run the game immediately
test: $(TARGET)
	./$(TARGET)


tar: 
	tar -cvzf $(TAR_NAME) *.c *.h Makefile

#make clean to remove binaries and files to start fresh
clean:
	rm -f *.o $(TARGET) $(TAR_NAME)

.PHONY: all test clean tar

