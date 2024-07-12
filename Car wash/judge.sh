#!/bin/bash

program="./CarWashManager.out"
test_dir="./Tests"

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

for dir in "$test_dir"/*/; do
    stages_file="${dir}stages.csv"
    workers_file="${dir}workers.csv"
    input_file="${dir}input.txt"
    expected_output="${dir}output.txt"

    if [[ -f "$stages_file" && -f "$workers_file" && -f "$input_file" && -f "$expected_output" ]]; then
        result_output="$temp_dir/result.txt"
        
        $program "$stages_file" "$workers_file" < "$input_file" > "$result_output"
        
        if diff -q -w "$result_output" "$expected_output" > /dev/null; then
            echo -e "${GREEN}PASS: $(basename "$dir")${NC}"
        else
            echo -e "${RED}FAIL: $(basename "$dir")${NC}"
        fi
    else
        echo -e "${RED}Missing files in $(basename "$dir"). Skipping this test.${NC}"
    fi
done

rm -rf "$temp_dir"