#include <stdio.h>

int main (void)
{
  printf ("short = %lu\n", sizeof (short));
  printf ("unsigned short = %lu\n", sizeof (unsigned short));
  printf ("unsigned short int = %lu\n", sizeof (unsigned short int));

  char x = 0x1;
  printf ("%d\n", x);
  x = 0x0;
  printf ("%d\n", x);
  return (0);
}
