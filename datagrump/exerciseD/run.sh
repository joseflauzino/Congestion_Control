#!/bin/bash
###################
# Exercise C script
###################
echo "Running Exercise D"
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
cp controller_exeD.cc controller.cc
for i in ${array[@]}
do
	echo "Running with window size = "$i
	sed -i "s/unsigned int Controller::timeout_ms(){ return.*/unsigned int Controller::timeout_ms(){ return "$i"; }/" controller.cc
    cd ..
    make
    cd datagrump
    ./run-contest RedBullTeDaAsas &> "exerciseD/tmp.txt"
    throughput=$(cat "exerciseD/tmp.txt" | grep "Average throughput:" | cut -d: -f2 | cut -d " " -f2)
	echo "Throughput: " $throughput
	delay=$(cat  "exerciseD/tmp.txt" | grep "95th percentile signal delay:" | cut -d: -f2 | cut -d " " -f2)
	echo "Delay: " $delay
	echo $throughput $delay >> "exerciseD/output.txt"
	rm "exerciseD/tmp.txt"
done
cd exerciseD

echo "Making plot"
python plot.py
echo "Finish"
