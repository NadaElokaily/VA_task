#pragma once
#ifndef ACTOR_H
#define ACTOR_H
#include <iostream>
using namespace std;

class Actor{
protected:
    string name;
    int count;

public:
    Actor(string passedName) {name = passedName; count = 0;};
    int getCount(){return count;}
    virtual void decrease() = 0;
    virtual void increase() = 0;
    string getName(){return name;};
};

#endif
