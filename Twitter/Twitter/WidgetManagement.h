#pragma once
#include <QObject>
#include<qpushbutton.h>
#include"../CommonClasses/CommonClasses.h"
#include<qlistwidget.h>
#include<qlabel.h>
class WidgetManagement : public QObject
{
	Q_OBJECT


public:
	WidgetManagement(QObject *parent);
	~WidgetManagement();
public:
	static void test(QPushButton* but);

	static void EnableButton(QPushButton*button);
	static void DisableButton(QPushButton* button);
	static void DislikeAndLikeButton(QPushButton* like, QPushButton* dislike,uint64_t id_user,uint64_t id_post, const std::string& type);

	static std::string FromObjectToString(std::shared_ptr<Post> post);

	static void LikeAction(QPushButton* like, QPushButton* dislike, uint64_t id_user, uint64_t id_post, const std::string& type, std::shared_ptr<Post> post);
	static void DislikeAction(QPushButton* like, QPushButton* dislike, uint64_t id_user, uint64_t id_post, const std::string& type, std::shared_ptr<Post> post);

	static void CommentManagement( QListWidget* list,std::vector<std::shared_ptr<CommentServer>>comment);
	static void ClearList(QListWidget* list);

	static void ProfileManagement(std::shared_ptr<PostPersonalProfile> all,QLabel* postLabel,QLabel* likeLabel,QLabel* dislikeLabel,QLabel*commentLabel);
};
