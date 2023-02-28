#include "ClientManagement.h"
#include<fstream>
#include <chrono>
#include <cstdint>
#include <iostream>
#include"../CommonClasses/PostPersonalProfile.h"
#include"../CommonClasses/CommentServer.h"
#include"../CommonClasses/Repost.h"
#include <chrono>
#include <thread>
#include<string>
ClientManagement::Action ClientManagement::FromStringToAction(const std::string& actionString)
{
	if (actionString == "Register")
		return Action::eRegister;
	else if (actionString == "Login")
		return Action::eLogin;
	else if (actionString == "UserSearch")
		return Action::eUserSearch;
	else if (actionString == "UserPostSend")
		return Action::eUserPostSend;
	else if (actionString == "UserPostPersonal")
		return Action::eUserPostPersonal;
	else if (actionString == "FollowAndFollowing")
		return Action::eFollowAndFollowing;
	else if (actionString == "FollowStats")
		return Action::eFollowStats;
	else if (actionString == "FollowOrUnfollow")
		return Action::eFollowOrUnfollow;
	else if (actionString == "KeywordSearch")
		return Action::eKeywordSearch;
	else if (actionString == "LikeAndDislikeStats")
		return Action::eLikeAndDislikeStats;
	else if (actionString == "LikeOrDislikeMake")
		return Action::eLikeOrDislikeMake;
	else if (actionString == "Comment")
		return Action::eComment;
	else if (actionString == "Feed")
		return Action::eFeed;
	else if (actionString == "Repost")
		return Action::eRepost;

}

std::string ClientManagement::FromActionToaString(ClientManagement::Action action)
{
	switch (action)
	{
	case Action::eLogin:
		return "Login";
		break;
	case Action::ePost:
		return "Post";
		break;
	case Action::eRegister:
		return "Register";
		break;
	case Action::eUserSearch:
		return "UserSearch";
		break;
	case Action::eUserPostSend:
		return "UserPostSend";
		break;
	case Action::eUserPostPersonal:
		return "UserPostPersonal";
		break;
	case Action::eFollowAndFollowing:
		return "FollowAndFollowing";
		break;
	case Action::eFollowStats:
		return "FollowStats";
		break;
	case Action::eFollowOrUnfollow:
		return "FollowOrUnfollow";
		break;
	case Action::eKeywordSearch:
		return "KeywordSearch";
		break;
	case Action::eLikeAndDislikeStats:
		return "LikeAndDislikeStats";
		break;
	case Action::eLikeOrDislikeMake:
		return "LikeOrDislikeMake";
		break;
	case Action::eComment:
		return "Comment";
		break;
	case Action::eFeed:
		return "Feed";
		break;
	case Action::eRepost:
		return "Repost";
		break;
	}
	return std::string();
}
bool ClientManagement::IsEmpty(std::ifstream& pFile)
{
	return pFile.peek() == std::ifstream::traits_type::eof();;
}



std::vector<std::shared_ptr<PostPersonalProfile>> ClientManagement::ReadFromFilePostPersonalInitial(int id_user)
{
	std::vector<std::shared_ptr<PostPersonalProfile>>personalProfileVector;

	while (true)
	{
		std::string actiune, next;
		std::string id_user_temp;
		std::ifstream fin("../Server/server.out");
		if (IsEmpty(fin) != true)
		{
			std::ifstream fin("../Server/server.out");
			std::getline(fin, actiune);
			std::getline(fin, id_user_temp);
			if (id_user_temp == std::to_string(id_user) && actiune == FromActionToaString(Action::eUserPostPersonal))
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(100));

				std::getline(fin, next);
				if (next == "FALSE")
				{
					std::ofstream ofs("../Server/server.out", std::ios::out | std::ios::trunc);
					return personalProfileVector;
				}
				else if (next == "TRUE")
				{
					std::string size;
					std::getline(fin, size);

					for (int i = 0; i < std::stoi(size); i++)
					{
						std::string id_post, like, dislike;
						std::string postText, postDate;
						std::getline(fin, id_post);
						std::getline(fin, postText);
						std::getline(fin, postDate);
						std::getline(fin, like);
						std::getline(fin, dislike);
						std::string nextCom;
						std::getline(fin, nextCom);
						std::vector<std::shared_ptr<CommentServer>>commentPostProf;
						if (nextCom == "COMTRUE")
						{
							std::string sizeCom;
							std::getline(fin, sizeCom);
							for (int i = 0; i < std::stoi(sizeCom); i++)
							{
								std::string id_com, id_user_com;
								std::string comm, dateCom, usernameCom;
								std::getline(fin, id_com);
								std::getline(fin, id_user_com);
								std::getline(fin, usernameCom);
								std::getline(fin, comm);
								std::getline(fin, dateCom);

								commentPostProf.emplace_back(new CommentServer(std::stoi(id_com), std::stoi(id_user_com), comm, dateCom, usernameCom));

							}
						}
					
						personalProfileVector.emplace_back(new PostPersonalProfile(std::stoi(id_post), postText, commentPostProf, std::stoi(like), std::stoi(dislike), postDate));
					}


					std::ofstream ofs("../Server/server.out", std::ios::out | std::ios::trunc);
					return personalProfileVector;
				}
			}
		}
	}

}

