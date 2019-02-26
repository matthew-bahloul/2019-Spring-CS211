#include <iostream>
#include <stack>
#include <istream>
#include <string>
#include "StringSplitter.h"

using namespace std;

int main(void)
{
	stack<int> numbers;
	int result = NULL;
	int operator_count = 0;
	string expression_string = "";
	string go_again = "y";

	cout << "*** Postfix Evaluator***" << endl;

	while (go_again == "Y" or go_again == "y")
	{
		cout << "Enter an expression to evaluate: ";

		getline(cin, expression_string);
		vector<string> expression_vec = StringSplitter::split(expression_string, " ");

		for (auto item : expression_vec)
		{ 
			try
			{
				numbers.push(stoi(item));
			}
			catch (...)
			{
				int right = numbers.top();
				numbers.pop();
				int left = numbers.top();
				numbers.pop();

				if (item == "+")
				{
					numbers.push(left + right);
					operator_count++;
				}
				else if (item == "-")
				{
					numbers.push(left - right);
					operator_count++;
				}
				else if (item == "*")
				{
					numbers.push(left * right);
					operator_count++;
				}
				else if (item == "/")
				{
					numbers.push(left / right);
					operator_count++;
				}
				else
				{
					cout << "Bad expression, press any key to exit" << endl;
					cin.get();
					exit(1);
				}
			}	
		}

		result = numbers.top();

		cout << "Result: " << result << endl;
		cout << "Continue (y/n)?: ";
		getline(cin, go_again);
	}

	return 0;
}