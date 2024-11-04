#!/usr/bin/python3

import random
import os
import sys


def make_value_bytes(value: int):
    result = value.to_bytes(4, byteorder="little", signed=True)
    while len(result) < 4:
        result = b"\0x00" + result
    return result;


def make_data_and_answers(max_entries: int):
    if 0==max_entries:
        return b"", b""
    randoms = list(range(0, max_entries))
    random.shuffle(randoms)
    file_size = max_entries * 4
    dat = bytearray(file_size)
    ans = bytearray(file_size)
    dat_view = memoryview(dat)
    ans_view = memoryview(ans)
    for index, value in enumerate(randoms):
        start_address = index * 4
        end_address = start_address + 4
        dat_view[start_address:end_address] = make_value_bytes(value)
        ans_view[start_address:end_address] = make_value_bytes(index)
    return dat, ans


def make_test(test_no: int, max_entries: int):
    dat, ans = make_data_and_answers(max_entries)
    os.mkdir("tests/{:03d}.dir".format(test_no))
    with open("tests/{:03d}.dir/in.dat".format(test_no), "wb") as f:
        f.write(dat)
    with open("tests/{:03d}.ans".format(test_no), "wb") as f:
        f.write(ans)
    with open("tests/{:03d}.inf".format(test_no), "w") as f:
        print("params = in.dat", file=f)
    with open("tests/{:03d}.dat".format(test_no), "w") as f:
        print("", file=f)

        
def main():
    test_no = int(sys.argv[1])
    max_entries = int(sys.argv[2])
    make_test(test_no, max_entries)

if __name__=="__main__":
    main()
    
