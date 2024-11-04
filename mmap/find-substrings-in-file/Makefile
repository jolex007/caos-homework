CC=gcc -std=c11 -g

all: solution

solution: solution.c
	$(CC) -o solution solution.c

test: solution
	for i in `seq 1 5`; do \
		./solution tests/00$$i.dir/in.dat `cat tests/00$$i.dir/params.inf` > tests/00$$i.dir/my.ans ; \
		diff tests/00$$i.dir/my.ans tests/00$$i.dir/correct.ans > /dev/null ; \
		echo Test $$i finished with status $$? ; \
	done
