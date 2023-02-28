#pragma once
#include<string>
class KeywordSearch
{
public:
	std::string getKeyword();
	void setKeyword(std::string keyword);

private:
	std::string m_keyword;

};

