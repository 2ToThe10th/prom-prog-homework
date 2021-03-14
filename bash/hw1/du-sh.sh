#!/bin/bash

if [ $# -lt 1 ];
then
	echo "Please, write directory name as first argument to discover its disk usage"
	exit 1
fi

awk_script=$(realpath find_dir_size.awk)

function find_dir_size {
	dir_info=($(ls -al | awk -f $awk_script))
	file_sum_size_index=$(( ${#dir_info[@]} - 1 ))
	dir_size=${dir_info[$file_sum_size_index]}
	for i in $(seq 2 $((file_sum_size_index - 1)) )
	do
		cd ${dir_info[$i]}
		dir_size=$(($dir_size + $(find_dir_size)))
		cd ..
	done
	echo $dir_size
	return 0
}

cd $1

find_dir_size

