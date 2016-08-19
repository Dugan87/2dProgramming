#include <iostream>
#include <memory>
#include <functional>

#include "Player.h"

using namespace std;

#define BIND_STATE(func) std::bind(&Player::func, this, placeholders::_1)

void Player::CreateFSM()
{
	fsm["idle"] = BIND_STATE(idleState);
	fsm["walk"] = BIND_STATE(walkState);
	fsm["run"] =  BIND_STATE(runState);
}

void Player::Update(char op)
{
	string new_state = fsm[state](op);
	state = new_state.empty() ? state : new_state;
}


string Player::idleState(char op)
{
	cout << "idle" << endl;
	if (op == 'f' || op == 'F')
		return "walk";

	return "";
}

string Player::walkState(char op)
{
	cout << "walk" << endl;

	if (op == 'F')
		return "run";
	else if (op == 'f')
		return "";
	else
		return "idle";
}

string Player::runState(char op)
{
	cout << "Bolt!!" << endl;
	if (op != 'F')
		return "walk";

	return "";
}






