#!/bin/bash
sudo sysctl -w net.ipv4.ip_forward=1
cd ..
make
cd datagrump
./run-contest jose_wilson
