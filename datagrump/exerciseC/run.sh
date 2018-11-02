#!/bin/bash
###################
# Exercise C script
###################
echo "Running Exercise C"
sudo sysctl -w net.ipv4.ip_forward=1
if [ -e "output.txt" ] ; then
	rm output.txt
fi
touch output.txt
cd ..
if [ -e "controller.cc" ] ; then
rm controller.cc
fi
array=('50' '55' '60' '65' '70')
cp controller_exeC.cc controller.cc
for i in ${array[@]}
do
	echo "Running with window size = "$i
	sed -i "s/unsigned int Controller::timeout_ms(){ return.*/unsigned int Controller::timeout_ms(){ return "$i"; }/" controller.cc
    cd ..
    make
    cd datagrump
    ./run-contest jose_wilson &> "exerciseC/tmp.txt"
    throughput=$(cat "exerciseC/tmp.txt" | grep "Average throughput:" | cut -d: -f2 | cut -d " " -f2)
	echo "Throughput: " $throughput
	delay=$(cat  "exerciseC/tmp.txt" | grep "95th percentile signal delay:" | cut -d: -f2 | cut -d " " -f2)
	echo "Delay: " $delay
	echo $throughput $delay >> "exerciseC/output.txt"
	rm "exerciseC/tmp.txt"
done
cd exerciseC

echo "Making plot"
python plot.py
echo "Finish"
