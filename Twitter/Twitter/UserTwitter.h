#pragma once
#include <vector>
#include <string>
class UserTwitter
{
public:
	UserTwitter();
	UserTwitter(const std::string& username,const std::string &password);
	const std::string& GetUsername() const;
	const std::string& GetPassword() const;
	const uint64_t GetIdUser() const;
	const bool& GetUserRegistered() const;
	void SetIdUser(uint64_t id_user);
	void SetUsername(std::string username);
	void SetPassword(std::string password);
	void SetUserRegistered(bool userRegistered);

private:
	uint64_t m_id_user;
	std::string m_username;
	std::string m_password;
	bool m_userRegistered;

};

