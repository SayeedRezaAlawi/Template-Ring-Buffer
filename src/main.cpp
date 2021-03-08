//============================================================================
// Name        : main.cpp
// Author      : Sayeed Reza Alawi
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "CTRingBuffer.h"
using namespace std;

int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	CTRingBuffer<float> myBuffer(10);
	//Filling the buffer
	try
	{
	for (unsigned int i = 0; i < 5; i++ )
	{
	myBuffer+=(i);
	}
	}
	catch (error_t &errCode)
	{
	switch (errCode)
	{
	case BUFFERFULL : cout << "Opps, buffer is full" << endl; break;
	case BUFFEREMPTY : cout << "Opps, buffer is empty" << endl; break;
	}
	}

	CTRingBuffer<float>::iterator first = myBuffer.first();
	cout << "first: " << first << endl;
	CTRingBuffer<float>::iterator last = myBuffer.last();
	cout << "last: " << last << endl;
	//Reading the buffer
	try
	{
	for (CTRingBuffer<float>::iterator i = first; i != last; ++i)
	{
	cout << "Read element at position: " << i << " ";
	cout << " having the content : " << *myBuffer << endl;
	}
	}
	catch (error_t &errCode)
	{
	switch (errCode)
	{
	case BUFFERFULL : cerr << "Opps, buffer is full" << endl; break;
	case BUFFEREMPTY : cerr << "Opps, buffer is empty" << endl; break;
	}
	}

	return 0;
}
