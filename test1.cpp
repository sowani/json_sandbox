#include <iostream>
#include <iomanip>
#include <fstream>
#include "nlohmann/json.hpp"
#include <vector>
using namespace std;
using json = nlohmann::json;
json cfgRoot;

int main (void)
{
    json root;
    ifstream file ("../UpstreamConfig.json");
    file >> root;
    file.close();

    cout << root["kevinID"] << endl;
    cout << root["logTargets"][0] << endl;
    cout << root["logTargets"][1] << endl;
    cout << root << endl;

    std::vector<std::string> vec = root["logTargets"];
    cout << "vector values:" << endl;
    for (vector<std::string>::iterator it = vec.begin(); it != vec.end(); it++)
      cout << *it << endl;

    //auto it = root.find ("junk");
    auto it = root.find ("kevinID");
    if (it == root.end() )
      cout << "not found" << endl;
    else
      cout << "found" << endl;

    root["newEntry"] = "testing";
    root["cfgVersion"] = "1.0";
    cout << root << endl;

    ofstream file1 ("test.conf");
    file1 << setw(2) << root;
    file1.close();

    return (0);
}
