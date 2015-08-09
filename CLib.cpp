// Implementation of example C-like library
// Declare structure and functions:

#include "Clib.h"
#include <iostream>
#include <cassert>

using namespace std;

// Quatity of elements to add when increasing storage:
const int increment = 100;

void initialize(CStash* s, int size)
{
	s->size = size;
	s->quantity = 0;
	s->next = 0;
	s->storage = 0;
}

void* fetch(CStash* s, int index)
{
	// Check index boundaries:
	assert(0 <= index);
	if(index >= s->next)
		return 0;
	// Produce pointer to desired elment
	return &(s->storage[index * s->size]);			
}

int count(CStash *s)
{
	return s->next; 
}

void inflate(CStash* s, int increase)
{
	assert(increase > 0);
	int newQuantity = s->quantity + increase;
	int newBytes = newQuantity * s->size;
	int oldBytes = s->quantity * s->size;

	unsigned char* b = new unsigned char[newBytes];			//开辟更长的内存空间

	for (int i = 0; i < oldBytes; i++)
	{
		b[i] = s->storage[i];
	}

	delete []s->storage;
	s->storage = b;
	s->quantity = newQuantity;
}

int add(CStash* s, const void* element)
{
	if (s->next >= s->quantity)
	{
		inflate(s, increment);
	}
	// Copy element into storage
	// starting at next empty space
	int startBytes = s->next * s->size;
	unsigned char* e = (unsigned char*)element;
	for (int i = 0; i < s->size; i++)
	{
		s->storage[startBytes + i] = e[i];
	}
	s->next++;
	return(s->next - 1);		// Index number
}

void cleanUp(CStash* s)
{
	if(s->storage != 0)
	{
		cout << "free storage" << endl;
		delete []s->storage;
	}
}