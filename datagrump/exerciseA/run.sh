#!/bin/bash
sudo sysctl -w net.ipv4.ip_forward=1
touch output.txt
#array=('1' '2' '3' '4' '5' '6' '7' '8' '9' '10' '11' '12' '13' '14' '15' '16' '17' '18' '19' '20' '30' '40' '50' '60' '70' '80' '90' '100' '110' '120' '130' '140' '150' '160' '170' '180' '190' '200' '220' '240' '280' '300' '350') 
array=('1' '2')
cd ..
for i in ${array[@]}
do
	echo "Running with window size = "$i
	sed -i "s/unsigned int the_window_size =.*/unsigned int the_window_size = "$i";/" controller.cc
        cd ..
        make
        cd datagrump
        ./run-contest jose_wilson &> "exerciseA/tmp.txt"
        throughput=$(cat "exerciseA/tmp.txt" | grep "Average throughput:" | cut -d: -f2 | cut -d " " -f2)
	echo "Throughput: " $throughput
	delay=$(cat  "exerciseA/tmp.txt" | grep "95th percentile signal delay:" | cut -d: -f2 | cut -d " " -f2)
	echo "Delay: " $delay
	echo $throughput $delay >> 'exerciseA/output.txt'
	rm "exerciseA/tmp.txt"
done
echo "Making plot"
python exerciseA/plot.py
echo "Finish"
