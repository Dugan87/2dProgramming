#pragma once

#include <string>
#include <map>
#include <functional>

class Player
{

public:
	Player() : state("idle") {}

	void CreateFSM();
	void Update(char op);

private:
	std::string idleState(char op);
	std::string walkState(char op);
	std::string runState(char op);

	typedef std::function<std::string(char)> StateFunc;
	typedef std::map<std::string, StateFunc> StateFuncMap;

		StateFuncMap fsm;
		std::string state;
};

