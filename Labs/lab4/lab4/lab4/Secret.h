#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include "StringSplitter.h"
#include "Pixel.h"
#include <random>
#include <time.h>
using namespace std;

class Secret
{
private:
	vector<string> _dimensions_vector, _input_file_vector;
	string _input_file_string, _output_file_string, _magic_number, _max_brightness;
	int _width, _length;
	ofstream _output_stream;

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

public:
	// constructor for input and output files
	Secret(string i_file_name, string o_file_name)
	{
		_input_file_string = i_file_name;
		_output_file_string = o_file_name;

		_input_file_vector = readFile(_input_file_string);
		_output_stream = ofstream{_output_file_string};
	}

	// constructor when given one file name, uses a second parameter to determine if in or out file
	Secret(string file_name, int in_or_out)
	{
		if (in_or_out == 0)
		{
			_input_file_string = file_name;
			_input_file_vector = readFile(file_name);
		}
		else if (in_or_out == 1)
		{
			_input_file_string = file_name;
			_input_file_vector = readFile(file_name);

		//	_output_file_string = file_name;
			_output_stream = ofstream{ "temp.ppm" };

		}
	}

	// gets the header of the input file
	void getHeader()
	{
		_dimensions_vector = StringSplitter::split(_input_file_vector[1], " ");

		_magic_number = _input_file_vector[0];
		_width = stoi(_dimensions_vector[0]);
		_length = stoi(_dimensions_vector[1]);
		_max_brightness = _input_file_vector[2];
	}

	// writes the header of the output file if there is an output file (NOT WORKING)
	void writeHeader()
	{
		getHeader();

		_output_stream << _magic_number << endl;
		_output_stream << _width << " " << _length << endl;
		_output_stream << _max_brightness << endl;
	}

	// make a table of pixels objects from Pixel class, which contain RGB values
	vector<vector<Pixel>> makeTable() 
	{
		getHeader();
		// blank table
		vector<vector<Pixel>> pixel_table{};

		// row to be populated with pixels then cleared
		vector<Pixel> current_row{};

		// current row index
		int row_counter = 0;

		// blank pixel
		Pixel current_pixel{};
		
		pixel_table.resize(_length);

		for (unsigned int i = 3; i <= _input_file_vector.size() - 1; i++)
		{
			vector<string> _color_values_vector = StringSplitter::split(_input_file_vector[i], " ");

			for (unsigned int i = 3; i < _color_values_vector.size() - 1; i++)
			{
				// try to do i += 3 and get rid of if statement
				try
				{
					if (i % 3 == 0)
					{
						int RGB_val = stoi(_color_values_vector[i]);
						current_pixel.setRedValue(stoi(_color_values_vector[i - 3]));
						current_pixel.setGreenValue(stoi(_color_values_vector[i - 2]));
						current_pixel.setBlueValue(stoi(_color_values_vector[i - 1]));
						current_row.push_back(current_pixel);
						current_pixel = Pixel{};
					}
					if (current_row.size() == _width - 1)
					{
						pixel_table[row_counter] = current_row;
						current_row = vector<Pixel>{};
						row_counter++;
					}
				}
				catch (...)
				{ }
			}

			/*ofstream table_stream = ofstream{ "table.ppm" };
			for (auto row : pixel_table)
			{
				for (auto pix : row)
				{
					table_stream << "(" << pix.getRedValue() << ", " << pix.getGreenValue() << ", " << pix.getBlueValue() << "), -- ";
				}
				table_stream << endl;
			}*/
		}
		return pixel_table;
	}

	// method to traverse image to find secrete message
	string getMessage()
	{
		vector<vector<Pixel>> table = makeTable();
		ostringstream message{};
		Pixel current_pixel = table[0][0];

		message << (char)current_pixel.getRedValue();
		int next_row = current_pixel.getGreenValue();
		int next_col = current_pixel.getBlueValue();

		while (next_row != 0 && next_col != 0)
		{
			current_pixel.clear();
			current_pixel = table[next_row][next_col];
			next_row = current_pixel.getGreenValue();
			next_col = current_pixel.getBlueValue();

			message << (char)current_pixel.getRedValue();
		}
		return message.str();
	}

	// function to embed a message into an image
	void setMessage(string secret_message)
	{
		vector<vector<Pixel>> table = makeTable();
		getHeader();
		srand(time(NULL));

		Pixel current_pixel{};
		vector<Pixel> phrase{};

		for (auto c : secret_message)
		{
			current_pixel.setRedValue((int)c);
			current_pixel.setGreenValue(rand() % _length + 1);
			current_pixel.setBlueValue(rand() % _width + 1);

			phrase.push_back(current_pixel);
		}

		phrase[phrase.size() - 1].setRedValue((int)phrase[phrase.size()-1].getRedValue());
		phrase[phrase.size() - 1].setGreenValue(0);
		phrase[phrase.size() - 1].setBlueValue(0);

		//for (auto pix : phrase)
		//{
		//	cout << "(" << pix.getRedValue() << ", " << pix.getGreenValue() << ", " << pix.getBlueValue() << ") " << endl;
		//}

		table[0][0].setRedValue(phrase[0].getRedValue());
		table[0][0].setGreenValue(phrase[0].getGreenValue());
		table[0][0].setBlueValue(phrase[0].getBlueValue());

		for (unsigned int i = 1; i < phrase.size() - 1; i++)
		{
			table[phrase[i].getGreenValue()][phrase[i].getBlueValue()].setRedValue(phrase[i].getRedValue());
		}

		getHeader();
		ofstream table_stream = ofstream{ "output.ppm" };
		table_stream << _magic_number << endl;
		table_stream << _width << " " << _length << endl;
		table_stream << _max_brightness << endl;

		for (auto row : table)
		{
			for (auto pix : row)
			{
				table_stream << pix.getRedValue() << " " << pix.getGreenValue() << " " << pix.getBlueValue() << " ";
			}
			table_stream << endl;
		}

		//_input_file_string = "output.ppm";
	}
};
