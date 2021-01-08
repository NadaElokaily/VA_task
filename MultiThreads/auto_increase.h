#pragma once

#ifndef AUTO_INCREASE_H
#define AUTO_INCREASE_H
#include "count_with_value.h"

class AutoIncrease: public CountWithValue{
private:
    int autoIncrease;
public:
    AutoIncrease(string, int, int);
    int getInterval();
};

#endif

