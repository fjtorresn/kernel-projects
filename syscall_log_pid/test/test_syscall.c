#include <unistd.h>
#include <sys/syscall.h>
#include <stdio.h>

#define SYS_log_pid_info 462

int main() {
    long ret = syscall(SYS_log_pid_info);
    if (ret == 0) {
        printf("Syscall log_pid_info executed successfully. \n");
    } else {
        perror("Syscall failed");
    }
    return 0;
}
