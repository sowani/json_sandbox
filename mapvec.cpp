#include <map>
#include <vector>
#include <iostream>
using namespace std;

map<string, string> topicMap;

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
    vector<string> chars;
    chars = myTable.getChars (40004);
    for (vector<string>::iterator it = chars.begin(); it != chars.end(); ++it)
    {
      //string topic = '"' + (*it) + '"';
      string topic = *it;
      //cout << *it << endl;
      cout << topic << endl;
      topicMap[topic] = "test value for " + *it;
    }
    cout << topicMap["char5"] << endl;
    cout << topicMap["char6"] << endl;
    cout << topicMap["char7"] << endl;
    return (0);
}
