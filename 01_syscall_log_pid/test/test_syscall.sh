#!/bin/bash

echo "[+] Compiling test_syscall.c ..."
g++ -o test_syscall test_syscall.c

echo "[+] Executing syscall ..."
./test_syscall

echo "[+] Verifying logs in dmesg ..."
dmesg | tail -n 10 | grep "Syscall log_pid_info"
