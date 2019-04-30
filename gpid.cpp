#include <sys/types.h>
#include <unistd.h>
#include <iostream>
using namespace std;

int main (void)
{
  cout << "pid: " << getpid() << endl;
  return (0);
}
