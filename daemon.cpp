#include <sys/types.h>
#include <unistd.h>
#include <csignal>
#include <iostream>
#include <fstream>
using namespace std;

ofstream logFile;

void signalCB (int sig)
{
  logFile << ">>> caught signal " << sig << endl;
  signal (SIGUSR1, signalCB);
}

int main (void)
{
  signal (SIGUSR1, signalCB);
  signal (SIGKILL, signalCB);

  logFile.open ("./myproc.log", ios::app);

  //if (daemon(1,1) == -1)
  //{
    //logFile << "daemonisation failed." << endl;
    //return (-1);
  //}

  logFile << "running as daemon with pid " << getpid() << endl;

  while (1)
  {
    logFile << "daemon is running ..." << endl;
    sleep (10);
  }

  return (0);
}
