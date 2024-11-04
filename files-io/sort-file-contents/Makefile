CC=gcc -std=c11 -g

all: solution

solution: solution.c
	$(CC) -o solution solution.c

test: solution
	for i in `seq 1 6`; do \
		cp tests/00$$i.dat tests/my$$i.ans ; \
		./solution tests/my$$i.ans ; \
		diff tests/my$$i.ans tests/00$$i.ans > /dev/null ; \
		echo Test $$i finished with status $$? ; \
	done
