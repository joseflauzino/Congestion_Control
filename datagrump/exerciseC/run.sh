#!/bin/bash
###################
# Exercise C script
###################
echo "Running Exercise C"
sudo sysctl -w net.ipv4.ip_forward=1
cd ..

if [ -e "controller.cc" ] ; then
rm controller.cc
fi

#cp controller_exeC.cc controller.cc
cp controller_exeC_tmp.cc controller.cc
cd ..
make
cd datagrump
./run-contest jw
echo "Finish"
