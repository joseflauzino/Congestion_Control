#!/bin/bash
#while read line; do
#	echo $line
#done < teste.txt
data=$(cat -e 'teste.txt')
echo $data