std::pair<uint64_t, uint64_t> ClientManagement::ReadFromFileNumberOfFollowingAndFollowers(uint64_t id_user)
{
	std::string actiune;
	uint64_t NumberOfFollowers;
	uint64_t NumberOfFollowing, id_user_temp;
	while (true)
	{
		std::ifstream fin("../Server/server.out");
		if (IsEmpty(fin) != true)
		{
			fin >> actiune;
			fin >> id_user_temp;
			if (id_user_temp == id_user && actiune == FromActionToaString(Action::eFollowAndFollowing))
			{
				fin >> NumberOfFollowing;
				fin >> NumberOfFollowers;
				std::ofstream ofs("../Server/server.out", std::ios::out | std::ios::trunc);
				return std::make_pair(NumberOfFollowing, NumberOfFollowers);
			}
		}

	}
}

int ClientManagement::ReadFromFileLogin(uint64_t time)
{
	std::string actiune, confirmare;
	int id_user;
	uint64_t timeCurent;

	while (true)
	{
		std::ifstream fin("../Server/server.out");
		if (IsEmpty(fin) != true)
		{
			fin >> actiune;
			fin >> id_user;
			fin >> timeCurent;
			fin >> confirmare;
			if (timeCurent == time && actiune == FromActionToaString(Action::eLogin))
			{
				if (confirmare == "FALSE")
				{
					std::ofstream ofs("../Server/server.out", std::ios::out | std::ios::trunc);
					return id_user;
					break;
				}
				else
					if (confirmare == "TRUE")
					{
						std::ofstream ofs("../Server/server.out", std::ios::out | std::ios::trunc);
						return id_user;
						break;
					}
			}
		}

	}
}

bool ClientManagement::ReadFromFileRegister(uint64_t time)
{
	std::string actiune, confirmare;
	uint64_t timeCurent;

	while (true)
	{
		std::ifstream fin("../Server/server.out");
		fin >> actiune;
		fin >> timeCurent;
		fin >> confirmare;
		if (timeCurent == time && actiune == FromActionToaString(Action::eRegister))
		{
			if (confirmare == "FALSE")
			{
				std::ofstream ofs("../Server/server.out", std::ios::out | std::ios::trunc);
				return false;
				break;
			}
			else
				if (confirmare == "TRUE")
				{
					std::ofstream ofs("../Server/server.out", std::ios::out | std::ios::trunc);
					return true;
					break;
				}

		}
	}
}

bool ClientManagement::ReadFromFileFollowStats(uint64_t id_user)
{
	uint64_t id_user_temp;
	while (true)
	{
		std::ifstream fin("../Server/server.out");
		if (IsEmpty(fin) == false)
		{
			std::string actionString, rez;
			fin >> actionString;
			if (FromStringToAction(actionString) == Action::eFollowStats) {
				fin >> id_user_temp;
				if (id_user_temp == id_user)
				{
					fin >> rez;
					if (rez == "TRUE")
					{
						std::ofstream ofs("../Server/server.out", std::ios::out | std::ios::trunc);
						return true;
					}
					else if (rez == "FALSE")
					{
						std::ofstream ofs("../Server/server.out", std::ios::out | std::ios::trunc);
						return false;
					}
				}
			}
		}
	}
}

