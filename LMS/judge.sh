#!/bin/bash

program="./utms.out"
majors="./Tests/csv/majors.csv"
students="./Tests/csv/students.csv"
courses="./Tests/csv/courses.csv"
teachers="./Tests/csv/teachers.csv"
test_dir="./Tests/"
result_dir="./result"

GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' # No Color

temp_dir=$(mktemp -d)

echo "Building the project..."
make

if [ $? -ne 0 ]; then
    echo -e "${RED}Build failed. Aborting tests.${NC}"
    rm -rf "$temp_dir"
    exit 1
fi

find "$test_dir" -type f -name "*.in" | while read -r input_file; do
    expected_output="${input_file%.in}.out"
    
    result_output="$temp_dir/$(basename "${input_file%.in}.out")"
    
    $program $majors $students $courses $teachers < "$input_file" > "$result_output"
    
    if diff -q "$result_output" "$expected_output" > /dev/null; then
        echo -e "${GREEN}PASS: $(basename "$input_file")"
    else
        echo "${RED}FAIL: $input_file"

    fi
done

rm -rf "$temp_dir"