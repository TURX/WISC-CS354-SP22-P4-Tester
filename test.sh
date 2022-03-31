#!/usr/bin/env bash

# CS354 SP22 Project 4 Sample Tester
# Authored by Ruixuan Tu

echo "CS354 SP22 Project 4 Sample Tester"
echo "Authored by Ruixuan Tu"
echo "---------------------------------"

UNAME_S=$(uname -s)
export readonly UNAME_S
if [ "$UNAME_S" == "Darwin" ]
then
  MY_CC=clang
  export readonly MY_CC
else
  MY_CC=gcc
  export readonly MY_CC
fi
echo "[Environment]"
echo OS: "$UNAME_S"
echo Compiler: "$MY_CC"
echo "---------------------------------"

echo "[Execution]"
rm -rf test_output
mkdir test_output
for f in test_driver/*.c
do
  [[ -e "$f" ]] || break
  filename=$(basename "$f")
  filenameWithoutExt="${filename%.*}"
  echo "Running $filenameWithoutExt"
  cp "$f" driver_test.c
  make test_compile
  ./driver_test.exe > test_output/"$filenameWithoutExt".txt
  make test_clean
done
echo "---------------------------------"

echo "[Check]"
for f in expected_output/*.txt
do
  [[ -e "$f" ]] || break
  filename=$(basename "$f")
  filenameWithoutExt="${filename%.*}"
  echo "Checking $filenameWithoutExt"
  python3 judger.py "$f" test_output/"$filename"
done
echo "---------------------------------"

echo "Finished"
