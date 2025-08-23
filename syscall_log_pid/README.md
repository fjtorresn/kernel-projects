# 1. Syscall `log_pid_info()`

## Description
This project implements a syscall in the Linux 6.8 kernel that logs PID, UID and timestamp of the process that invokes it.

## Components
- **Syscall**: `log_pid_info()` defined in `kernel/sys.c`
- **Patch**: located in `patch/0001-add-log_pid_info.patch`
- **Test**: C program and Shell script to validate the syscall.
