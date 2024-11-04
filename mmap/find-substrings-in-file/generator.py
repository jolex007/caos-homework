#!/usr/bin/python3

import random
import os
import sys


def make_data(count: int, phrase: str):
    return phrase * count


def make_answers(contents: str, pattern: str):
    start = 0
    result = []
    while -1!=start and start<len(contents):
        start = contents.find(pattern, start)
        if -1!=start:
            result += [start]
            start += 1
    return result
        

def make_test(test_no: int, phrases_count: int, phrase: str, pattern: str):
    contents = make_data(phrases_count, phrase)
    answers = make_answers(contents, pattern)
    os.mkdir("tests/{:03d}.dir".format(test_no))
    with open("tests/{:03d}.dir/in.dat".format(test_no), "wb") as f:
        f.write(contents.encode("utf-8"))
    with open("tests/{:03d}.ans".format(test_no), "w") as f:
        for ans in answers:
            print(ans, end=" ", file=f)
    with open("tests/{:03d}.inf".format(test_no), "w") as f:
        print("params = in.dat \"{}\"".format(pattern), file=f)
    with open("tests/{:03d}.dat".format(test_no), "w") as f:
        pass

        
def main():
    test_no = int(sys.argv[1])
    phrases_count = int(sys.argv[2])
    phrase = sys.argv[3]
    pattern = sys.argv[4]                       
    make_test(test_no, phrases_count, phrase, pattern)

if __name__=="__main__":
    main()
    
