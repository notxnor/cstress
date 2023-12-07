#!/bin/bash
set -e
chmod +x prep_efficient.sh
chmod +x prep_correct.sh
rm -rf ./.stress
rm -rf ./failed.in
mkdir .stress

i=1
max_tests=$1
diff_found=0

RED='\033[1;31m'
GREEN='\033[1;32m'
DEFAULT='\033[0m'
ONBLUE='\033[0;104m' 

./prep_efficient.sh
./prep_correct.sh
g++ -std=c++2a generator.cpp -o ./.stress/generator

while [ $i -le $max_tests ]
do
    ./.stress/generator > ./.stress/tcase
    ./.stress/eff < ./.stress/tcase > ./.stress/p_out
    ./.stress/crr < ./.stress/tcase > ./.stress/w_out
    if diff -B -F --side-by-side --ignore-space-change ./.stress/p_out ./.stress/w_out > ./.stress/dr; then
        echo -e "Test $i: ${GREEN}OK${DEFAULT}"
    else
        echo -e "Test $i: ${RED}FAIL${DEFAULT}"
        diff_found=1
        break
    fi
    i=$((i+1))
done

if [ $diff_found -eq 1 ]
then
    cat ./.stress/tcase > ./failed.in
    echo ""
    echo -e "${ONBLUE}Input:${DEFAULT}"
    cat ./.stress/tcase
    echo ""
    echo -e "${ONBLUE}Output:${DEFAULT}"
    cat ./.stress/p_out
    echo ""
    echo ""
    echo -e "${ONBLUE}Expected:${DEFAULT}"
    cat ./.stress/w_out
    echo ""
    echo ""
else
    echo -e "${GREEN}OK ${max_tests} test cases.${DEFAULT}"
fi

rm -rf ./.stress
