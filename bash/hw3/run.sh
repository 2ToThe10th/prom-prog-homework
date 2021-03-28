#!/bin/bash

while [[ $# > 0 ]]
do
    case $1 in
	-h | --help) echo "./run.sh --input <file_with_data> --train_ratio <train_ration>"; exit 0 ;;
        -i | --input) input_file=$2; shift 2;;
        -t | --train_ratio) train_ratio=$2; shift 2;;
	*) echo "$1 - Unknown argument"; exit 1;;
    esac
done

line_number=$(($(wc -l <$input_file) - 1))

lines_in_train=$(( (line_number * train_ratio) / 100 ))

data=$(tail -n+2 $input_file | shuf)

echo "train:"
echo "$data" | head -n $lines_in_train 

echo "validate:"
echo "$data" | tail -n $(($line_number - $lines_in_train))
