MultiThreads

## classes Dispatcher, Actor, DefaultCount, CountWithValue, AutoIncrement, AutoDecrement are created successfully
## using the terminal you can press
 ### a to add new actor with a unique name only
 ### i to increase the count of an existing actor
 ### d to decrease the count of an existing actor
 ### c to the count of an existing actor
 ### p to get into a specific actor thread and peak another actor

Files
 actor.h,
 default_count.h/.cpp,
 count_with_value.h/.cpp,
 auto_increase/decrease.h/.cpp
contain all declarations and definition related code for the different actors 

main.cpp initializes the dispacher class & calls the dispacher class threads joining

dispacher.cpp

 the dispacher has a vector of threads & actors and a map that maps each name to its actor pointer
 each actor is assigned to a thread

 controlling the shared resources using a condition_variable and a lock

 function getData is the main thread that creates other threads based on user choice retrieved from the terminal & passes the user's main choices

 countDefaultOrValue is the thread function used for DefaultCount and CountWithValue threads

 increaseOrDecreaseAction is the thread used function for AutoIncrease and AutoDecrease threads
 
 stopWorkers to join all threads

 then the destructor is called to free all the used up memory to avoid memory leaks

#Warning: please enter the required input as requested either the input choice characters
#or the integer values