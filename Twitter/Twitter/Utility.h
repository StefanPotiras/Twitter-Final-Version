#pragma once
#include <iostream>
#include <unordered_map>

class Utility
{

public:
	//GETERS & SETTERS
	static std::unordered_map <std::string, std::string> GetSearchedUsernames();
	static void SetSearchedUsernames(std::unordered_map <std::string, std::string> searchedUsernames);

	//METHODS
	static std::string GetId(std::string username);

};

