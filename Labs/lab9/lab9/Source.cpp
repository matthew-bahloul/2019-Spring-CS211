#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#include "StringSplitter.h"

using namespace std;

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

bool operator<(pair<string, int> pair_a, pair<string, int> pair_b)
{
	return pair_a.second < pair_b.second;
}
bool operator>(pair<string, int> pair_a, pair<string, int> pair_b)
{
	return pair_a.second > pair_b.second;
}

void concordance(string file_name)
{
	vector<string> lines = readFile(file_name);
	vector<string> words{};
	for (auto line : lines)
	{
		vector<string> all_words = StringSplitter::split(line, " ");
		for (auto word : all_words)
		{
			words.push_back(word);
		}
	}

	unordered_map<string, int> word_frequencies{};

	for (auto word : words)
	{
		word_frequencies[word]++;
	}

	for (auto group : word_frequencies)
	{
		cout << group.first << ": " << group.second << endl;
	}

}

bool hasUniqueChars(string text)
{
	unordered_map<char, int> char_frequencies{};

	for (char ch : text)
	{
		char_frequencies[ch]++;
	}
	
	if (text == "")
	{
		return true;
	}

	for (auto pair : char_frequencies)
	{
		if (pair.second > 1)
		{
			return false;
		}
	}

	return true;
}

bool isAnagram(string first, string second)
{
	unordered_map<char, int> first_string_char_frequencies{};
	unordered_map<char, int> second_string_char_frequencies{};

	for (char ch : first) // frequency chart for first string
	{
		if (ch != ' ')
		{
			first_string_char_frequencies[ch]++;
		}
	}

	for (char ch : second) // frequency chart for second string
	{
		if (ch != ' ')
		{
			second_string_char_frequencies[ch]++;
		}
	}
	
	if (first_string_char_frequencies.size() != second_string_char_frequencies.size())
	{
		return false;
	}

	else
	{
		for (auto pair : first_string_char_frequencies)
		{
			if (pair.second == second_string_char_frequencies[pair.first])
			{
				continue;
			}
			else
			{
				return false;
			}
		}
		return true;
	}

}

string mostCommonSubstring(string text, int size)
{
	vector<string> substrings{};
	unordered_map<string, int> substring_frequencies{};

	int start = 0;
	int end = size - 1;

	if (size > text.size())
	{
		return NULL;
	}

	for (int i = 0; i < text.size() - (size - 1); i ++)
	{
		try
		{
			string temp_sub = text.substr(i, size);
			substrings.push_back(temp_sub);
			substring_frequencies[temp_sub]++;
		}
		catch (...)
		{}
	}

	pair<string, int> max(substrings[0], -1);

	for (auto group : substring_frequencies)
	{
		if (group > max)
		{
			max = group;
		}
	}

	return max.first;
}




int main(void)
{

	cout << boolalpha;

	//TODO: open test_file, create concordance
// concordance test
	cout << "***concordance test***" << endl;
	
	concordance("happy.txt");

	cout << endl;

//unique chars test
	cout << "***unique characters test***" << endl;

	//test case #1
	cout << "abcde: " <<
		hasUniqueChars("abcde")
		<< " (expected: true)"
		<< endl;

	//test case #2:
	cout << "aaaa: " <<
		hasUniqueChars("aaaa")
		<< " (expected: false)"
		<< endl;

	//test case #3:
	cout << "(empty string): " <<
		hasUniqueChars("")
		<< " (expected: true)"
		<< endl;

	//test case #4:
	cout << "abcdea: " <<
		hasUniqueChars("abcdea")
		<< " (expected: false)"
		<< endl;

//anagram tests
	cout << endl << endl;
	cout << "***anagram tests***" << endl;

	//test case #1:
	cout << "tab, bat: " <<
		isAnagram("tab", "bat")
		<< " (expected: true)"
		<< endl;

	//test case #2
	cout << "bat, tab: " <<
		isAnagram("bat", "tab")
		<< " (expected: true)"
		<< endl;

	//test case #3
	cout << "(empty), (empty): " <<
		isAnagram("", "")
		<< " (expected: true)"
		<< endl;

	//test case #4
	cout << "dog, cat: " <<
		isAnagram("dog", "cat")
		<< " (expected: false)"
		<< endl;

	//test case #5
	cout << "castles, castle: " <<
		isAnagram("castles", "castle")
		<< " (expected: false)"
		<< endl;

	//test case #6
	cout << "bat, tabb: " <<
		isAnagram("bat", "tabb")
		<< " (expected: false)"
		<< endl;

//most common substring
	cout << endl << endl << "***Most common substring***" << endl;

	//test case #1
	cout << "abcabcdefdefabc. 3: " <<
		mostCommonSubstring("abcabcdefdefabc", 3)
		<< " (expected: abc)"
		<< endl;

	//test case #2
	cout << "defdefabcabc, 3: " <<
		mostCommonSubstring("defdefabcabc", 3)
		<< " (expected: def)"
		<< endl;

	//test case #3
	cout << "aaabbcccc, 1: " <<
		mostCommonSubstring("aaabbcccc", 1)
		<< " (expected: c)"
		<< endl;

	//test case #4
	cout << "abcdefhijklmnopqrstuvwxyz, 4: " <<
		mostCommonSubstring("abcdefhijklmnopqrstuvwxyz", 4)
		<< " (expected: abcd)"
		<< endl;

	//test case #5
	cout << "abc, 5: " <<
		mostCommonSubstring("abc", 5)
		<< " (expected: NULL)"
		<< endl;

	//test case #6
	cout << "(Empty), 1: " <<
		mostCommonSubstring("", 1)
		<< " (expected: NULL)"
		<< endl;

	//test case #7
	cout << "abcabcab, 3: " <<
		mostCommonSubstring("abcabcab", 3)
		<< " (expected: abc)"
		<< endl;

	//test case #8
	cout << "abcabcab, 0: " <<
		mostCommonSubstring("abcabcab", 0)
		<< " (expected: NULL)"
		<< endl;

	return 0;
}