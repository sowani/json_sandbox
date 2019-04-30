#include <iostream>
#include <iomanip>
#include <fstream>
#include "nlohmann/json.hpp"
using namespace std;
using json = nlohmann::json;
json jroot;
ofstream file1;
ifstream file2;

void readlog()
{
  string line;
  json jstr;
  if (file2.is_open())
  {
    while (getline (file2, line))
    {
      jstr = json::parse(line);
      cout << setw(4) << jstr << endl;
    }
  }
}

void writelog()
{
  json j;
  string str;
  j["timestamp"] = "time";
  j["componentID"] = "cID";
  j["severity"] = "critical";
  j["messageText"] = "19332:OTA:OTA service failed to start";
  //str = j.dump();
  file1 << j.dump() << endl;
}

int main (void)
{
  file1.open ("./log_entry.json", ios::app);
  writelog();
  writelog();
  file1.close();

  file2.open ("./log_entry.json");
  readlog();
  file2.close();
  return (0);
}
