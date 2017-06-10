CC=gcc
CCFLAGS=-g -Wall -O3
CLEAN=rm -f
PROGRAM_NAME=binTr
OBJECT_FILES=*.o
SOURCE_FILES=main.c binTransl.c

$(PROGRAM_NAME): $(OBJECT_FILES)
	$(CC) $(CCFLAGS) -o $@ $^

$(OBJECT_FILES): $(SOURCE_FILES)
	$(CC) $(CCFLAGS) -c $^

clean:
	$(CLEAN) *.o $(PROGRAM_NAME)

