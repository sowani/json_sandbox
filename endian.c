#include <stdio.h>

int main (void)
{
  /*
  printf ("unsigned char = %ld\n", sizeof (unsigned char));
  printf ("unsigned int = %ld\n", sizeof (unsigned int));
  printf ("unsigned short = %ld\n", sizeof (unsigned short));
  */

  unsigned int num = 0xabcd;
  unsigned char *arr;
  arr = (unsigned char *) &num;
  printf ("[0xabcd] 1: %02x, 0: %02x\n", arr[1], arr[0]);

  num = 0x0123;
  arr = (unsigned char *) &num;
  printf ("[0x0123] 1: %02x, 0: %02x\n", arr[1], arr[0]);
  return (0);
}
