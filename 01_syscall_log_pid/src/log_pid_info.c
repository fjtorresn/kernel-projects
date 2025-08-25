/**
 * This code has been extracted from kernel/sys.c to implement the
 * syscall log_pid_info().
 *
 * This file is not to be compiled, it is included as reference.
 */


SYSCALL_DEFINE0(log_pid_info) {
    struct timespec64 ts;
    ktime_get_rel_ts64(&ts);
    printk(KERN_INFO "Syscall log_pid_info: PID=%d UID=%d Time=%lld.%09ld\n", current->pid, current_uid().val, (s64)ts.tv_sec, ts.tv_nsec);
    return 0;
}
