#!/bin/bash

echo "[+] Compiling module ..."
cd ../src/
make
cd ../test/

echo "[+] Inserting module ..."
sudo insmod ../src/hello.ko || { echo "Error while inserting"; exit 1; }

echo "[+] Verifying using dmesg ..."
dmesg | tail -n 20 > load.log
grep "Hello" load.log || echo "Expected output has not been found in dmesg"

echo "[+] Removing module ..."
sudo rmmod ../src/hello.ko || { echo "Error while removing"; exit 1; }

echo "[+] Verifying using dmesg ..."
dmesg | tail -n 20 > load.log
grep "Goodbye" load.log || echo "Expected output has not been found in dmesg"
