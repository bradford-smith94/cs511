# Bradford Smith (bsmith8)
# Makefile for CS 511 Assignment 4
# 11/08/2015
# "I pledge my honor that I have abided by the Stevens Honor System."
################################################################################

AUTHOR=bsmith8
PROJECT=cs511-assignment4
RM=rm -f
JC=javac
GIVEN=TokenCount.java
V1=MyTokenCountV1.java
V2=MyTokenCountV2.java
V3=MyTokenCountV3.java
V4=MyTokenCountV4.java
SHARED=Page.java Pages.java PoisonPill.java WikiPage.java Words.java
TEX=pdflatex
REPORT=report.tex

all: given mine report

given:
	$(JC) $(GIVEN) $(SHARED)

mine: v1 v2 v3 v4

v1:
	$(JC) $(V1) $(SHARED)
v2:
	$(JC) $(V2) $(SHARED)
v3:
	$(JC) $(V3) $(SHARED)
v4:
	$(JC) $(V4) $(SHARED)

report:
	$(TEX) $(REPORT)

report_clean:
	$(RM) *.aux
	$(RM) *.log

clean:
	$(RM) *.swp
	$(RM) *.aux
	$(RM) *.log

fclean: clean
	$(RM) *.class
	$(RM) $(REPORT:.tex=.pdf)

re: fclean all

tar: fclean report report_clean
	tar -cvzf ../$(AUTHOR)_$(PROJECT).tar.gz ./*

