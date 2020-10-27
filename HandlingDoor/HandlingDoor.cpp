// HandlingDoor.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
//#include <cstdio>
//#include <conio.h>

using namespace std;

enum ActionEnum
{
	ACTION_CLOSE,  //0
	ACTION_OPEN,   //1
	ACTION_LOCK,   //2
	ACTION_UNLOCK  //3
};

class StateBase
{
public:
	virtual StateBase* GetNextState(int action) = 0;
	virtual  char* ToString() = 0;
};

//State Closed
class Closed : public StateBase
{
public:
	virtual StateBase* GetNextState(int action);
	virtual char* ToString() {
		return "Closed" ;
	}
};

//State Locked
class Locked : public StateBase
{
public:
	virtual StateBase* GetNextState(int action);
	virtual char* ToString() {
		return "Locked" ;
	}
};

//State Opened
class Opened : public StateBase
{
public:
	virtual StateBase* GetNextState(int action);
	virtual char* ToString() {
		return "Opened";
	}
};

StateBase* Closed::GetNextState(int action)
{
	if (action == 0 || action == 3) {
		cout << "Nothing happen !  \n\n";
		return new Closed();
	}
	else if (action == 2) {
		return new Locked();
	}
	else if (action == 1) {
		return new Opened();
	}
}

StateBase * Locked::GetNextState(int action)
{
	if (action == 3) {
		return new Closed();
	}
	else if (action == 0 || action == 1 || action == 2) {
		cout << "Nothing happen !  \n\n";
		return new Locked();
	}
	
}
StateBase * Opened::GetNextState(int action) {
	if (action == 0) {
		return new Closed();
	}
	else if (action == 1 || action == 2 || action == 3) {
		cout << "Nothing happen !  \n\n";
		return new Opened();
	}
 }
class TheDoor
{
public:
	TheDoor() {}
	TheDoor(StateBase* pContext) {
		m_pState = pContext;
	}
	~TheDoor() {
		delete m_pState;
	}
	//Handle state
	void StateChanged(int action) {
		if (m_pState) {
			StateBase* pState = m_pState->GetNextState(action);
			delete m_pState;
			m_pState = pState;
		}
	}
	//GetName
	char* GetStateName() {
		return m_pState->ToString();
	}
protected:
	StateBase* m_pState;
};

int main()
{
	int action;
	TheDoor Door(new Closed);
	cout << "There are 4 actions to do with a door:\n";
	cout << "0 : Close \n";
	cout << "1 : Open \n";
	cout << "2 : Lock \n";
	cout << "3 : Unlock \n\n";

	cout << "Firstly, The Door is " << Door.GetStateName() << "\n\n";
	while (1) {
		
		cin >> action;
		Door.StateChanged(action);
		cout << "The Door is " << Door.GetStateName() << "\n\n";
	}
	
	//system("pause");
}
