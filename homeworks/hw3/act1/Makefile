# Makefile for activity 1
# 

CFLAGS_1 = -Wno-format -g -ggdb -std=c99
CLIBFLAGS = -lcurses

all:
	@echo command choices:
	@echo make phase1
	@echo or...
	@echo make phase2
	@echo or...
	@echo make clean

# phase 1 debugging
phase1:
	gcc $(CFLAGS_1) good-life.c -o good-life $(CLIBFLAGS)


CFLAGS_2 = -g -ggdb -std=c99

# phase 2 debugging
phase2:
	gcc $(CFLAGS_2) good-life.c -o good-life $(CLIBFLAGS)

clean:
	-rm -f good-life

