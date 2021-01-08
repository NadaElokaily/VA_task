#include "dispatcher.h"

#include <iostream>
#include <stdio.h>
using namespace std;

Dispatcher::Dispatcher() {
    dataReady = false;
    getDataThread = thread(&Dispatcher::getData, this);
    name = "";
    action = '_';
}

void Dispatcher::getData() {
    int wait = 5;
    cout<<"Starting get data thread\n";
    char type, continueFlag='c';
    int inc,interval;
    while(continueFlag == 'c') {
        {
            lock_guard<mutex> lck(writingMutex);
            dataReady = true;
            type = '_';
            inc = 0;
            interval = 1;
            action = '_';
            //prevent other threads from interfering in the user interaction process
            dispacherReadingMutex.lock();
            while((action!='a')&&(action!='i')&&(action!='d')&&(action!='c')&&(action!='p')){
                cout<<"(a/i/d/c) for add/increase/decrease/count of actors\nOr p to peek other actors\n";
                cin>>action;
            }
            dispacherReadingMutex.unlock();
            if (action == 'a') {

                dispacherReadingMutex.lock();
                cout<<"Enter actor's name\n";
                cin>>name;
                dispacherReadingMutex.unlock();
                if (nameAndActor.find(name) == nameAndActor.end()){
                    dispacherReadingMutex.lock();
                    while((type!='d')&&(type!='v')&&(type!='i')&&(type!='m')){
                        cout<<"(d/v/i/m) for default/count_with_value/auto_increment/auto_decrement\n";
                        cin>>type;
                    }

                    if((type=='i')||(type=='m')||(type=='v')) {
                        cout<<"Enter integer increment value\n";
                        cin>>inc;
                    }
                    if((type=='i')||(type=='m')) {
                        cout<<"Enter integer interval value\n";
                        cin>>interval;
                    }
                    dispacherReadingMutex.unlock();
                    thread* x;
                    if ((type == 'd')||(type == 'v')){
                        x = new thread(&Dispatcher::countDefaultOrValue, this, name, type, inc);
                    }
                    else if ((type == 'i')||(type == 'm')) {
                        x = new thread(&Dispatcher::increaseOrDecreaseAuto, this, name, type, inc, interval);
                    }
                    threads.push_back(x);
                }
                else {
                    cout<<"actor already exists\n";
                    wait = 0;
                }
            }

            else if((action == 'i')||(action=='d')||(action=='c')||(action=='p')){
                dispacherReadingMutex.lock();
                cout<<"Enter actor's name\n";
                cin>>name;
                if (nameAndActor.find(name) == nameAndActor.end()) {
                    cout<<"Actor doesn't exist\n";
                    wait = 0;
                }
                dispacherReadingMutex.unlock();
            }
        }
        condVar.notify_all();
        this_thread::sleep_for(chrono::seconds(wait));
        dispacherReadingMutex.lock();
        cout<<"c to continue manipulating actors\n";
        cin>>continueFlag;
        dispacherReadingMutex.unlock();
        wait = 5;
    }
    condVar.notify_all();
    //join threads if the user doesn't want to add anymore actors
}

