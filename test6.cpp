#include <iostream>
#include <fstream>
#include <iomanip>
#include "nlohmann/json.hpp"
using json = nlohmann::json;
using namespace std;

int main (void)
{
  json cfgRoot;
  ifstream cfgFile;
  cfgFile.open ("UpstreamConfig.json");
  cfgFile >> cfgRoot;
  cfgFile.close();

  if (cfgRoot.count("otaFrequency") != 0)
  {
    int x = cfgRoot["otaFrequency"];
    cout << 2*x << endl;
  }
  else
    cout << "otaFrequency not defined." << endl;
  return (0);
}
