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


void DefaultState::handle()
{

}
void QuoteState::handle()
{

}
void DoubleQuoteState::handle()
{

}
void EndState::handle()
{

}

#endif