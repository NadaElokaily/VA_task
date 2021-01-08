#include "default_count.h"

DefaultCount::DefaultCount(string passedName):Actor(passedName) {
    string s  = ("Actor " + name + " is created.\n" );
    cout<<s;
}

void DefaultCount::decrease() {
    count--;
    string s  = "Decrease Default Count " + name + " new count is " + std::to_string(count) + "...\n";
    cout<<s;
}

void DefaultCount::increase() {
    count++;
    string s  = ("Increase Default Count " + name + " new count is " + std::to_string(count) + "...\n");
    cout<<s;
}
