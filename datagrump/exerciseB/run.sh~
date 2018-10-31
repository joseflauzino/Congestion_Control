#!/bin/bash
###################
# Exercise B script
###################
echo "Running Exercise B"
sudo sysctl -w net.ipv4.ip_forward=1
cd ..

if [ -e "controller.cc" ] ; then
rm controller.cc
fi

cp controller_exeB.cc controller.cc
cd ..
make
cd datagrump
./run-contest jose_wilson
echo "Finish"
