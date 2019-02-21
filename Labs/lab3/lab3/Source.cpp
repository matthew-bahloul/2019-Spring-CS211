/*
	Matthew Bahloul
	2019.02.11
*/

#include <iostream>
#include <string>
#include <vector>
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
	string target_file, key_file, out_file_name, red_key("33"), green_key("255"), blue_key("0");

	// prompt the user for file names
	cout << "Enter key ppm: ";
	getline(cin, key_file);
	cout << "Enter target ppm: ";
	getline(cin, target_file);
	cout << "Enter output file: ";
	getline(cin, out_file_name);

	// use readFile to read file specified by the user
	vector<string> ppm_key_file = readFile(key_file);
	vector<string> ppm_target_file = readFile(target_file);

	// write the first three lines of the output file
	ofstream ppm_out_file(out_file_name);
	ppm_out_file << "P3" << endl;
	ppm_out_file << "300 188" << endl;
	ppm_out_file << "255" << endl;

	// start on row 4 because the first three lines are just header information
	for (unsigned int i = 3; i < ppm_key_file.size(); i++)
	{
		// split the strings into vectors
		vector<string> key_row = StringSplitter::split(ppm_key_file[i], " ");
		vector<string> target_row = StringSplitter::split(ppm_target_file[i], " ");

		for (unsigned int j = 0; j < key_row.size() - 1; j += 3)
		{
			if (key_row[j] == red_key && key_row[j + 1] == green_key && key_row[j + 2] == blue_key)
			{
				ppm_out_file << target_row[j] << " " << target_row[j + 1] << " " << target_row[j + 2] << " ";
			}
			else
			{
				ppm_out_file << key_row[j] << " " << key_row[j + 1] << " " << key_row[j + 2] << " ";
			}
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