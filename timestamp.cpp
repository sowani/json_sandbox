#include <ctime>
#include <iostream>

void getTimeStamp (char *ts)
{
    // YYYY-MM-DD HH:MM:SS.mmm
    const char *format = "%F %T";
    std::time_t result = std::time(nullptr);
    std::strftime(ts, 24*sizeof(char), format, std::localtime(&result));
}
 
int main()
{
    char mbstr[24];
    getTimeStamp(&mbstr[0]);
    std::cout << mbstr << std::endl;
    return (0);
}

/* requires c++17
#include <cstdio>
int main()
{
    std::timespec ts;
    std::timespec_get(&ts, TIME_UTC);
    char buf[100];
    std::strftime(buf, sizeof buf, "%F %T", std::gmtime(&ts.tv_sec));
    std::cout << buf << std::endl;
    //std::printf("Current time: %s.%09ld UTC\n", buf, ts.tv_nsec);
}
*/
