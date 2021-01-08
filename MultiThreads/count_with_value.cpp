#include "count_with_value.h"

CountWithValue::CountWithValue(string passedName, int incrementValue) : Actor(passedName), increment(incrementValue) {
    string s  = ("Actor " + name + " is created.\n" );
    cout<<s;
}

void CountWithValue::decrease() {
    count -= increment;
    string s  = "Decrease Count " + name +" with value "+to_string(increment)+ " new count is " + std::to_string(count) + "...\n";
    cout<<s;
}

void CountWithValue::increase() {
    count += increment;
    string s  = ("Increase Count " + name +" with value "+to_string(increment)+ " new count is " + std::to_string(count) + "...\n");
    cout<<s;
}
