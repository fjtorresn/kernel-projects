#!/bin/bash

echo "[+] Compiling module ..."
cd ../src/
make
cd ../test/
gcc test.c -o test

echo "[+] Inserting module ..."
if lsmod | grep mycdev > /dev/null; then
    sudo rmmod mycdev;
fi
sudo insmod ../src/mycdev.ko || { echo "Error while inserting"; exit 1; }
    

echo "[+] Getting device number ..."
dmesg | tail -n 1 > tmp.log
DEV_NUM=$(grep "Major device number: \d+" -oP tmp.log | grep "\d+" -oP)

if [ -n "$DEV_NUM" ]; then
    echo "[+] Creating a device file ..."
    sudo mknod /dev/mydev0 c $DEV_NUM 0
#    sudo cat /dev/mydev0
else
    echo "Error while getting device number";
    exit 1;
fi
echo "[+] Writing into the file ..."
sudo echo "This is a test for reading and writing" > /dev/mydev0
echo "[+] Checking dmesg ..."
dmesg | tail -n 1
echo "[+] Reading the file ..."
sudo ./test
echo "[+] Checking dmesg ..."
dmesg | tail -n 10

echo "[+] Removing module ..."
sudo rmmod ../src/mycdev.ko || { echo "Error while removing"; exit 1; }
rm tmp.log
