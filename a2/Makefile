CC = gcc
CFLAGS = -Wall -g
EXEC = dsh

SRCS = main.c input.c executable.c
OBJS = $(SRCS:.c=.o)
HEADERS = input.h executable.h

all: $(EXEC)

$(EXEC): $(OBJS)
        $(CC) $(CFLAGS) -o $(EXEC) $(OBJS)

main.o: main.c $(HEADERS)
        $(CC) $(CFLAGS) -c main.c

input.o: input.c $(HEADERS)
        $(CC) $(CFLAGS) -c input.c

executable.o: executable.c $(HEADERS)
        $(CC) $(CFLAGS) -c executable.c

clean:
        rm -f $(EXEC) $(OBJS)