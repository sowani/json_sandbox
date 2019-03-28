#pragma GCC diagnostic ignored "-Weffc++"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <map>
#include "nlohmann/json.hpp"
using json = nlohmann::json;
#define DEFAULT_KEVIN_CONFIG_FILE "KevinConfig.json"
using namespace std;

class Config
{
  protected:
    json cfgRoot;
  public:
    Config() {}
    ~Config() {}

    bool isKeyPresent (std::string key);
    void loadConfiguration (std::string configFile);
    vector<int> getNumOfAdapter (const string AdapterName);
    map<string,string> getValue (const string sensor, const string service, int index);
    void setKevinID (int kevinID);
    void setKevinID (string kevinID);
    bool updateSensorID (const std::string sensorName, string sensorID);
    bool updateConfigurationValue (const std::string sensorName,
		string sensorID, const std::string service,
		const std::string key, int value);
    bool updateConfigurationValue (const std::string sensorName,
		string sensorID, const std::string service,
		const std::string key, string value);
    void printConfig() { cout << setw(4) << cfgRoot << endl; }
};

bool Config::updateSensorID (const std::string sensorName, string sensorID)
{
  bool retval = false;
  for (int i = 0; i < cfgRoot["Sensors"]["KevinController"]["KevinController"][sensorName]; i++)
  {
    if (cfgRoot["Sensors"][sensorName]["IDs"][i] == "")
    {
      cfgRoot["Sensors"][sensorName]["IDs"][i] = sensorID;
      retval = true;
      break;
    }
    else
    {
      retval = false;
    }
  }
  return (retval);
}

bool Config::updateConfigurationValue (const std::string sensorName,
		string sensorID, const std::string service,
		const std::string key, int value)
{
  bool retval = false;
  int index = 0;
  // from the ID, find the index.
  for (int i = 0; i < cfgRoot["Sensors"]["KevinController"]["KevinController"][sensorName]; i++)
  {
    if (cfgRoot["Sensors"][sensorName]["IDs"][i] == sensorID)
    {
      index = i;
      retval = true;
      break;
    }
  }

  if (retval == true)
    cfgRoot["Sensors"][sensorName][service][index][key] = value;

  return (retval);
}

bool Config::updateConfigurationValue (const std::string sensorName,
		string sensorID, const std::string service,
		const std::string key, std::string value)
{
  bool retval = false;
  int index = 0;
  // from the ID, find the index.
  for (int i = 0; i < cfgRoot["Sensors"]["KevinController"]["KevinController"][sensorName]; i++)
  {
    if (cfgRoot["Sensors"][sensorName]["IDs"][i] == sensorID)
    {
      index = i;
      retval = true;
      break;
    }
  }

  if (retval == true)
    cfgRoot["Sensors"][sensorName][service][index][key] = value;

  return (retval);
}

bool Config::isKeyPresent (std::string key)
{
    if (cfgRoot.find (key) == cfgRoot.end())
    {
        return (false);
    }
    return (true);
}

void Config::loadConfiguration (std::string configFile)
{
    ifstream cfgFile;
    cfgFile.open (configFile);
    cfgFile >> cfgRoot;
    cfgFile.close();
    //cout << std::setw(4) << cfgRoot << endl;
}

vector<int> Config::getNumOfAdapter (const string AdapterName)
{
  json sectionData;
  vector<int> adapterIDs;

  for (int i = 0; i < cfgRoot["Sensors"]["KevinController"]["KevinController"][AdapterName]; i++)
  {
    sectionData = cfgRoot["Sensors"][AdapterName]["IDs"];
    //cout << sectionData[i] << endl;
    adapterIDs.push_back(sectionData[i]);
  }
  return adapterIDs;
}