std::vector<std::shared_ptr<Post>> ClientManagement::ReadFromFeed()
{
	std::vector<std::shared_ptr<Post>> m_keywordPosts;
	//std::vector<std::shared_ptr<CommentServer>>comment;

	while (true) {

		std::ifstream fin("../Server/server.out");

		if (IsEmpty(fin) == false)
		{
			Action action; 
			std::string actionString;
			std::getline(fin, actionString);
			action = FromStringToAction(actionString);
			
			if (action == Action::eFeed) {

				std::string numberPost;
				std::getline(fin, numberPost);
				std::this_thread::sleep_for(std::chrono::milliseconds(100));

				for (int i = 0; i < std::stoi(numberPost); ++i) {

					std::string postareCheck;
					std::getline(fin, postareCheck);

					std::string idPost, idRepost;
					std::string repostText, postText;
					std::string usernamePost, usernameRepost;
					std::string timeOfRepost, timePost;
					std::string likes, dislikes, idUser, idUserRepost;

					if (postareCheck == "REPOSTARE") {

						std::getline(fin, idRepost);
						std::getline(fin, idPost);
						//std::cout << idPost << "\n";
						std::getline(fin, repostText);
						std::getline(fin, postText);
						std::getline(fin, usernamePost);
						std::getline(fin, usernameRepost);
						std::getline(fin, idUser);
						std::getline(fin, idUserRepost);
						std::getline(fin, timeOfRepost);
						std::getline(fin, timePost);
						std::getline(fin, likes);
						//std::cout << likes << "\n";
						std::getline(fin, dislikes);
						//std::cout << dislikes << "\n";
					}
					else {
						std::getline(fin, idPost);
						//std::cout << idPost << "\n";
						std::getline(fin, postText);
						std::getline(fin, usernamePost);
						std::getline(fin, idUser);
						std::getline(fin, timePost);
						std::getline(fin, likes);
						//std::cout << likes << "\n";
						std::getline(fin, dislikes);
						//std::cout << dislikes << "\n";
					}

					std::string nextCom;
					std::getline(fin, nextCom);
					std::vector<std::shared_ptr<CommentServer>>comment;
					if (nextCom == "COMTRUE") {

						std::string sizeCom;
						std::getline(fin, sizeCom);
						for (int i = 0; i < std::stoi(sizeCom); i++)
						{
							std::string id_com, id_user_com;
							std::string comm, dateCom, usernameCom;
							std::getline(fin, id_com);
							std::getline(fin, id_user_com);
							std::getline(fin, usernameCom);
							std::getline(fin, comm);
							std::getline(fin, dateCom);

							comment.emplace_back(new CommentServer(std::stoi(id_com), std::stoi(id_user_com), comm, dateCom, usernameCom));

						}

					}

					if (postareCheck == "REPOSTARE") {
						m_keywordPosts.emplace_back(new Repost(std::stoi(idRepost), std::stoi(idUserRepost), usernameRepost, repostText, timeOfRepost,
							std::stoi(idUser), usernamePost, std::stoi(idPost), postText, comment, std::stoi(likes), std::stoi(dislikes), timePost));
					}
					else {
						m_keywordPosts.emplace_back(new Post(std::stoi(idUser), usernamePost, std::stoi(idPost), postText, comment, std::stoi(likes), std::stoi(dislikes), timePost));
					}


				}
				std::ofstream ofs("../Server/server.out", std::ios::out | std::ios::trunc);
				return m_keywordPosts;
			}

		}
	}
	return m_keywordPosts;
}

