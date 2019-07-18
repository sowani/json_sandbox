#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv)
{
  int i = 0;
  int datasize = 0;
  FILE *fp;
  unsigned char data = 0;

  if (argc < 2)
  {
    printf ("Usage: %s <size> <outfile>\n", argv[0]);
    return -1;
  }

  datasize = atoi (argv[1]);

  fp = fopen (argv[2], "w");

  for (i = 0; i < datasize; i++)
    fprintf (fp, "%x\n", data++);

  fclose(fp);
  return (0);
}
