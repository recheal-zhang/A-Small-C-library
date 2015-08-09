// Header file for a C-like library
// An array-like entity created at runtime 
typedef struct CStashTag
{
	int size;		// Size of each space
	int quantity;	// Nmber of storage spaces
	int next;		// Next empty space
	
	unsigned char* storage;		//Dynamically allocated array of bytes
}CStash;

void initialize(CStash* s, int size);

void cleanUp(CStash* s);

int add(CStash* s, const void* element);

void* fetch(CStash* s, int index);

int count(CStash* s);

void inflate(CStash* s, int increase);