map<string,string> Config::getValue (const string sensor, const string service, int index)
{
  json sectionData;
  map<string, string> valueMap;

  sectionData = cfgRoot["Sensors"][sensor][service][index];
  cout << sectionData << endl;

  for (auto it = sectionData.begin(); it != sectionData.end(); ++it)
  {
    //std::cout << "key: " << it.key() << ", value:" << it.value() << '\n';
    //valueMap[it.key()] = to_string(int(it.value())); -- assuming value is int
    valueMap[it.key()] = it.value();
  }
  return (valueMap);
}

void Config::setKevinID (int kevinID)
{
  cfgRoot["kevinID"] = kevinID;
}

void Config::setKevinID (string kevinID)
{
  cfgRoot["kevinID"] = kevinID;
}

int main (void)
{
  bool res;
  Config cfg;
  vector<int> tt1;
  map<string, string> tt2;

  cfg.loadConfiguration (DEFAULT_KEVIN_CONFIG_FILE);
  res = cfg.updateConfigurationValue ("PvAdapter", "2002", "ComponentID", "ManufactureWeek", "eight");
  //cout << "res = " << res << endl;
  //cfg.printConfig();


  // ------- tested -------
  //res = cfg.updateSensorID ("Ac2DcAdapter", 1001);
  //cout << "res = " << res << endl;
  //res = cfg.updateConfigurationValue ("Ac2DcAdapter", 1001, "AdapterInfo", "NumTempSensors", 6);
  //cout << "res = " << res << endl;
  //res = cfg.updateConfigurationValue ("Ac2DcAdapter", 1001, "AdapterInfo", "NumberOfFans", 4);
  //cout << "res = " << res << endl;
  //cfg.printConfig();

  //res = cfg.updateSensorID ("Ac2DcAdapter", 1001);
  //cout << "res = " << res << endl;
  //tt1 = cfg.getNumOfAdapter ("Ac2DcAdapter");
  //cout << "Ac2DcAdapter: " << tt1.size() << endl;
  //cout << "IDs: ";
  //for (int i = 0; i < tt1.size(); i++)
    //cout << tt1[i] << " ";
  //cout << endl;

  //res = cfg.updateSensorID ("Ac2DcAdapter", 1002);
  //cout << "res = " << res << endl;
  //tt1 = cfg.getNumOfAdapter ("Ac2DcAdapter");
  //cout << "Ac2DcAdapter: " << tt1.size() << endl;
  //cout << "IDs: ";
  //for (int i = 0; i < tt1.size(); i++)
    //cout << tt1[i] << " ";
  //cout << endl;

  //res = cfg.updateSensorID ("Ac2DcAdapter", 1003);
  //cout << "res = " << res << endl;

  //tt1 = cfg.getNumOfAdapter ("KevinController");
  //cout << "KevinController: " << tt1.size() << endl;
  //cout << "IDs: ";
  //for (int i = 0; i < tt1.size(); i++)
    //cout << tt1[i] << " ";
  //cout << endl;

  //tt1 = cfg.getNumOfAdapter ("Ac2DcAdapter");
  //cout << "Ac2DcAdapter: " << tt1.size() << endl;
  //cout << "IDs: ";
  //for (int i = 0; i < tt1.size(); i++)
    //cout << tt1[i] << " ";
  //cout << endl;

  //tt1 = cfg.getNumOfAdapter ("PvAdapter");
  //cout << "PvAdapter: " << tt1.size() << endl;
  //cout << "IDs: ";
  //for (int i = 0; i < tt1.size(); i++)
    //cout << tt1[i] << " ";
  //cout << endl;

  //tt1 = cfg.getNumOfAdapter ("BatteryAdapter");
  //cout << "BatteryAdapter: " << tt1.size() << endl;
  //cout << "IDs: ";
  //for (int i = 0; i < tt1.size(); i++)
    //cout << tt1[i] << " ";
  //cout << endl;

  tt2 = cfg.getValue ("Ac2DcAdapter", "AdapterInfo", 1);
  cout << tt2["NumberOfFans"] << ", ";
  cout << tt2["NumTempSensors"] << endl;

  return (0);
}
