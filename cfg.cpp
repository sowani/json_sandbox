#include "cfg.h"
using namespace std;

#define DEFAULT_UPSTREAM_CONFIG_FILE "UpstreamConfig.json"
#define SAVED_UPSTREAM_CONFIG_FILE   "UpstreamConfig1.json"

Configuration::Configuration(): version(""), configKeyValueMap{} {
}

Configuration::~Configuration() {
}

const std::string& Configuration::getVersion() const {
	return version;
}

void Configuration::setVersion(const std::string& version) {
	this->version = version;
}

const std::map<std::string, std::string>& Configuration::getConfigKeyValueMap() const {
	return configKeyValueMap;
}

void Configuration::setConfigKeyValueMap(const std::map<std::string, std::string>& configKeyValueMap) {
	this->configKeyValueMap = configKeyValueMap;
}

UpstreamConfiguration::UpstreamConfiguration() :
    configFile (DEFAULT_UPSTREAM_CONFIG_FILE)
{
  loadConfiguration();
}

UpstreamConfiguration::UpstreamConfiguration (std::string cfgFile) :
    configFile (cfgFile)
{
  loadConfiguration();
}

UpstreamConfiguration::~UpstreamConfiguration() {
  cout << "saving upstream configuration ..." << endl;
  saveConfiguration (SAVED_UPSTREAM_CONFIG_FILE);
}

void UpstreamConfiguration::loadConfiguration()
{
    ifstream cfgFile;
    cout << "initializing configuration from " << configFile << endl;
    cfgFile.open (configFile);
    if (!cfgFile)
    {
      cout << "invalid config file, using default config file." << endl;
      configFile = DEFAULT_UPSTREAM_CONFIG_FILE;
      cfgFile.open (configFile);
    }
 
    cfgFile >> cfgRoot;
    cfgRoot["hasConfigChanged"] = false;
    cfgFile.close();
}

void UpstreamConfiguration::saveConfiguration (std::string filename)
{
    if (! hasUpstreamConfigurationChanged())
    {
        ofstream file1 (filename);
        file1 << setw(2) << cfgRoot;
        file1.close();
    }
    else
        cout << "Discarded un-applied Upstream configuration changes.\n";
}

std::vector<std::string> UpstreamConfiguration::getLogTargets (void) const
{
    std::vector<std::string> targets = cfgRoot["logTargets"];
    return (targets);
}

std::string UpstreamConfiguration::getConfigurationKeyValue (const std::string key)
{
    if (cfgRoot.find (key) == cfgRoot.end())
    {
        cout << "Invalid configuration parameter specified." << endl;
        return ("INVALID_KEY");
    }
    return (cfgRoot[key]);
}

int UpstreamConfiguration::setConfigurationKeyValue (const std::string key, const std::string value)
{
    if (cfgRoot.find (key) == cfgRoot.end())
    {
        cout << "Invalid configuration parameter specified." << endl;
        return (1);
    }
    cfgRoot[key] = value;
    cfgRoot["hasConfigChanged"] = true;
    return (0);
}

bool UpstreamConfiguration::applyUpstreamConfiguration()
{
  // apply configuration changes to Upstream processor
  cfgRoot["hasConfigChanged"] = false;
}

bool UpstreamConfiguration::hasUpstreamConfigurationChanged()
{
    return (cfgRoot["hasConfigChanged"]);
}

void UpstreamConfiguration::printUpstreamConfiguration (std::map<std::string, std::string>& configKeyValueMap)
{
    cout << setw(2) << cfgRoot << endl;
}

int main (void)
{
  std::map<std::string, std::string> cfg;
  UpstreamConfiguration upconfig;
  cout << "changed: " << upconfig.hasUpstreamConfigurationChanged() << endl;
  //UpstreamConfiguration upconfig("altConfig.json");
  //upconfig.setVersion("1.0");
  upconfig.setConfigurationKeyValue ("tt", "2");
  cout << "changed: " << upconfig.hasUpstreamConfigurationChanged() << endl;
  cfg = upconfig.getConfigKeyValueMap();
  cout << "config ver = " << upconfig.getVersion() << endl;
  upconfig.printUpstreamConfiguration(cfg);
  cout << "changed: " << upconfig.hasUpstreamConfigurationChanged() << endl;
  upconfig.applyUpstreamConfiguration();
  cout << "changed: " << upconfig.hasUpstreamConfigurationChanged() << endl;
  return (0);
}
