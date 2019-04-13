#define INT '\x00' 
#define STRING '\x01'
#define BOOL '\x02'
#define CUSTOM '\x03'
struct arg 
{	//the flag were looking for
	char * flag;
	//the memory address where to store the argument
	void * store;
	//the type that we want to convert the found data into
	char type;	
	//wether or not the argument is required
	bool set=false;
	//the size of bytes that the target arguments can address
	int size;
	//this is a user defined parser for custom parsing
	//the value it returns is how many arguments we want to skip ahead after
	//parsing out a value
	int (*parser) (void*,void*); 
};
int parse(int argc,char ** argv,int destc,struct arg** dest);

