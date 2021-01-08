#pragma once

#ifndef COUNT_WITH_VALUE_H
#define COUNT_WITH_VALUE_H
#include "actor.h"

class CountWithValue: public Actor{
private:
    int increment;
public:
    CountWithValue(string, int);
    void decrease();
    void increase();
};

#endif

