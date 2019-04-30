#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include <string>
using namespace std;

int main (void)
{
  std::string msgStr;
  pid_t pid = getpid();
  const char *compID = "XYZ";

  msgStr = pid + compID;

  return (0);
}
