#include "WidgetManagement.h"
#include"ClientManagement.h"
WidgetManagement::WidgetManagement(QObject *parent)
	: QObject(parent)
{
}

WidgetManagement::~WidgetManagement()
{
}

void WidgetManagement::test(QPushButton* but)
{
	but->setText("Test");
}

void WidgetManagement::EnableButton(QPushButton* button)
{
	
	button->setStyleSheet("color:rgb(255, 255, 255);"
		"background-color:rgb(28, 162, 243);"
		"border-radius: 20px;");
}

void WidgetManagement::DisableButton(QPushButton* button)
{
	
	button->setStyleSheet("color:rgb(255, 255, 255);"
		"background-color: rgb(20 ,31, 42);"
		"border-top: 2px solid rgb(20, 60, 88);"
		"border-left: 2px solid rgb(20, 60, 88);"
		"border-right: 2px solid rgb(20, 60, 88);"
		"border-bottom: 2px solid rgb(20, 60, 88);"
		"border-radius: 20px;");
}

void WidgetManagement::DislikeAndLikeButton(QPushButton* like, QPushButton* dislike, uint64_t id_user,uint64_t id_post,const std::string& type)
{
	
	ClientManagement::WriteInFileAction(ClientManagement::FromActionToaString(ClientManagement::Action::eLikeAndDislikeStats),id_user,id_post,type);
	uint64_t stats = ClientManagement::ReadFromFileLikeAndDislikeStats(id_user);

	if (stats == 1)
	{
		EnableButton(like);
		DisableButton(dislike);
	}
	else if (stats == -1)
	{
		EnableButton(dislike);
		DisableButton(like);
	}
	else if (stats == 0)
	{
		DisableButton(dislike);
		DisableButton(like);
	}
}

std::string WidgetManagement::FromObjectToString(std::shared_ptr<Post> post)
{
	if (std::dynamic_pointer_cast<Repost>(post))
		return "REPOST";
	else if (std::dynamic_pointer_cast<Post>(post))
		return"POST";

}

void WidgetManagement::LikeAction(QPushButton* like, QPushButton* dislike, uint64_t id_user, uint64_t id_post, const std::string& type, std::shared_ptr<Post> post)
{
	ClientManagement::WriteInFileAction(ClientManagement::FromActionToaString(ClientManagement::Action::eLikeAndDislikeStats), id_user, id_post, type);	
	uint64_t stats = ClientManagement::ReadFromFileLikeAndDislikeStats(id_user);

	if (stats == 1)
	{
		DisableButton(like);
		
		ClientManagement::WriteInFileAction(ClientManagement::FromActionToaString(ClientManagement::Action::eLikeOrDislikeMake), 
			id_user, id_post, "LIKE", type, "DELETE");
		post->SetLikes(post->GetLikes()-1);
	}
	else if (stats==0)
	{
		EnableButton(like);
		//ClientManagement::WriteLikeAndDislikeMake(id_user,id_post,type,"LIKE","NO");

		ClientManagement::WriteInFileAction(ClientManagement::FromActionToaString(ClientManagement::Action::eLikeOrDislikeMake),
			id_user, id_post, "LIKE", type, "NO");
		post->SetLikes(post->GetLikes()+1);

	}
	else if (stats == -1)
	{
		EnableButton(like);
		DisableButton(dislike);

		//ClientManagement::WriteLikeAndDislikeMake(id_user, id_post, type, "LIKE", "EXIST");
		ClientManagement::WriteInFileAction(ClientManagement::FromActionToaString(ClientManagement::Action::eLikeOrDislikeMake),
			id_user, id_post, "LIKE", type, "EXIST");

		post->SetLikes(post->GetLikes() + 1);
		post->SetDislikes(post->GetDislikes() -1);
		
	}
}

void WidgetManagement::DislikeAction(QPushButton* like, QPushButton* dislike, uint64_t id_user, uint64_t id_post, const std::string& type, std::shared_ptr<Post> post)
{
	ClientManagement::WriteInFileAction(ClientManagement::FromActionToaString
	(ClientManagement::Action::eLikeAndDislikeStats), id_user, id_post, type);
	uint64_t stats = ClientManagement::ReadFromFileLikeAndDislikeStats(id_user);

	if (stats == 1)
	{
		DisableButton(like);
		EnableButton(dislike);
		//ClientManagement::WriteLikeAndDislikeMake(id_user, id_post, type, "DISLIKE", "EXIST");
		ClientManagement::WriteInFileAction(ClientManagement::FromActionToaString(ClientManagement::Action::eLikeOrDislikeMake),
			id_user, id_post, "DISLIKE", type, "EXIST");
		post->SetLikes(post->GetLikes() - 1);
		post->SetDislikes(post->GetDislikes() +1);

	}
	else if (stats == 0)
	{
		EnableButton(dislike);
		//ClientManagement::WriteLikeAndDislikeMake(id_user, id_post, type, "DISLIKE", "NO");
		ClientManagement::WriteInFileAction(ClientManagement::FromActionToaString(ClientManagement::Action::eLikeOrDislikeMake),
			id_user, id_post, "DISLIKE", type, "NO");

		post->SetDislikes(post->GetDislikes() + 1);

	}
	else if (stats == -1)
	{		
		DisableButton(dislike);
		//ClientManagement::WriteLikeAndDislikeMake(id_user, id_post, type, "DISLIKE", "DELETE");
		ClientManagement::WriteInFileAction(ClientManagement::FromActionToaString(ClientManagement::Action::eLikeOrDislikeMake),
			id_user, id_post, "DISLIKE", type, "DELETE");
		post->SetDislikes(post->GetDislikes() - 1);

	}
}

void WidgetManagement::CommentManagement(QListWidget* list, std::vector<std::shared_ptr<CommentServer>> comment)
{
	ClearList(list);
	int index = 0;
	for (auto& index2 : comment)
	{
		std::cout << index2->GetComment() << "\n";
		QFont font;
		QFont font2;
		//font.setWeight(QFont::Bold);
		font2.setPointSize(8);

		std::string time = index2->GetTimeOfComment();
		time = time.substr(0, 16);

		list->addItem(QString::fromStdString("   By:  " + index2->GetUsername() + "   " + "Date:  " + time));
		font.setPointSize(10);
		font2.setWeight(QFont::Normal);
		list->addItem(QString::fromStdString("  " + index2->GetComment()));
		list->item(index)->setFont(font2);
		list->item(index)->setForeground(Qt::gray);
		index++;
		list->item(index)->setFont(font);
		list->item(index)->setForeground(Qt::white);
		index++;

	}
	
}

void WidgetManagement::ClearList(QListWidget* list)
{
	int counter =list->count();
	for (int index = 0; index < counter; index++)
	{
		QListWidgetItem* item =list->takeItem(0);
		delete item;
	}
}

void WidgetManagement::ProfileManagement(std::shared_ptr<PostPersonalProfile> all, QLabel* postLabel, QLabel* likeLabel, QLabel* dislikeLabel, QLabel* commentLabel)
{
	postLabel->setText(QString::fromStdString(all->GetPostText()));
	likeLabel->setText("Likes:" + QString::number(all->GetLikes()));
	dislikeLabel->setText("Dislikes:" + QString::number(all->GetDislikes()));
	commentLabel->setText("Comments:" + QString::number(all->GetCommentsSize()));
}


