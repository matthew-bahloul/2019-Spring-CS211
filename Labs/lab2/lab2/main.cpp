/*
	Matthew Bahloul
	2019.02.05
	Collaborators: Bryce Ellard, Madison Clark
*/

#include <iostream>
#include <string>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "StringSplitter.h"

using namespace std;

vector<string> readFile(ifstream& some_file);
vector<string> readFile(ifstream&& some_file);
vector<string> readFile(string file_name);


int main(void)
{
	// store the names of the in/out files
	string source_file_name;
	string out_file_name;

	// prompt the user for file names
	cout << "Enter a PPM file to parse: ";
	getline(cin, source_file_name);
	cout << "Enter a destination file: ";
	getline(cin, out_file_name);

	// tell the user that the process is starting
	cout << "parsing..." << endl;

	// use readFile to read file specified by the user
	vector<string> ppm_in_file = readFile(source_file_name);

	// write the first three lines of the output file
	ofstream ppm_out_file(out_file_name);
	ppm_out_file << "P3" << endl;
	ppm_out_file << "400 273" << endl;
	ppm_out_file << "255" << endl;

	// start on row 4 because the first three lines do not match the format of the rest of the document
	for (unsigned int i = 3; i < ppm_in_file.size(); i++)
	{
		// split the strings into vectors
		vector<string> color_row = StringSplitter::split(ppm_in_file[i], " ");

		// remove the color by changing  value to 0, 
		for (unsigned int j = 1; j < color_row.size(); j += 3)
		{
			color_row[j] = "0";
		}

		// write the values to the output file specified by the user
		for (auto val : color_row)
		{
			ppm_out_file << val << " ";
		}
		ppm_out_file << endl;
	}

	// update the user
	cout << "Processing image complete...";

	return 0;
}

vector<string> readFile(ifstream& some_file)
{
	vector<string> result{};
	//is the file open?
	if (some_file.is_open() == true)
	{
		while (some_file.good() == true)
		{
			//two ways to grab data
			string data;
			//first_names >> data; //CIN style
			getline(some_file, data); //more robust method
			result.push_back(data);
		}
	}
	return result;
}
vector<string> readFile(ifstream&& some_file)
{
	ifstream& local_file = some_file;

	//auto is an automatically inferred variable type
	//in our case, vector<string>
	auto result = readFile(local_file);
	local_file.close();
	return result;
}
vector<string> readFile(string file_name)
{
	return readFile(ifstream{ file_name });
}