#include "auto_decrease.h"

AutoDecrease::AutoDecrease(string passedName, int incrementValue, int interval)
:CountWithValue(passedName, incrementValue),
autoDecrease(interval) {
    string s  = ("Actor " + name + " is created.\n" );
    cout<<s;
}

int AutoDecrease::getInterval() {
    return autoDecrease;
}
