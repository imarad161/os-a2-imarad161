
#include "kernel/types.h"
#include "kernel/pinfo.h"
#include "user/user.h"

int
main(void)
{
  struct pinfo info[64];
  int pid = getpid();
  volatile unsigned long counter = 0;

  printf("MLFQ priority boost test starting (PID %d)\n", pid);

  for (int round = 0; round < 10; round++) {
    for (unsigned long i = 0; i < 200000000UL; i++) {
      counter += i;
    }

    int count = getpinfo(info, 64);

    if (count < 0) {
      printf("getpinfo failed\n");
      exit(1);
    }

    for (int i = 0; i < count; i++) {
      if (info[i].pid == pid) {
        printf("Round %d: LEVEL=%d TICKS=%d SCHEDULED=%d\n",
               round + 1,
               info[i].level,
               info[i].runticks,
               info[i].nsched);
        break;
      }
    }
  }

  exit(0);
}

