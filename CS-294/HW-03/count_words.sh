awk '
{
	for(i = 1; i <= NF; ++i){
		lines[$i]++
	}
}
END{
	for(key in lines){
		print lines[key], key
	}
}'
