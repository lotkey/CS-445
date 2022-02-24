#!/bin/env bash

if [ $# ne 2 ]; do
    echo "Usage: ./test.sh program testDataDirectory"
    exit
fi

PROGRAM=$1
TESTDATADIR=$2
OUTPUTDIR=diffs

rm -rf ${OUTPUTDIR}
mkdir ${OUTPUTDIR}

SRCS=`${TESTDATADIR}/*.c-`
OUTPUT=`${TESTDATADIR}/*.output`

for src in ${SRCS}; do
    ${PROGRAM} -P ${src} > ${OUTPUTDIR}/${src}.output
done