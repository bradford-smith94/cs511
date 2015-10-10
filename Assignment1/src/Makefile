# Bradford Smith (bsmith8)
# Makefile for CS 511 Assignment 1
# 09/27/2015
# "I pledge my honor that I have abided by the Stevens Honor System."
################################################################################

PRG=primes
AUTHOR=bsmith8
PROJECT=cs511-assignment1
SRC=main.c printError.c printDebug.c findPrimes.c
OBJ=$(SRC:.c=.o)
CC=gcc
RM=rm -f
INCLPATH= -I../include
LIBPATH=
LDLIBS=
LDFLAGS+=
# implicit compiling rules:
# C complied with: `$(CC) -c $(CPPFLAGS) $(CFLAGS)`
CFLAGS+= $(INCLPATH)
CPPFLAGS+= -std=c99 -pedantic-errors -Wall
DBFLGS= -g -DDEBUG

all: $(OBJ)
	$(CC) $(LDFLAGS) $(OBJ) $(LDLIBS) -o $(PRG)

debug: fclean
debug: CPPFLAGS+= $(DBFLGS)
debug: all

clean:
	$(RM) *.o

fclean: clean
	$(RM) *.pipe
	$(RM) $(PRG)

re: fclean all

test: debug
	./primes 44 100

run: re
	./primes 44 100

tar: fclean
	tar -cvzf ../../$(AUTHOR)_$(PROJECT).tar.gz ../*

