
#pragma once
#ifndef DISPATCHER_H
#define DISPATCHER_H

#include <map>
#include <vector>
#include <thread>
#include <condition_variable>
#include "default_count.h"
#include "count_with_value.h"
#include "auto_decrease.h"
#include "auto_increase.h"


using namespace std;
extern mutex logMutex;

class Dispatcher {
public:
    mutex writingMutex;
    mutex dispacherReadingMutex;
    condition_variable condVar;
    bool dataReady;
    string name;
    char action;
    thread getDataThread;
    map<string, Actor*> nameAndActor;
    vector<Actor*> actors;
    vector<thread*> threads;

    Dispatcher();
    ~Dispatcher();
    void getData();
    void countDefaultOrValue(string actorName, char type, int increment);
    void increaseOrDecreaseAuto(string actorName,char type, int increment, int interval);
    void stopWorkers();
};

#endif
