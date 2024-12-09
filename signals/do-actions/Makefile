CC=gcc -g
CPP=g++ -std=c++14 -g

all: solution

solution: solution.c interactor.cpp
	$(CC) -o solution solution.c
	$(CPP) -o interactor interactor.cpp

test: solution
	for i in `seq 1 1`; do \
		./solution `head -n 1 tests/00$$i.dat` | ./interactor tests/00$$i.dat > tests/my$$i.ans ; \
		diff tests/my$$i.ans tests/00$$i.ans > /dev/null ; \
		echo Test $$i finished with status $$? ; \
	done

clear:
	rm -rf tests/my*.ans