std::vector<std::shared_ptr<Post>> ClientManagement::ReadFromFileKeyword()
{
	std::vector<std::shared_ptr<Post>> m_keywordPosts;
	

	while (true) {
		
		std::ifstream fin("../Server/server.out");

		if (IsEmpty(fin) == false)
		{
			Action action;
			std::string actionString;
			std::getline(fin, actionString);
			action = FromStringToAction(actionString);
			std::cout << actionString;
			if (action == Action::eKeywordSearch) {
				
				std::string numberPost;
				std::getline(fin, numberPost);
				std::this_thread::sleep_for(std::chrono::milliseconds(100));

				for (int i = 0; i < std::stoi(numberPost); ++i) {

					std::string postareCheck;
					std::getline(fin, postareCheck);

					std::string idPost, idRepost;
					std::string repostText, postText;
					std::string usernamePost, usernameRepost;
					std::string timeOfRepost, timePost;
					std::string likes, dislikes, idUser, idUserRepost;

					if (postareCheck == "REPOSTARE") {
						
						std::getline(fin, idRepost);
						std::getline(fin, idPost);
						//std::cout << idPost << "\n";
						std::getline(fin, repostText);
						std::getline(fin, postText);
						std::getline(fin, usernamePost);
						std::getline(fin, usernameRepost);
						std::getline(fin, idUser);
						std::getline(fin, idUserRepost);
						std::getline(fin, timeOfRepost);
						std::getline(fin, timePost);
						std::getline(fin, likes);
						//std::cout << likes << "\n";
						std::getline(fin, dislikes);
						//std::cout << dislikes << "\n";
					}
					else {
						std::getline(fin, idPost);
						//std::cout << idPost << "\n";
						std::getline(fin, postText);
						std::getline(fin, usernamePost);
						std::getline(fin, idUser);
						std::getline(fin, timePost);
						std::getline(fin, likes);
						//std::cout << likes << "\n";
						std::getline(fin, dislikes);
						//std::cout << dislikes << "\n";
					}

					std::string nextCom;
					std::getline(fin, nextCom);
					std::vector<std::shared_ptr<CommentServer>>comment;
					if (nextCom == "COMTRUE") {

						std::string sizeCom;
						std::getline(fin, sizeCom);
						for (int i = 0; i < std::stoi(sizeCom); i++)
						{
							std::string id_com, id_user_com;
							std::string comm, dateCom, usernameCom;
							std::getline(fin, id_com);
							std::getline(fin, id_user_com);
							std::getline(fin, usernameCom);
							std::getline(fin, comm);
							std::getline(fin, dateCom);

							comment.emplace_back(new CommentServer(std::stoi(id_com), std::stoi(id_user_com), comm, dateCom, usernameCom));

						}
						
					}
					
					if (postareCheck == "REPOSTARE") {
						m_keywordPosts.emplace_back(new Repost(std::stoi(idRepost), std::stoi(idUserRepost), usernameRepost, repostText, timeOfRepost,
							std::stoi(idUser), usernamePost, std::stoi(idPost), postText, comment, std::stoi(likes), std::stoi(dislikes), timePost));
					}
					else {
						m_keywordPosts.emplace_back(new Post(std::stoi(idUser), usernamePost, std::stoi(idPost), postText, comment, std::stoi(likes), std::stoi(dislikes), timePost));
					}
					

				}
				std::ofstream ofs("../Server/server.out", std::ios::out | std::ios::trunc);
				return m_keywordPosts;
			}
			
		}
	}
	return m_keywordPosts;
}

int ClientManagement::ReadFromFileLikeAndDislikeStats(uint64_t id_user)
{
	
	while (true)
	{
		std::ifstream fin("../Server/server.out");
		if (IsEmpty(fin) == false)
		{
			Action action;
			std::string actionString;
			int id_user_curent;
			fin >> actionString;
			fin >> id_user_curent;
			if (FromStringToAction(actionString) == Action::eLikeAndDislikeStats && id_user==id_user_curent) {
				std::string stats;
				fin >> stats;
				std::ofstream ofs("../Server/server.out", std::ios::out | std::ios::trunc);
				if (stats == "LIKE")
					return 1;
				else if (stats == "DISLIKE")
					return -1;
				else if (stats == "NO")
					return 0;								
			}		
			
		}
	}
}

std::vector<std::pair<std::string, std::string>> ClientManagement::ReadFromFileUserSearch()
{
	std::vector<std::pair<std::string, std::string>>usernames;
	std::string username;
	std::string id;

	while (true)
	{
		std::ifstream fin("../Server/server.out");
		if (IsEmpty(fin) == false)
		{
			Action action;
			std::string actionString;
			fin >> actionString;
			action = FromStringToAction(actionString);

			if (action == Action::eUserSearch) {

				while (fin >> username >> id) {

					std::cout << "\n" << username << " " << id << "\n";
					usernames.push_back(std::make_pair(username, id));

				}
			}
			std::ofstream ofs("../Server/server.out", std::ios::out | std::ios::trunc);
			return usernames;

		}
	}
}

uint64_t ClientManagement::TimeSinceEpochMillisec()
{
	using namespace std::chrono;
	return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}
