CC:=aarch64-linux-gnu-gcc  # Write it to the PATH
LINARO_SYSROOT_AARCH64:=<path to sysroot>

all: solution

solution: main.c solution.S
	$(CC) -o solution main.c solution.S

test: solution tests/001.dat tests/001.ans
	qemu-aarch64 -L $(LINARO_SYSROOT_AARCH64) ./solution < tests/001.dat > tests/my.ans
	diff tests/my.ans tests/001.ans
