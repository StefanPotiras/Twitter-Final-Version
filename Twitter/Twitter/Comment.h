#pragma once
#include<string>

class Comment
{ public:
Comment();
Comment(uint64_t id_comment, uint64_t id_user, const std::string& comment, const std::string& timeOfComment, const std::string& usernameCom);

const std::string& GetComment() const;
const std::string& GetTimeOfComment() const;
const uint64_t GetIdComment() const;
const uint64_t GetIdUser() const;
const uint64_t GetIdPost() const;
const std::string& GetUsername() const;
void SetComment(const std::string& comment);

private:
	uint64_t m_id_comment;
	uint64_t m_id_user;
	uint64_t m_id_post;
	std::string m_comment;
	std::string m_timeOfComment;
	std::string m_usernameCom;

};

