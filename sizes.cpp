#include <iostream>
using namespace std;

int main(void)
{
  cout << "char    : " << sizeof (char) << " bytes" << endl;
  cout << "bool    : " << sizeof (bool) << " bytes" << endl;
  cout << "short   : " << sizeof (short) << " bytes" << endl;
  cout << "float   : " << sizeof (float) << " bytes" << endl;
  cout << endl;

  cout << "int8_t  : " << sizeof (int8_t) << " bytes" << endl;
  cout << "int16_t : " << sizeof (int16_t) << " bytes" << endl;
  cout << "int32_t : " << sizeof (int32_t) << " bytes" << endl;
  cout << "int64_t : " << sizeof (int64_t) << " bytes" << endl;
  cout << endl;

  cout << "long    : " << sizeof (long) << " bytes" << endl;
  cout << "longlong: " << sizeof (long long) << " bytes" << endl;

  cout << "char*   : " << sizeof (char*) << " bytes" << endl;
  cout << "short*  : " << sizeof (short*) << " bytes" << endl;
  cout << "float*  : " << sizeof (float*) << " bytes" << endl;
  cout << "int*    : " << sizeof (int*) << " bytes" << endl;
  cout << "int8_t* : " << sizeof (int8_t*) << " bytes" << endl;
  cout << "int16_t*: " << sizeof (int16_t*) << " bytes" << endl;
  cout << "int32_t*: " << sizeof (int32_t*) << " bytes" << endl;
  cout << "int64_t*: " << sizeof (int64_t*) << " bytes" << endl;
  cout << "long*   : " << sizeof (long*) << " bytes" << endl;
  return (0);
}
