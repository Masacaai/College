for f in $*
do
	if [ -e $f ]
	then
		if [ -d $f ]
		then
			echo -e "$f is a directory"
		else
			if sort -C $f 
			then
				echo -e "$f is sorted"
			else
				echo -e "$f is not sorted"
			fi
		fi
	else
		echo -e "$f does not exist"
	fi
done
