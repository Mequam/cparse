# cparse
a c++ library for parsing CLI arguments

this library provides a parsing function that takes the arguments int argc,char argv**,int destc,struct arg** destv
where argc and argv** are the arguments that the os passes to the main function and destc and destv are the number of
different arguments that you want to parse out and a pointer to pointers of argument types

the basic idea is that you can represent command line flags as structs and pass them to the parseing function without worrying about
the specifics of how they get parsed out.


the definition for the argument structures is as follows, stripped almost word for word from the structs definition file

struct arg 

{	
  
  //the flag to the left of the argument that we want to parse out, required
  
  char * flag;

//the memory address where we store the parsed argument when we find it, required

void * store;

//the type that we want to convert the found data into, can be INT,BOOL,STR or CUSTOM these values are defined in parse.h

char type;	

//this is set by the parsing function to tell you wether or not it parsed a value into the given variable

//set will be true if we did

bool set=false;

//the size of bytes that the target arguments can address, this is only used when parsing out STRING, otherwise the default

//data sizes are assumed

int size;

//this is a user defined parser for custom parsing

//the value it returns is how many arguments we want to skip ahead after

//parsing out a value

//the two arguments are the a pointer to the given argument and the destination that you want to store it in

int (*parser) (void*,void*); 

};

