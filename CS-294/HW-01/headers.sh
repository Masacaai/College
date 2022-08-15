for f in *.txt
do
	head -1 -n 1 $f | tr [:lower:] [:upper:]
done > headers
