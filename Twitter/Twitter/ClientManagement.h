#pragma once
#include<string>
#include <vector>
#include"UserTwitter.h"
#include"../CommonClasses/PostPersonalProfile.h"
#include"../CommonClasses/Post.h"
#include<fstream>
#include"Comment.h"
class ClientManagement
{
public:
	enum class Action
	{
		eRegister,
		eLogin,
		ePost,
		eUserSearch,
		eUserPostPersonal,
		eUserPostSend,
		eFollowAndFollowing,
		eFollowStats,
		eFollowOrUnfollow,
		eKeywordSearch,
		eLikeAndDislikeStats,
		eLikeOrDislikeMake,
		eComment,
		eFeed,
		eRepost
	};
	


	static std::vector<std::shared_ptr<PostPersonalProfile>> ReadFromFilePostPersonalInitial(int id_user);
	static std::pair<uint64_t, uint64_t> ReadFromFileNumberOfFollowingAndFollowers(uint64_t id_user);
	static int ReadFromFileLogin(uint64_t time);
	static bool ReadFromFileRegister(uint64_t time);
	static bool ReadFromFileFollowStats(uint64_t id_user);
	static std::vector<std::shared_ptr<Post>> ReadFromFeed();
	static std::vector<std::shared_ptr<Post>> ReadFromFileKeyword();
	static int ReadFromFileLikeAndDislikeStats(uint64_t id_user);

	static std::vector<std::pair<std::string, std::string>> ReadFromFileUserSearch();
	static uint64_t TimeSinceEpochMillisec();
		
	template<class... T>
	static void WriteInFileAction(T&& ...args);


	static Action FromStringToAction(const std::string& actionString);
	static std::string FromActionToaString(ClientManagement::Action action);
private:
	static bool IsEmpty(std::ifstream& pFile);
};

template<class... T>
void ClientManagement::WriteInFileAction(T&& ...args)
{ 
	while (true)
	{
		std::ifstream fin("../Server/server.in");
		if (IsEmpty(fin) == true)
		{
			std::ofstream out("../Server/server.in");
			((out << std::forward<T>(args) << "\n"), ...);
			break;
		}
	}
}

