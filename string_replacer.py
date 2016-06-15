#!/usr/bin/env python
import sys


def is_end_of_listening(input_data):
    return input_data.startswith("-q")


def get_adjusted_output(sequence, cout):
    if cout > 9:
        return "0{0}".format(sequence)
    else:
        return "{0}{1}".format(cout, sequence)


def is_letter_in_sequence(letter, sequence):
    return sequence.find(letter) != -1


def get_count_and_erase_sequence(input_data, pattern):
    cout = 1
    while input_data.startswith(pattern):
        cout += 1
        input_data = input_data[len(pattern):]
    return input_data, cout


def replace_sequence(input_data):
    my_sequence = ""
    output = ""

    while input_data != "":
        if my_sequence == "" or not is_letter_in_sequence(input_data[0], my_sequence):
            my_sequence += input_data[0]
            input_data = input_data[1:]
        else:
            input_data, cout = get_count_and_erase_sequence(input_data, my_sequence)
            output += get_adjusted_output(my_sequence, cout)
            my_sequence = ""
    if my_sequence != "":
        output += get_adjusted_output(my_sequence, 1)
    print(output)

input_data = str(raw_input())
while not is_end_of_listening(input_data):
    if not input_data.isalpha():
        sys.exit("ERROR: Wrong input. Contains non alphabetic characters")
    replace_sequence(input_data)
    input_data = str(raw_input())