void Dispatcher::countDefaultOrValue(string actorName, char type, int increment) {
    Actor* actor;
    if(type == 'd')
        actor = new DefaultCount(actorName);
    else if(type == 'v')
        actor = new CountWithValue(actorName, increment);
    else
        return;
    actors.push_back(actor);
    cout<<"Thread "+actorName+" was created successfully\n";
    nameAndActor[actorName] = actor;
    while(true){
        unique_lock<mutex> lck(writingMutex);
        condVar.wait(lck, [&](){ return this->dataReady;});
        dispacherReadingMutex.lock();
        if(name == actorName){
            if((action == 'i')||(action == 'd')||(action == 'c')||(action == 'p')) {
                cout<<"Thread "+name+" welcomes you\n";
                if (action == 'i')
                    actor->increase();
                else if (action == 'd')
                    actor->decrease();
                else if (action == 'c')
                    cout<<"count of "+name+" is "<<actor->getCount()<<endl;
                else if (action == 'p'){
                    string anotherActorName;
                    char peakChoice = '_';
                    cout<<"Enter the name of the actor you want "+name+" to peak\n";
                    cin>>anotherActorName;
                    if(nameAndActor.find(anotherActorName) != nameAndActor.end()) {
                        while ((peakChoice!='i')&&(peakChoice!='d')&&(peakChoice!='c')){
                            cout<<"i/d/c for increase or decrease or count of actor "+anotherActorName+"\n";
                            cin>>peakChoice;
                        }
                        if(peakChoice == 'i'){
                            nameAndActor[anotherActorName]->increase();
                        }
                        else if(peakChoice =='d'){
                            nameAndActor[anotherActorName]->decrease();
                        }
                        else if(peakChoice =='c'){
                            cout<<nameAndActor[anotherActorName]->getCount()<<endl;
                        }
                    }
                    else {
                        cout<<"actor doesn't exist";
                    }

                }
                action = '_';
                name="_______";
            }
        }
        /*else if (name != "_______") {
            cout<<"This is "+actorName+" not the requested "+name+"\n";
        }*/
        dispacherReadingMutex.unlock();
        this_thread::sleep_for(chrono::seconds(1));

    }
}

void Dispatcher::increaseOrDecreaseAuto(string actorName,char type, int increment, int interval) {
    Actor* actor;
    if(type == 'i'){
        actor = new AutoIncrease(actorName, increment, interval);
    }
    else if(type == 'm'){
        actor = new AutoDecrease(actorName, increment, interval);
    }
    else
        return;
    actors.push_back(actor);
    nameAndActor[actorName] = actor;
    cout<<"Thread "+actorName+" was created successfully and is waiting for further orders\n";
    while(true){
        unique_lock<mutex> lck(writingMutex);
        condVar.wait(lck, [&](){ return this->dataReady;});
        dispacherReadingMutex.lock();
        if(name == actorName){
            if((action == 'i')||(action == 'd')||(action == 'c')||(action == 'p')) {
                cout<<"actor "+name+" welcomes you\n";
                if (action == 'i')
                    actor->increase();
                else if (action == 'd')
                    actor->decrease();
                else if (action == 'c')
                    cout<<"count of "+name+" is "<<actor->getCount()<<endl;
                else if (action == 'p'){
                    string anotherActorName;
                    char peakChoice = '_';
                    cout<<"Enter the name of the actor you want "+name+" to peak\n";
                    cin>>anotherActorName;
                    if(nameAndActor.find(anotherActorName) != nameAndActor.end()) {
                        while ((peakChoice!='i')&&(peakChoice!='d')&&(peakChoice!='c')){
                            cout<<"i/d/c for increase or decrease or count of actor "+anotherActorName+"\n";
                            cin>>peakChoice;
                        }
                        if(peakChoice == 'i'){
                            nameAndActor[anotherActorName]->increase();
                        }
                        else if(peakChoice =='d'){
                            nameAndActor[anotherActorName]->decrease();
                        }
                        else if(peakChoice =='c'){
                            cout<<nameAndActor[anotherActorName]->getCount()<<endl;
                        }
                    }
                    else {
                        cout<<"actor doesn't exist";
                    }

                }

                action = '_';
                name="_______";
            }
        }
        if(type == 'i')
            actor->increase();
        else if(type == 'm')
            actor->decrease();
        dispacherReadingMutex.unlock();
        //this_thread::sleep_for(chrono::seconds(actor->getInterval()));
        this_thread::sleep_for(chrono::seconds(interval));
    }
}

void Dispatcher::stopWorkers() {
    getDataThread.join();
    for(int i =0; i<threads.size(); i++) {
        threads[i]->join();
    }
}

Dispatcher::~Dispatcher() {
    for(int i =0; i<actors.size(); i++) {
        delete actors[i];
    }
    for(int i =0; i<threads.size(); i++) {
        delete threads[i];
    }
}
