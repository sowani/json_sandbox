#include <iostream>
#include <csignal>
#include <unistd.h>
using namespace std;

void signalCB (int sig)
{
  if (sig == SIGUSR1)
    cout << "usb insert event detected" << endl;
  else if (sig == SIGUSR2)
    cout << "usb eject event detected" << endl;
  signal (SIGUSR1, signalCB);
  signal (SIGUSR2, signalCB);
}

int main (void)
{
  signal (SIGUSR1, signalCB);
  signal (SIGUSR2, signalCB);
  while (1)
  {
    cout << "event handler active ..." << endl;
    sleep (5);
  }
  return (0);
}
