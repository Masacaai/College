for f in $*
do
	for num in {1..1000}
	do 
		echo $num $f 
	done > 1000_$f.txt

done
