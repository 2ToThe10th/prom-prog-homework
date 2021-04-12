#!/bin/bash

while [[ $# > 0 ]]
do
    case $1 in
	-h | --help) echo "./run.sh --worker 4 --column link --directory download_to --file labelled_newscatcher_dataset.csv"; exit 0 ;;
        -w | --worker) worker_number=$2; shift 2;;
        -c | --column) column_with_link=$2; shift 2;;
        -d | --directory) save_dir=$2; shift 2;;
	-f | --file) file=$2; shift 2;;
	*) echo "$1 - Unknown argument"; exit 1;;
    esac
done

is_header=1
column_with_info=0
links=()
while read line
do
	if [[ $is_header = 1 ]] 
	then
		is_header=0
		IFS=";"
		for column_name in $line
		do
			if [ $column_name = $column_with_link ]
			then
				break
			fi
			((column_with_info=column_with_info+1))	
		done
	else
		IFS=";" read -a data <<< $line
		links+=(${data[$column_with_info]})
	fi;
done < $file

printf "%s\n" ${links[@]} | parallel -I% -j $worker_number wget -P $save_dir
