#include <cstring>
#include <stdio.h>
//perhaps make these point to the address of functions instead of types?
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
	//set to true whenever we set the variable
	bool set;
	//the size of bytes that the target arguments can address
	int size;
	//this is a user defined parser for custom parsing
	//the number that it returns is added to i so the user can define custom parsing
	int (*parser) (void*,void*);
};
//this is basicaly a switch statement that creates the basic number to char mapping
int char2int(char s)
{	switch (s)
	{
		case '1':
			return 1;
		case '2':
			return 2;
		case '3':
			return 3;
		case '4':
			return 4;
		case '5':
			return 5;
		case '6':
			return 6;
		case '7':
			return 7;

		case '8':
			return 8;
		default:
			//they gave us a value we didnt recognise, return 0
			//this case is also used for the valid number symbol of 0, that way the code has more mappings to 0
			return 0;
	}
}
int pow(int x,int y) 
{
	//this function takes x to the power of any real intager
	bool neg = false;
	if (y == 0) {return 1;}
	if (y < 0) {neg = true; y*=-1;}	
	int ret_val = 1;
	for (int i = 0; i < y; i++)
	{
		ret_val *= x;
	}
	if (neg) { return 1/ret_val; }
	return ret_val;
}
//this is a custom function to take a string and store it into an intager pointed to by the given pointer
int str2int(char* s,int* x,int base = 10)
{	//zero out the variable that we want to store things in just to be safe
	*x = 0;
	int i = 0;
	//realy on the 0x00 ending in c strings
	while (s[i]!='\x00')
	{
		//this adds succesfully, now we need to figure out how to get it to output the strings the way we want
		i+=1;
	}
	//the above loop finds the string leangth, what we actualy want is the last index, which is allways 1 less than the string lenth
	//so decriment the length we found by one
	i-=1;

	for (int j=i;j>=0;j--)
	{
		//go starting on the last index of the string, and add the value of char*10^location to the target x
		*x += char2int(s[j])*pow(base,i-j);
	}
	return 0;
}
bool cmpstrs(char* s1, char* s2)
{
	int i = 0;
	while (s1[i] != '\x00')
	{
		if (s1[i]!=s2[i]) {return false;}
		i+=1;
	}
	return true;
}
bool strcpy_safe(char* dest, char* src,int size)
{
	int i = 0;
	//copy from src to dest as long as their is no null byte and we did not go over the length of dest
	while (i < size)
	{
		dest[i] = src[i];
		//did we copy over a null byte to the other string, if so exit
		if (src[i] == '\x00') {break;}
		i+=1;

	}
	//this is where this function differs from strcpy, if we are given a string that is too long we make sure
	//that the target has a cutoff with a null byte!
	if (i == size) 
	{
		dest[i-1]='\x00';
		//failed to copy the whole string
		return false;
	}
	//copied the whole string
	return true;
}
int parse(int argc,char ** argv,int destc,struct arg** dest)
{
	for (int i = 1; i < argc; i++)
	{
		for (int j = 0; j < destc;j++)
		{
			if (cmpstrs(dest[j]->flag,argv[i]))
			{
				//we found a match to our flag
				switch(dest[j]->type)
				{
					case 0x00:
						//this will only fire if we wont go over the number of variables that we have
						if (!(i+1 > argc-1))
						{
							//create an intager and store it into the given memory location
							str2int(argv[i+1],(int *)dest[j]->store);
							dest[j]->set=true;
							//incriment i becuse we used the flag
							i+=1;
						}
						break;
					case 0x01:
						//this is dangerous becuse the user could give any amount of data as input
						//going to need to find a way to limit the size of data read in by the user
						//perhaps we can add somthing to our struct?
						if (!(i+1 > argc -1))
						{
							strcpy_safe((char *)dest[j]->store,argv[i+1],dest[j]->size);
							dest[j]->set=true;
							i+=1;
								
						}
						break;
					case 0x02:
						//with the boolean values we only copy true into them if they exist
						memset(dest[j]->store,true,1);
						dest[j]->set=true;
						break;
					case 0x03:
						if (!(i+1 > argc-1))
						{
							//if we have a value following our flag
							//feed that value into the user defined function
							i+=dest[j]->parser((void*)argv[i+1],dest[j]->store);
						}
						else
						{
							//its the last value on the so dont feed it i+1 feed it the given value
							i+=dest[j]->parser((void*)argv[i],dest[j]->store);
						}
						//we parsed out the value so set the set flag to true
						dest[j]->set=true;
						break;
				}	
				break;
			}
		}
	}
	return 1;
}
