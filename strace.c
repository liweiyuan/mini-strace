#include <stdio.h>
#include <stdlib.h>
#include <sys/ptrace.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/user.h>
#include <sys/wait.h>
#include <unistd.h>

/**
 * 运行目标方法
 *
 * 此方法用于执行指定的目标操作。它接受一个目标对象，并调用该对象的run方法。
 *
 * @param target 目标对象，必须实现run方法
 * @throws IllegalArgumentException 如果目标对象为null或不包含run方法
 */
void run_target(const char *programname) {
  printf("Target started. Will run '%s'\n", programname);
  if (ptrace(PTRACE_TRACEME, 0, NULL, NULL) < 0) {
    perror("ptrace");
    exit(1);
  }
  execl("/bin/sh", "sh", "-c", programname, NULL);
  perror("execl");
  exit(1);
}
/**
 * @brief 运行调试器方法
 *
 * 此方法用于启动和运行调试器。它将根据提供的配置和参数
 * 初始化调试器环境，并开始调试会话。
 *
 * @param config 调试器配置对象，包含调试器所需的所有设置和选项
 * @param args 调试器运行时所需的参数列表
 *
 * @return 如果调试器成功启动并运行，则返回true；否则返回false
 */
void run_debugger(pid_t child_pid) {
  int wait_status;
  struct user_regs_struct regs;
  if (waitpid(child_pid, &wait_status, 0) < 0) {
    perror("waitpid");
    exit(1);
  }

  while (WIFSTOPPED(wait_status)) {
    if (ptrace(PTRACE_GETREGS, child_pid, 0, &regs) < 0) {
      perror("ptrace GETREGS");
      exit(1);
    }
    const char *syscall_name;
    switch (regs.orig_rax) {
    case SYS_read:
      syscall_name = "read";
      break;
    case SYS_write:
      syscall_name = "write";
      break;
    case SYS_open:
      syscall_name = "open";
      break;
    case SYS_close:
      syscall_name = "close";
      break;
    case SYS_execve:
      syscall_name = "execve";
      break;
    case SYS_exit:
      syscall_name = "exit";
      break;
    case SYS_fork:
      syscall_name = "fork";
      break;
    case SYS_wait4:
      syscall_name = "wait4";
      break;
    case SYS_mmap:
      syscall_name = "mmap";
      break;
    case SYS_munmap:
      syscall_name = "munmap";
      break;
    case SYS_mprotect:
      syscall_name = "mprotect";
      break;
    case SYS_brk:
      syscall_name = "brk";
      break;
    case SYS_rt_sigaction:
      syscall_name = "rt_sigaction";
      break;
    case SYS_rt_sigprocmask:
      syscall_name = "rt_sigprocmask";
      break;
    case SYS_rt_sigreturn:
      syscall_name = "rt_sigreturn";
      break;
    case SYS_rt_sigpending:
      syscall_name = "rt_sigpending";
      break;
    case SYS_rt_sigtimedwait:
      syscall_name = "rt_sigtimedwait";
      break;
    case SYS_rt_sigqueueinfo:
      syscall_name = "rt_sigqueueinfo";
      break;

    // other syscalls
    default:
      syscall_name = "unknown";
      break;
    }
    printf("syscall(%s) = %lld\n", syscall_name, regs.rax);
    if (ptrace(PTRACE_SYSCALL, child_pid, 0, 0) < 0) {
      perror("ptrace SYSCALL");
      exit(1);
    }
    if (waitpid(child_pid, &wait_status, 0) < 0) {
      perror("waitpid");
      exit(1);
    }
  }
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "Usage: %s <program to trace>\n", argv[0]);
    return 1;
  }

  pid_t child_pid = fork();
  if (child_pid == 0) {
    run_target(argv[1]);
  } else if (child_pid > 0) {
    run_debugger(child_pid);
  } else {
    perror("fork");
    return 1;
  }

  return 0;
}