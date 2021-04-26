#!/usr/bin/env bash

PROG_PATH=${1}

IN1="manually
1
1
100
0
100
0
100
7
2
2
main_output.txt
-1
1
3
3
6"

IN2="file
main_output.txt
-1
1
3
3
6"

echo "${IN1}" | eval "${PROG_PATH}"

echo "${IN2}" | eval "${PROG_PATH}"
