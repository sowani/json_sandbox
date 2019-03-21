#pragma GCC diagnostic ignored "-Weffc++"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <map>
#include "nlohmann/json.hpp"
using json = nlohmann::json;
#define DEFAULT_KEVIN_CONFIG_FILE "KevinConfig.json"
using namespace std;
json cfgRoot;

class Config
{
/*
    KevinControllerCfg
    {
	  int numAc2DcAdapters;
	  int numPvAdapters;
	  int numBatteryAdapters;
    };

	Ac2DcAdapterCfg {
      int numTempSensors;
      int numFans;
	};

    PvAdapterCfg {
      int numTempSensors;
      int numFans;
    };

	BatteryAdapterCfg {
      int numTempSensors;
      int numFans;
	};
*/
    map<string, int> KevinControllerCfg;
    map<string, int> Ac2DcAdapterCfg;
    map<string, int> PvAdapterCfg;
    map<string,int> BatteryAdapterCfg;
    vector<map<string,int>> Sensor;

  public:
    Config() {}
    ~Config() {}

    void loadConfiguration (std::string configFile);
    int getNumOfAdapter (const string AdapterName);
    int getValue (const string sensor, const string service, int index);
    void populateConfiguration();
    void populateKevinControllerConfig();
    void populateAc2DcAdapterConfig();
    //void populatePvAdapterConfig();
    //void populateBatteryAdapterConfig();
};

void Config::loadConfiguration (std::string configFile)
{
    ifstream cfgFile;
    cfgFile.open (configFile);
    cfgFile >> cfgRoot;
    cfgFile.close();
    //cout << std::setw(4) << cfgRoot << endl;
}

int Config::getNumOfAdapter (const string AdapterName)
{
  //for (int i = 0; i < cfgRoot["Sensors"]["KevinController"][AdapterName]; i++)
  //{

  //}
  return cfgRoot["Sensors"]["KevinController"][AdapterName];
}

int Config::getValue (const string sensor, const string service, int index)
{
  json sectionData;
  map<string, string> valueMap;
  string str = to_string(index);
  sectionData = cfgRoot["Sensors"][sensor][service][str];
  cout << sectionData << endl;
  //valueMap = sectionData;
  //cout << setw(4) << sectionData << endl;
  return (0);
}

void Config::populateKevinControllerConfig()
{
  int n;
  KevinControllerCfg["numAc2DcAdapters"] = getNumOfAdapter ("numAc2DcAdapters");
  KevinControllerCfg["numPvAdapters"] = getNumOfAdapter ("numPvAdapters");
  KevinControllerCfg["numBatteryAdapters"] = getNumOfAdapter ("numBatteryAdapters");
  Sensor.push_back (KevinControllerCfg);
}

void Config::populateAc2DcAdapterConfig()
{
    json sectionData;
    typedef map<string, int> map_t;
    map_t Ac2DcAdapterCfg[4];

    for (int i = 0; i < KevinControllerCfg["numAc2DcAdapters"]; i++)
    {
        sectionData = cfgRoot["Sensors"]["Ac2DcAdapter"]["adapterInfo"][i];
        Ac2DcAdapterCfg[i]["numberOfFans"] =  sectionData["numberOfFans"];
        Ac2DcAdapterCfg[i]["numberOfTemperatureSensors"] = sectionData["numberOfTemperatureSensors"];
        //Sensors.push_back(Ac2DcAdapterCfg[i]);
    }
}

void Config::populateConfiguration()
{
   populateKevinControllerConfig();
   //populateAc2DcAdapterConfig();
   //populatePvAdapterConfig();
   //populateBatteryAdapterConfig();
}

int main (void)
{
  Config cfg;

  cfg.loadConfiguration ("KevinConfig.json");
  cfg.populateConfiguration();
  cfg.getValue ("BatteryAdapter", "adapterInfo", 1);

  return (0);
}
