#pragma once
#include <QObject>

class Register
{
public:
	static bool HasPasswordCorrectPattern(const std::string& pass);
    static bool VerifyUsername(const std::string& userName);
	static bool VerifyPassword(const std::string& pass);
};