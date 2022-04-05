# CS354 SP22 Project 4 Sample Tester
# Authored by Ruixuan Tu

import sys
import re

if __name__ == '__main__':
    if len(sys.argv) != 3:
        print("Usage: python3 " + sys.argv[0] + " <expected_output> <actual_output>")
        exit(1)
    expected_output_src = sys.argv[1]
    actual_output_src = sys.argv[2]
    expected_output = open(expected_output_src, 'r').read().split('\n')
    actual_output = open(actual_output_src, 'r').read().split('\n')
    last_expected_pointer = 0
    last_actual_pointer = 0
    for line_num in range(len(expected_output)):
        expected_output_line = expected_output[line_num]
        actual_output_line = actual_output[line_num]
        if len(expected_output_line) != len(actual_output_line):
            print("Output length mismatch at line " + str(line_num + 1))
            exit(1)
        if len(expected_output_line) == 91 and expected_output_line[0] == '>' and actual_output_line[0] == '>':
            expected_output_line_with_pointer = re.sub(r' +', ' ', expected_output_line)
            expected_output_line_with_pointer = expected_output_line_with_pointer[2:]
            parsed_expected_output = expected_output_line_with_pointer.split(' ')

            actual_output_line_with_pointer = re.sub(r' +', ' ', actual_output_line)
            actual_output_line_with_pointer = actual_output_line_with_pointer[2:]
            parsed_actual_pointer = actual_output_line_with_pointer.split(' ')

            if parsed_expected_output[0] != parsed_actual_pointer[0] \
                    or parsed_expected_output[1] != parsed_actual_pointer[1] \
                    or parsed_expected_output[4] != parsed_actual_pointer[4] \
                    or parsed_expected_output[5] != parsed_actual_pointer[5] \
                    or parsed_expected_output[6] != parsed_actual_pointer[6] \
                    or parsed_expected_output[7] != parsed_actual_pointer[7] \
                    or parsed_expected_output[8] != parsed_actual_pointer[8]:
                print("Block info mismatch at line " + str(line_num + 1))
                exit(1)

            expected_pointer = int(parsed_expected_output[2], 16)
            actual_pointer = int(parsed_actual_pointer[2], 16)

            if last_expected_pointer == 0 and last_actual_pointer == 0:
                last_expected_pointer = expected_pointer
                last_actual_pointer = actual_pointer

            if expected_pointer - last_expected_pointer != actual_pointer - last_actual_pointer:
                print("Block pointer mismatch at line " + str(line_num + 1))
                exit(1)

            expected_pointer = int(parsed_expected_output[3], 16)
            actual_pointer = int(parsed_actual_pointer[3], 16)

            if expected_pointer - last_expected_pointer != actual_pointer - last_actual_pointer:
                print("Block pointer mismatch at line " + str(line_num + 1))
                exit(1)
        else:
            if expected_output_line != actual_output_line:
                print("Output mismatch at line " + str(line_num + 1))
                exit(1)
    print("Output correct")
