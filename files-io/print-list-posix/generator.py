#!/usr/bin/python3

import random
import os
import sys

def make_struct(value: int, next_index: int):
    result = next_index.to_bytes(4, byteorder="little", signed=False)
    while len(result) < 4:
        result = b"\0x00" + result
    result = value.to_bytes(4, byteorder="little", signed=True) + result
    while len(result) < 8:
        result = b"\0x00" + result
    return result;


def make_data_and_answers(max_entries: int):
    if 0==max_entries:
        return b"", []
    random_indeces = list(range(1, max_entries))
    random.shuffle(random_indeces)
    indeces = [0] + random_indeces
    answers = []
    struct_size = 8  # { int32_t value; uint32_t next_index; }
    file_size = max_entries * struct_size
    contents = bytearray(file_size)
    view = memoryview(contents)
    for i, index in enumerate(indeces):
        value = random.randint(-100000, 100000)
        start_address = index * struct_size
        end_address = start_address + struct_size
        next_index = indeces[i+1]*struct_size if i<len(indeces)-1 else 0
        struct_contents = make_struct(value, next_index)
        view[start_address:end_address] = struct_contents
        answers += [value]
    return contents, answers


def make_test(test_no: int, max_entries: int):
    contents, answers = make_data_and_answers(max_entries)
    with open("tests/{:03d}.dat".format(test_no), "wb") as f:
        f.write(contents)
    with open("tests/{:03d}.ans".format(test_no), "w") as f:
        for ans in answers:
            print(ans, end=" ", file=f)

        
def main():
    test_no = int(sys.argv[1])
    max_entries = int(sys.argv[2])
    make_test(test_no, max_entries)

if __name__=="__main__":
    main()
    
