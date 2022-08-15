awk '
{
	lines[$0]++
}
END{
	for(key in lines){
		print lines[key], key
	}
}'
