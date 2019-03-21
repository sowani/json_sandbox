#include <iostream>
#include <iomanip>
#include <fstream>
#include "nlohmann/json.hpp"
#include <vector>
using namespace std;
using json = nlohmann::json;
json cfgRoot;

auto sampleJSON = R"(
{
    "KevinAc2DcAdapter1Configuration" : {
        "systemBusEnergy": 30
    },
    "KevinAc2DcAdapter2Configuration" : {
        "externalBusEnergy": 50
    }
}
)";

int main (void)
{
    json jData = json::parse(sampleJSON);
    cout << setw(4) << jData << endl;
}
