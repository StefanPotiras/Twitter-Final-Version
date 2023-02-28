#include "UserTwitter.h"

UserTwitter::UserTwitter() 
	:m_username()
	,m_password()
	,m_userRegistered()
{}

UserTwitter::UserTwitter(const std::string& username, const std::string& password)
	:m_username(username)
	,m_password(password)
	
{}

const std::string& UserTwitter::GetUsername() const
{
	return m_username;
}

const std::string& UserTwitter::GetPassword() const
{
	return m_password;
}

const uint64_t UserTwitter::GetIdUser() const
{
	return m_id_user;
}

const bool& UserTwitter::GetUserRegistered() const
{
	return m_userRegistered;
}

void UserTwitter::SetIdUser(uint64_t id_user)
{
	m_id_user = id_user;
}

void UserTwitter::SetUsername(std::string username)
{
	this->m_username = username;
}

void UserTwitter::SetPassword(std::string password)
{
	this->m_password = password;
}

void UserTwitter::SetUserRegistered(bool userRegistered)
{
	this->m_userRegistered = userRegistered;
}