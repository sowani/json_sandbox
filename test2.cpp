#include <iostream>
#include <iomanip>
#include <fstream>
#include "nlohmann/json.hpp"
#include <vector>
using namespace std;
using json = nlohmann::json;
json cfgRoot;
json jData;

//void readSampleUpdates(void)
//{
//    jData = json::parse(sampleJSON);
//    cout << setw(4) << jData << endl;
//}

void loadConfiguration (std::string configFile)
{
    ifstream cfgFile;
    cfgFile.open (configFile);
    cfgFile >> cfgRoot;
    cfgRoot["hasConfigChanged"] = false;
    cfgFile.close();
    cout << std::setw(4) << cfgRoot << endl;
}

std::string getConfigurationKeyValue (std::string key)
{
	if (cfgRoot[key].is_structured())
		return (cfgRoot[key].dump());
	if (cfgRoot[key].is_string())
		return cfgRoot[key];
	if (cfgRoot[key].is_number())
		return cfgRoot[key].dump();
}

bool isKeyPresent (std::string key)
{
    if (cfgRoot.find (key) == cfgRoot.end())
    {
        return (false);
    }
    return (true);
}

void printConfiguration()
{
    int numAdapters = cfgRoot["numAc2DcAdapters"].get<int>();
    cout << "Found " << numAdapters << " adapters." << endl;

    // query a parameter for each adapter.
    string adapterName;
    for (int i = 0; i < numAdapters; i++)
    {
    	adapterName = "KevinAc2DcAdapter" + to_string(i+1) + "Configuration";
        json jData = json::parse(getConfigurationKeyValue (adapterName));
        cout << jData["systemBusEnergy"] << endl;
        cout << jData["externalBusEnergy"] << endl;
    }
    cout << cfgRoot["dummyVar"] << endl;
}

bool updateConfigurationByKey (const std::string key, const std::string value, bool isComposite)
{
    if (isKeyPresent (key))
    {
        if (isComposite)
        {
            cout << "need to handle composite case." << endl;
            json jData = json::parse (value);
            // TODO: for each value in jData, update corresponding
            //       value in cfgRoot.
        }
        else
        {
            cfgRoot[key] = value;
        }
        cfgRoot["hasConfigUpdate"] = true;
    }
    else
    {
        cout << "Invalid key provided." << endl;
        return (false);
    }
	return (false);
}

bool updateConfigurationByKey1 (const std::string key, int value)
{
    if (isKeyPresent (key))
    {
        cfgRoot[key] = value;
        cfgRoot["hasConfigUpdate"] = true;
        return (true);
    }
    else
    {
        cout << "Invalid key provided." << endl;
        return (false);
    }
	return (false);
}

bool updateConfigurationByKey2 (const std::string key, const std::string value)
{
    if (isKeyPresent (key))
    {
        cfgRoot[key] = stof(value);
        cfgRoot["hasConfigUpdate"] = true;
        return (true);
    }
    else
    {
        cout << "Invalid key provided." << endl;
        return (false);
    }
	return (false);
}

int main (void)
{
  loadConfiguration ("KevinConfig.json");
  //printConfiguration();
  //cout << "updating configuration" << endl;
  //updateConfigurationByKey ("dummyVar", "1", false);
  //updateConfigurationByKey1 ("dummyVar", 1);
  //updateConfigurationByKey2 ("dummyVar", "1.0");
  //printConfiguration();
}
