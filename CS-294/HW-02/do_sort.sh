for f in $*
do
	if sort -C $f
	then
		:
	else
		mv "$f" "${f%.txt}.orig.txt"
		sort "${f%.txt}.orig.txt" > $f
	fi

done
