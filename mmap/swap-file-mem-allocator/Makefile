CC=gcc -std=c11 -g -D_XOPEN_SOURCE=500

all: solution

solution: main.c solution.c
	$(CC) -o solution main.c solution.c

test: solution
	for i in `seq 1 1`; do \
		./solution tests/00$$i.dat > tests/my$$i.ans ; \
		diff tests/my$$i.ans tests/00$$i.ans > /dev/null ; \
		echo Test $$i finished with status $$? ; \
	done
