CC=gcc -std=c11 -g -no-pie -nostdlib

all: solution

solution: solution.c syscall.S
	$(CC) -o solution solution.c syscall.S

test: solution
	for i in `seq 1 9`; do \
		./solution < tests/00$$i.dat > tests/my$$i.ans ; \
		diff tests/my$$i.ans tests/00$$i.ans > /dev/null ; \
		echo Test $$i finished with status $$? ; \
	done
