#pragma once
#include <vector>
#include <string>
class User
{
public:
	User();
	User(const std::string& username,const std::string &password,const bool &userRegistered);
	const std::string& GetUsername() const;
	const std::string& GetPassword() const;
	const bool& GetUserRegistered() const;
	void setUsername(std::string username);
	void setPassword(std::string password);
	void setUserRegistered(bool userRegistered);

private:
	std::string m_username;
	std::string m_password;
	bool m_userRegistered;

};

