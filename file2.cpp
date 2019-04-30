#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

#define LFILE "/tmp/lock-file"

int main (void)
{
  struct stat buff;
  while (0 == stat (LFILE, &buff))
  {
    printf ("waiting on file %s ...\n", LFILE);
    sleep (3);
  }
  printf ("proceeding ...\n");
  return (0);
}

