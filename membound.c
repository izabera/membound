#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/resource.h>
#include <sys/time.h>

int main() {
  #define SIZ (1<<28)  // 256mb > L2

  struct rlimit limit = { .rlim_cur = SIZ + 1, .rlim_max = SIZ + 1 };

  if (setrlimit(RLIMIT_MEMLOCK, &limit) == -1)
    return 1;


  unsigned char *largebuf = mmap(NULL, SIZ, PROT_READ|PROT_WRITE,
                                 // lock in memoria == no page fault
                                 MAP_PRIVATE|MAP_ANONYMOUS|MAP_LOCKED,
                                 -1, 0);
  if (largebuf == MAP_FAILED)
    return 2;



  for (size_t i = 0; i < SIZ; i++)
    largebuf[i] = random();


  // salta a caso
  size_t sum = 0;
  for (size_t i = 0; i < SIZ/1234; i++)
    sum += largebuf[random() % SIZ];

  printf("sum = %zu\n", sum);
}
