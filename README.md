# VA_task
## Implementation of minimum and maximum values retreival and indices for a given matrix  
An example:  

[
    [3,4,6],  
    [2,8,1],  
    [4,0,4]  
]  

The min is 0 (index 7, row 3, col 2) and max is 8 (index 4, row 2, col 2)  

## Implemention of an Address Book that is based on the Trie structure
for reference https://en.wikipedia.org/wiki/Trie  
- constructs a Trie graph for a number of Persons (name, address).  
- Trie-search a node (name, address) with the expected Trie algorithmic complexity from the command line.  
- exports the output tree as an XML file named Phonebook.xml

## A multi-threading system that has:
- A Dispatcher helper class, which creates an Actor object that runs in a separate thread. 
- A base class actor has two fields, name and count. The first is a unique identifier that allows us to reques
- The base Actor object has two abstract methods, decrease and increase,
  which are expected to be overridden by sub-classes. The two methods are expected to alter the value of the count field.  
- The base Actor has two sub types (classes), DefaultCount and CountWithValue. The first has a simple implementation of increase and decrease, 
  which increases or decreases the value of count by one.   
  CountWithValue has an additional increment field, 
  which is expected to be set during the construction of a CountWithValue object,
  The increment and decrement methods will increase or decrease the count value by this increment field's value instead of the default one as opposed to DefaultCount. 
- AutoIncrease and AutoDecrease, which are sub-classes of CountWithValue, but each has an additional field, autoIncrease or autoDecrease. 
  Each of which should be passed as a part of the AutoIncrease and AutoDecrease construction. 
  The autoIncrease and autoDecrease refer to an interval value, based on which the methods of increase or decrease are called periodically. 
- From Console run a command to dispatch a new actor, which runs in its own thread. The Actor must be assigned a unique name, which is provided by the command args. 
- From console run commands to decrease, increase, or print the count of a specific actor. We assume that we reach a specific actor via its identifying name.
- An Actor has a way to get information about the count of other Actors. We can run a command that asks a specific Actor to list the count information of other Actors.  
  
