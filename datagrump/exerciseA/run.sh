#!/bin/bash
###################
# Exercise A script
###################
echo "Running Exercise A"

#------------------
# Testing various window sizes
#------------------
sudo sysctl -w net.ipv4.ip_forward=1
if [ -e "output.txt" ] ; then
	rm output.txt
fi
touch output.txt
#array=('1' '2' '3' '4' '5' '6' '7' '8' '9' '10' '11' '12' '13' '14' '15' '16' '17' '18' '19' '20' '30' '40' '50' '60' '70' '80' '90' '100' '120' '140' '160' '180' '200' '220' '240' '280' '300' '350')
array=('1')
cd ..
if [ -e "controller.cc" ] ; then
rm controller.cc
fi
cp controller_exeA.cc controller.cc
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
	echo $throughput $delay >> "exerciseA/output.txt"
	rm "exerciseA/tmp.txt"
done
cd exerciseA

#------------------
# Removing best.txt files
#------------------
for a in {1..30}
do
	if [ -e "best/best$a.txt" ] ; then	
		rm best/best$a.txt
	fi
done


#------------------
# Running the best window size values
#------------------
best_array=('10' '11' '12' '13' '14' '15')
for x in {1..30}
do
	if [ "$x" -ne "1" ] ; then
		cd exerciseA
	fi
	touch best/best$x.txt
	for j in ${best_array[@]}
	do
		echo
		echo "---- BEST ----"
		echo "Test$x: Running with window size = "$j
		if [ "$j" -eq "10" ] ; then
			cd ..
		fi
		sed -i "s/unsigned int the_window_size =.*/unsigned int the_window_size = "$j";/" controller.cc
		cd ..
		make
		cd datagrump
		./run-contest jose_wilson &> "exerciseA/tmp.txt"
		throughput=$(cat "exerciseA/tmp.txt" | grep "Average throughput:" | cut -d: -f2 | cut -d " " -f2)
		echo "Throughput: " $throughput
		delay=$(cat  "exerciseA/tmp.txt" | grep "95th percentile signal delay:" | cut -d: -f2 | cut -d " " -f2)
		echo "Delay: " $delay
		echo $throughput $delay >> "exerciseA/best/best$x.txt"
		rm "exerciseA/tmp.txt"
	done
done
cd exerciseA

echo "Making plots"
python plot.py
echo "Finish"
