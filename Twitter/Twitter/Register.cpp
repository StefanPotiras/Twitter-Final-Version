#include<regex>
#include "Register.h"
bool Register::HasPasswordCorrectPattern(const std::string& pass)
{
	
	std::regex correctPassword{R"(^(?=.*[A-Za-z])(?=.*\d)[A-Za-z\d]{8,}$)"};
	if (std::regex_match(pass, correctPassword)) {

		return true;
	}
	else return false;


}

bool Register::VerifyUsername(const std::string& userName)
{ 
	//std::regex correctUsername{ R"(^(?=.{8,20}$)(?![_.])(?!.*[_.]{2})[a-zA-Z0-9._]+(?<![_.])$)" };
	std::regex correctUsername{ R"([a-zA-Z0-9]+)" };
	if (std::regex_match(userName, correctUsername)) {

		return true;
	}
	else return false;
}

bool Register::VerifyPassword(const std::string& pass)
{
	//std::regex correctPassword{ R"([a-zA-Z]+[0-9]*{7,15})" };
	std::regex correctPassword{ R"([a-zA-Z0-9]+)" };
	if (std::regex_match(pass, correctPassword)) {

		return true;
	}
	else return false;
}
