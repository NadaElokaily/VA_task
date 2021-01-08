#pragma once

#ifndef AUTO_DECREASE_H
#define AUTO_DECREASE_H
#include "count_with_value.h"

class AutoDecrease: public CountWithValue{
private:
    int autoDecrease;
public:
    AutoDecrease(string, int, int);
    int getInterval();
};

#endif
