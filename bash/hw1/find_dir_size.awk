BEGIN {
	files_full_size = 0
	directory_size = 0
}

{
	dir_letter=substr($1, 1, 1)
	size = $5
	if (dir_letter == "d") {
		if (directory_size == 0)
			directory_size = size 
		print $9
	}
	else if (dir_letter == "-")
		files_full_size += size
}

END {
	print files_full_size + directory_size
}
