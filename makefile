# change application name here (executable output name)
TARGET=server
# compiler
CC=gcc
# debug
DEBUG=-g
# optimisation
OPT=-O0
# warnings
WARN=-Wall

PTHREAD=-pthread

CCFLAGS=$(DEBUG) $(OPT) $(WARN) $(PTHREAD) -pipe

# linker
LD=gcc

LDFLAGS=$(PTHREAD)

OBJS=main.o udp.o

all: $(OBJS)
	$(LD) -o $(TARGET) $(OBJS) $(LDFLAGS)

main.o: main.c
	$(CC) -c $(CCFLAGS) main.c -o main.o

udp.o: udp.c udp.h
	$(CC) -c $(CCFLAGS) udp.c -o udp.o

clean:
	rm -f *.o $(TARGET)
