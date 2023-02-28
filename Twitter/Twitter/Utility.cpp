#include "Utility.h"


static std::unordered_map <std::string, std::string> m_searchedUsernames;

std::unordered_map <std::string, std::string> Utility::GetSearchedUsernames()
{
    return m_searchedUsernames;
}

void Utility::SetSearchedUsernames(std::unordered_map <std::string, std::string> searchedUsernames)
{
    m_searchedUsernames = searchedUsernames;
}

std::string Utility::GetId(std::string username)
{
    return m_searchedUsernames[username];
}
