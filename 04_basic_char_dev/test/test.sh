#!/bin/bash

echo "[+] Compiling module ..."
cd ../src/
make
cd ../test/

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
    sudo cat /dev/mydev0

    echo "[+] Checking dmesg ..."
    dmesg | tail -n 1 > tmp.log
    grep "Read is called" tmp.log || echo "Expected output has not been found in dmesg"
else
    echo "Error while getting device number";
    exit 1;
fi

echo "[+] Removing module ..."
sudo rmmod ../src/mycdev.ko || { echo "Error while removing"; exit 1; }
rm tmp.log
