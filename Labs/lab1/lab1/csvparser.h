#pragma once

#ifndef CSV_PARSER_H
#define CSV_PARSER_H

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
 
using namespace std;

class CsvStateMachine;	//has states
class CsvState;			//is a state
class DefaultState;		//is a state
class QuoteState;		//is a state
class DoubleQuoteState;	//is a state
class EndState;			//is a state

// csv state machine represents the entire state machine
class CsvStateMachine
{
private:
	// csv state machine needs a record of all possible states
	CsvState* _default_state = nullptr;
	CsvState* _quote_state = nullptr;
	CsvState* _double_quote_state = nullptr;
	CsvState* _end_state = nullptr;

	// a state is needed to keep track of the current/active state
	CsvState* _active_state = nullptr;

	// Object form of CSV file
	vector<vector<string>> _table;

	// file form of csv file
	ifstream _csv_stream;

	// object form of current row in file
	vector<string> _current_row;

	// raw form of current row
	string _raw_row;

	// keep track of position/character in row being processed
	int _current_row_position;

	// ostringstream is used to programmatically build strings efficiently
	ostringstream _current_cell;

public:
	// set up states
	CsvStateMachine(string file_name)
	{
		_default_state = new DefaultState(this);
		_quote_state = new QuoteState(this);
		_double_quote_state = new DoubleQuoteState(this);
		_end_state = new EndState(this);

		// at the beginning, the default state is the active state
		_active_state = _default_state;

		//set up the file stream for processing
		_csv_stream = ifstream{ file_name };
	}

	// destruct all dynamically created variables
	~CsvStateMachine()
	{
		delete _default_state;
		delete _quote_state;
		delete _double_quote_state;
		delete _end_state;
	}

	// setter functions allow states to alter the overall state machine
	void setStateToDefaultState()
	{
		_active_state = _default_state;
	}
	void setStateToQuoteState()
	{
		_active_state = _quote_state;
	}
	void setStateToDoubleQuoteState()
	{
		_active_state = _double_quote_state;
	}
	void setStateToEndState()
	{
		_active_state = _end_state;
	}

	//allows the active state to add content to the current cell
	void appendToCurrentCell(char ch)
	{
		_current_cell << ch;
	}
	
	// allows the active state to see the character is has to process
	char getNextCharToProcess()
	{
		// make sure that there is data to process
		if (_raw_row.length() <= _current_row_position)
		{
			return '\0';
		}
		char result = _raw_row[_current_row_position];
		_current_row_position++;
		return result;
	}

	vector<vector<string>> processFile()
	{
		//get the first line to prime the loop
		getline(_csv_stream, _raw_row);
		while (_csv_stream.good() == true && _raw_row.length() > 0)
		{
			if (_raw_row.length() == _current_row_position || _active_state == _end_state)
			{
				// current cell is an ostringstream so needs to be converted to actual string with .str()
				_current_row.push_back(_current_cell.str());

				// reset current cell
				_current_cell = ostringstream();

				//reset state machine
				setStateToDefault();
			}

			if(_raw_row.)
			if (_raw_row[_current_row_position - 1] == ',')
			{
				_current_row.push_back("");
			}
			else
			{
				// no new cell or line needed continue to run state machine
				_active_state->handle();
			}
		}
	}
};


// all states
class CsvState
{
public:
	virtual ~CsvState() {};	
	//virtual allows children classes to change the behavior of the parent

	CsvState(CsvStateMachine* machine)
	{
		_machine = machine;
	}

	virtual void handle() = 0;	
	// "=0" is a pure virtual function. 
	// 1. means that we cannot create an instance of this class directly because it is marked as abstract
	// 2. ensures that every concrete instate of CsvState must implement this function

protected:
	CsvStateMachine* _machine = nullptr;
};

class DefaultState : public CsvState
{
public:
	DefaultState(CsvStateMachine* machine) : CsvState(machine)
	{

	}

	virtual void handle();
};
class QuoteState : public CsvState
{
public:
	QuoteState(CsvStateMachine* machine) : CsvState(machine)
	{

	}

	virtual void handle();
};
class DoubleQuoteState : public CsvState
{
public:
	DoubleQuoteState(CsvStateMachine* machine) : CsvState(machine)
	{

	}

	virtual void handle();
};
class EndState : public CsvState
{
public:
	EndState(CsvStateMachine* machine) : CsvState(machine)
	{

	}

	virtual void handle();
};

// all logic for all states
void DefaultState::handle()
{
	//logic for when in the default state
	char next_char = _machine->getNextCharToProcess();

	// if , go to end state
	if (next_char == ',')
	{
		_machine->setStateToEndState();
	}
	// if " go to quote state
	else if (next_char == '"')	
	{
		_machine->setStateToQuoteState();
	}
	// otherwise add it to the current cell
	else
	{
		_machine->appendToCurrentCell(next_char);
	}
}
void QuoteState::handle()
{
	char next_char = _machine->getNextCharToProcess();

	// if , go to end
	if (next_char == '"')
	{
		_machine->setStateToDoubleQuoteState();
	}
}
void DoubleQuoteState::handle()
{
	char next_char = _machine->getNextCharToProcess();

	if (next_char == ',')
	{
		_machine->setStateToEndState();
	}
	else
	{
		// fringe cases mess this logic up
		_machine->appendToCurrentCell(next_char);
		if (next_char == '"')
		{
			_machine->setStateToQuoteState();
		}
		else
		{
			_machine->setStateToDefaultState();
		}
	}
}
void EndState::handle()
{
	// nothing to do if in end state
}

#endif