# Bradford Smith (bsmith8)
# Makefile for CS 511 Assignment 3
# 10/24/2015
# "I pledge my honor that I have abided by the Stevens Honor System."
################################################################################

PRG=trafficmgr
AUTHOR=bsmith8
PROJECT=cs511-assignment3
SRC=main.c thread_start.c monitor_init.c monitor_arrive.c monitor_cross.c \
	monitor_leave.c monitor_shutdown.c q.c
OBJ=$(SRC:.c=.o)
CC=gcc
RM=rm -f
INCLPATH=-I../include
LIBPATH=
LDLIBS= -lpthread
LDFLAGS+=
# implicit compiling rules:
# C complied with: `$(CC) -c $(CPPFLAGS) $(CFLAGS)`
CFLAGS+= $(INCLPATH)
CPPFLAGS+= -pedantic-errors -Wall
CXXFLAGS+=
DBFLGS= -g -DDEBUG

all: $(OBJ)
	$(CC) $(LDFLAGS) $(OBJ) $(LDLIBS) -o $(PRG)

debug: fclean
debug: CPPFLAGS+= $(DBFLGS)
debug: all

clean:
	$(RM) *.o

fclean: clean
	$(RM) $(PRG)

re: fclean all

tar: fclean
	tar -cvzf ../../$(AUTHOR)_$(PROJECT).tar.gz ../*

