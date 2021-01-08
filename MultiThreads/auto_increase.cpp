#include "auto_increase.h"

AutoIncrease::AutoIncrease(string passedName, int incrementValue, int interval)
:CountWithValue(passedName, incrementValue),
autoIncrease(interval) {
    string s  = ("Actor " + name + " is created.\n" );
    cout<<s;
}

int AutoIncrease::getInterval() {
    return autoIncrease;
}

