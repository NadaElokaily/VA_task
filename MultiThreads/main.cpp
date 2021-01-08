#include <iostream>
#include <mutex>
#include "dispatcher.h"

using namespace std;
mutex logMutex;

int main()
{
    Dispatcher d ;
    d.stopWorkers();
    return 0;
}
