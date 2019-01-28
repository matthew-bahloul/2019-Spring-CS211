#include <iostream>
#include "csvparser.h"

using namespace std;

int main(void)
{
	cout << "Hello world" << endl;

	DefaultState state{ nullptr };
	state.handle();
	return 0;
}