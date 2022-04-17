#!/bin/bash

if [ $# -ne 1 ]
then
    echo "Only one argument is allowed."
    exit
fi

./c- -M ./testData/$1.c- > .tmp_test
diff -y --width=209 .tmp_test ./testData/$1.out
rm .tmp_test