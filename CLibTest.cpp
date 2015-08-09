#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include "Clib.h"

using namespace std;

int main()
{
	CStash intStash, stringStash;
	int i ;
	char* cp;
	ifstream in;
	string line;
	const int bufSize = 80;

	//Now remember to initialize the variables
	initialize(&intStash, sizeof(int));
	for (int i = 0; i < 100; i++)
	{
		add(&intStash, &i);
	}
	for (int i = 0; i < count(&intStash); i++)
	{
		cout << "fetch(&intStash, " << i << ") = " << *(int*)fetch(&intStash, i) << endl;
	}

	//
	initialize(&stringStash, sizeof(char)* bufSize);
	in.open("CLibTest.cpp");
	assert(in);
	while (getline(in, line))
	{
		add(&stringStash, line.c_str());
	}

	i = 0;
	while ((cp = (char*)fetch(&stringStash, i++)) != 0)
	{
		//cout << "fetch(&stringStash, " << i << ") = \t" << cp << endl;
		cout << cp << endl;
	}

	cleanUp(&intStash);
	cleanUp(&stringStash);

	system("pause");
	return 0;
}

