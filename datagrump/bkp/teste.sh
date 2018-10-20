#!/bin/bash
echo ola > file.txt
data=$(cat file.txt)
#echo -e $data '\n' mundo > file.txt
echo $data mundo > file.txt
