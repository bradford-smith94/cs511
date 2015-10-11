# Bradford Smith (bsmith8)
# Makefile for CS 511 Assignment 2
# 10/11/2015
# "I pledge my honor that I have abided by the Stevens Honor System."
################################################################################

RW=rw
T1=transfer1
T2=transter2
TARGETS=$(RW) $(T1) $(T2)
AUTHOR=bsmith8
PROJECT=cs511-assignment2
RWSRC=rw.c printError.c printDebug.c
T1SRC=transfer1.c printError.c printDebug.c cbuf.c start_filler.c start_drainer.c
T2SRC=transter2.c printError.c printDebug.c
RWOBJ=$(RWSRC:.c=.o)
T1OBJ=$(T1SRC:.c=.o)
T2OBJ=$(T2SRC:.c=.o)
CC=gcc
RM=rm -f
INCLPATH=-I../include
LIBPATH=
LDLIBS=-lpthread
LDFLAGS+=
# implicit compiling rules:
# C complied with: `$(CC) -c $(CPPFLAGS) $(CFLAGS)`
CFLAGS+= $(INCLPATH)
CPPFLAGS+= -pedantic-errors -Wall
DBFLGS= -g -DDEBUG

all: $(TARGETS)

rw: $(RWOBJ)
	$(CC) $(LDFLAGS) $(RWOBJ) $(LDLIBS) -o $(RW)

t1: $(T1OBJ)
	$(CC) $(LDFLAGS) $(T1OBJ) $(LDLIBS) -o $(T1)

t2: $(T2OBJ)
	$(CC) $(LDFLAGS) $(T2OBJ) $(LDLIBS) -o $(T2)

debug: fclean
debug: CPPFLAGS+= $(DBFLGS)
debug: all

clean:
	$(RM) *.o

fclean: clean
	$(RM) ../output.txt
	$(RM) $(TARGETS)

re: fclean all

tar: fclean
	tar -cvzf ../../$(AUTHOR)_$(PROJECT).tar.gz ../src ../include

