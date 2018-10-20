#!/bin/bash
taxa=$(cat result_exeA/windowsize1.txt | grep "Average throughput:" | cut -d: -f2 | cut -d ' ' -f2)
echo $taxa
teste=10
delay=$(cat result_exeA/windowsize1.txt | grep "95th percentile signal delay:" | cut -d: -f2 | cut -d ' ' -f2)
echo $delay
#average=$(($teste + $delay))
average= echo "scale=2 ; $taxa / $delay" | bc
echo $average
