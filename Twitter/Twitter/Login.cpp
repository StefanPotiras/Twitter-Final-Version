#include "Login.h"

Login::Login(QObject *parent)
	: QObject(parent)
{}

Login::Login()
{}

Login::Login(const std::string & username, const std::string & password)
	:m_username(username)
	,m_password(password)
{}

Login::~Login()
{}

void Login::SetUsername(const std::string& username)
{
	this->m_username = username;
}

void Login::SetPassword(const std::string& password)
{
	this->m_password = password;
}

const std::string& Login::GetUsername() const
{
	return m_username;
}

const std::string& Login::GetPassword() const
{
	return m_password;
}

bool Login::VerifyUsername()
{

	//std::regex correctUsername{ R"(^(?=.{8,20}$)(?![_.])(?!.*[_.]{2})[a-zA-Z0-9._]+(?<![_.])$)" };
	std::regex correctUsername{ R"([a-zA-Z0-9])" };
	if (std::regex_match(this->GetPassword(), correctUsername)) {

		return true;
	}
	else return false;

}

bool Login::VerifyPassword()
{
	//std::regex correctPassword{ R"([a-zA-Z]+[0-9]*{7,15})" };
	std::regex correctPassword{ R"([a-zA-Z0-9])" };
	if (std::regex_match(this->GetPassword(), correctPassword)) {

		return true;
	}
	else return false;
}