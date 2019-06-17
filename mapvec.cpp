#include <map>
#include <vector>
#include <iostream>
#include <string>
using namespace std;

map<string, string> topicMap;

enum DATA_ELEMENT_TYPE {
	DATA_ELEMENT_TYPE_UINT8 = 0,
	DATA_ELEMENT_TYPE_UINT16,
	DATA_ELEMENT_TYPE_UINT32,
	DATA_ELEMENT_TYPE_UINT64,
	DATA_ELEMENT_TYPE_FLOAT,
	DATA_ELEMENT_TYPE_BOOL,
	DATA_ELEMENT_TYPE_STRING,
	DATA_ELEMENT_TYPE_UNDEFINED
};

enum CHARACTERISTIC_PRIORITY {
	PRIORITY_LOW = 0,
	PRIORITY_MEDIUM,
	PRIORITY_HIGH,
	PRIORITY_CRITICAL
};

class Characteristic {

protected:

	bool isUpdated;
	DATA_ELEMENT_TYPE type;
	CHARACTERISTIC_PRIORITY priority;
	time_t timeStamp;
	std::string name;

public:

	Characteristic() {
		this->isUpdated = false;
		this->type = DATA_ELEMENT_TYPE_UNDEFINED;
		this->priority = PRIORITY_MEDIUM;
		this->timeStamp = 0;
		this->name = "";
	}

	Characteristic(const char* name) {
		this->isUpdated = false;
		this->type = DATA_ELEMENT_TYPE_UNDEFINED;
		this->priority = PRIORITY_MEDIUM;
		this->timeStamp = 0;
		this->name = name;
	}

	// Set and reset updated state
	void markAsUpdated() {
		isUpdated = true;
		timeStamp = time(NULL); // Epoch time
	}

	void markAsNotUpdated() {
		isUpdated = false;
		timeStamp = 0;
	}

	// Setter and Getter APIs
	void setDataElementType(DATA_ELEMENT_TYPE type) {
		this->type = type;
	}

	DATA_ELEMENT_TYPE getDataElementType() {
		return this->type;
	}

	bool getIsUpdated() const{
		return isUpdated;
	}

	void setIsUpdated(bool isUpdated){
		this->isUpdated = isUpdated;
	}

	CHARACTERISTIC_PRIORITY getPriority() const{
		return priority;
	}

	void setPriority(CHARACTERISTIC_PRIORITY priority){
		this->priority = priority;
	}

	time_t getTimeStamp() const{
		return timeStamp;
	}

	void setTimeStamp(time_t timeStamp){
		this->timeStamp = timeStamp;
	}

	std::string getName() const {
		return name;
	}

	void setName(std::string name) {
		this->name = name;
	}

	void setName(const char* name) {
		this->name = name;
	}

	const char* getName() {
		return this->name.c_str();
	}

	std::string getStringName() {
		return this->name;
	}

	//void markAsUpdated() {
		//isUpdated = true;
		//timeStamp = time(NULL); // Epoch time
	//}

	//void markAsNotUpdated() {
		//isUpdated = false;
		//timeStamp = 0;
	//}
};

class CharacteristicUint16 : public Characteristic {
	uint16_t value;
public:
	CharacteristicUint16() {
		this->value =0;
	}

	CharacteristicUint16(const char* name) : Characteristic(name) {
		this->value =0;
	}

	uint16_t getValue() {
		markAsNotUpdated();
		return value;
	}

	void setValue(uint16_t value) {
		this->value = value;
		markAsUpdated();
	}
};

class pmac_table
{
private:
  const map<uint16_t, vector<string>> pmacTable = 
  {
    { 40001, { "char1" } },
    { 40002, { "char2" } },
    { 40003, { "char3", "char4" } },
    { 40004, { "char5", "char6", "char7" } }
  };

public:
    pmac_table() { };
    ~pmac_table() { };
    vector<string> getChars (uint16_t regAddr) const;
};

vector<string> pmac_table::getChars (uint16_t regAddr) const
{
    vector<string> chars;
    map<uint16_t, vector<string>>::const_iterator itr = pmacTable.find (regAddr);
    if (itr != pmacTable.end())
        chars = itr->second;
    return (chars);
}

int main (void)
{
    pmac_table myTable;
    CharacteristicUint16 char5 { "char5" };
    CharacteristicUint16 char6 { "char6" };
    CharacteristicUint16 char7 { "char7" };

    vector<string> chars;
    chars = myTable.getChars (40004);
    for (vector<string>::iterator it = chars.begin(); it != chars.end(); ++it)
    {
      string topic = *it;
	  cout << topic << endl;
      if (topic.compare("char5") == 0)
      {
        char5.setValue (55);
        topicMap[topic] = to_string(char5.getValue());
      }
      else if (topic.compare("char6") == 0)
      {
        char6.setValue (66);
        topicMap[topic] = to_string(char6.getValue());
      }
      else if (topic.compare("char7") == 0)
      {
        char7.setValue (77);
        topicMap[topic] = to_string(char7.getValue());
      }
    }
    cout << topicMap["char5"] << endl;
    cout << topicMap["char6"] << endl;
    cout << topicMap["char7"] << endl;
    return (0);
}
