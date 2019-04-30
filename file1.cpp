#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

#define LFILE "/tmp/lock-file"

int main (void)
{
  int fd;
  fd = open (LFILE, O_CREAT | O_EXCL, 7000);
  if (fd == -1)
  {
    printf ("unable to create lock file\n");
    return (1);
  }
  sleep (300);
  close (fd);
  remove (LFILE);
  return (0);
}
