#pragma once

#ifndef DEFAULT_COUNT_H
#define DEFAULT_COUNT_H
#include "actor.h"

class DefaultCount: public Actor{
public:
    DefaultCount(string);
    void decrease();
    void increase();
};

#endif
