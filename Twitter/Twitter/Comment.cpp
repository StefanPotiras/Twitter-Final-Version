#include "Comment.h"


Comment::Comment()
{}

Comment::Comment(uint64_t id_comment, uint64_t id_user, const std::string& comment, const std::string& timeOfComment, const std::string& usernameCom)
    : m_id_comment(id_comment)
    , m_id_user(id_user)
    , m_comment(comment)
    , m_timeOfComment(timeOfComment)
    ,m_usernameCom(usernameCom)
{}


const std::string& Comment::GetComment() const
{
    return m_comment;
}

const std::string& Comment::GetTimeOfComment() const
{
    return m_timeOfComment;
}

const uint64_t Comment::GetIdComment() const
{
    return m_id_comment;
}

const uint64_t Comment::GetIdUser() const
{
    return m_id_user;
}

const uint64_t Comment::GetIdPost() const
{
    return m_id_post;
}

const std::string& Comment::GetUsername() const
{
    return m_usernameCom;
}

void Comment::SetComment(const std::string& comment)
{
    this->m_comment = comment;
}