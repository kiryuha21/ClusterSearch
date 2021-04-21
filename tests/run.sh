#!/usr/bin/env bash

PROG_PATH=${1}

IN="
file
main_output.txt
-1
3
3
3
6
"

echo "${IN}" | eval "${PROG_PATH}"
