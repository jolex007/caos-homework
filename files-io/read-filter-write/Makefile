CC=gcc -std=c11 -g

all: solution

solution: solution.c
	$(CC) -o solution solution.c

test: solution
	for i in `seq 1 3`; do \
		./solution tests/00$$i.dir/in.txt tests/00$$i.dir/my-digits.txt tests/00$$i.dir/my-other.txt ; \
		diff tests/00$$i.dir/my-digits.txt tests/00$$i.dir/digits.txt > /dev/null && diff tests/00$$i.dir/my-other.txt tests/00$$i.dir/other.txt > /dev/null ; \
		echo Test $$i finished with status $$? ; \
	done
	
