#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

class Ppm
{
private:
	ifstream _ppm_stream;
	ofstream _ppm_processed;

	string _row;
	vector<string> _table;

public:
	Ppm(string file_name)
	{
		ifstream _ppm_stream{ file_name };
	}

	void processFile()
	{
		while (_ppm_stream.good())
		{
			getline(_ppm_stream, _row);
			_table.push_back(_row);
		}
	}

};