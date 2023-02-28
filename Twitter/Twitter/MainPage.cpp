#include "MainPage.h"

MainPage::MainPage()
	: m_searchPost("")
	, m_userSearch("")
	, m_textPost("")
	, m_feed()
{
}

MainPage::MainPage(std::string searchPost, std::string userSearch, std::string textPost, std::priority_queue<Post>feed)
	: m_searchPost(searchPost)
	, m_userSearch(userSearch)
	, m_textPost(textPost)
	, m_feed(feed)
{
}

const std::string& MainPage::GetSearchPost() const
{
	return m_searchPost;
}

const std::string& MainPage::GetUserSearch() const
{
	return m_userSearch;
}

const std::string& MainPage::GetTextPost() const
{
	return m_textPost;
}

const std::priority_queue<Post>& MainPage::GetFeed() const
{
	return m_feed;
}

void MainPage::SetSearchPost(const std::string& searchPost)
{
	m_searchPost = searchPost;
}

void MainPage::SetUserPost(const std::string& userSearch)
{
	m_userSearch = userSearch;
}

void MainPage::SetTextPost(const std::string& textPost)
{
	m_textPost = textPost;
}

void MainPage::SetFeed(const std::priority_queue<Post> feed)
{
	m_feed = feed;
}
