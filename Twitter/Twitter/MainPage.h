#pragma once
#include "Post.h"
#include <string>
#include <queue>

class MainPage
{

public:
	MainPage();
	MainPage(std::string searchPost, std::string userSearch, std::string textPost, std::priority_queue<Post>feed);

	void calculatePriority();
	void heywordSearch();
	void userSearch();
	void showPost();
	void createPost();
	void goToProfile();
	void logout();

	const std::string& GetSearchPost() const;
	const std::string& GetUserSearch() const;
	const std::string& GetTextPost() const;
	const std::priority_queue<Post>& GetFeed()const;

	void SetSearchPost(const std::string& searchPost);
	void SetUserPost(const std::string& userSearch);
	void SetTextPost(const std::string& textPost);
	void SetFeed(const std::priority_queue<Post>feed);

private:
	std::string m_searchPost;
	std::string m_userSearch;
	std::string m_textPost;
	std::priority_queue<Post>m_feed;

};

