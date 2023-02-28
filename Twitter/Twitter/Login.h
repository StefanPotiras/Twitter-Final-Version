#pragma once
#include <QObject>
#include <regex>
class Login : public QObject
{
	Q_OBJECT

public:
	Login(QObject *parent);
	Login();
	Login(const std::string &username, const std::string& password);

	~Login();

public:
	void SetUsername(const std::string& username);
	void SetPassword(const std::string& password);
	const std::string& GetUsername() const;
	const std::string& GetPassword() const;
	bool VerifyUsername();
	bool VerifyPassword();


private:
	std::string m_username;
	std::string m_password;
};
