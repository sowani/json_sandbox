#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
#include "nlohmann/json.hpp"

using json = nlohmann::json;

class Configuration {
	std::string version;
	std::map<std::string, std::string> configKeyValueMap;
protected:
	std::string getConfigParameter(std::string key);
public:
	Configuration();
	virtual ~Configuration();
	const std::string& getVersion() const;
	void setVersion(const std::string& version);
	const std::map<std::string, std::string>& getConfigKeyValueMap() const;
	void setConfigKeyValueMap(const std::map<std::string, std::string>& configKeyValueMap);
};

class UpstreamConfiguration: public Configuration {
    std::string configFile;
	json cfgRoot;
    bool hasConfigChanged;
public:
	UpstreamConfiguration();
    UpstreamConfiguration (std::string cfgFile);
	std::vector<std::string> getLogTargets(void) const;

	UpstreamConfiguration& getInstance(void) const {
		static UpstreamConfiguration theInstance;
		return theInstance;
	}

    void loadConfiguration();
    void saveConfiguration (std::string filename);
	std::string getConfigurationKeyValue (const std::string key);
	int setConfigurationKeyValue (const std::string key, const std::string value);
    bool applyUpstreamConfiguration();
    bool hasUpstreamConfigurationChanged();

    // debugging
    void printUpstreamConfiguration (std::map<std::string, std::string>& configKeyValueMap);

	virtual ~UpstreamConfiguration();
};

#endif /* CONFIGURATION_H_ */
