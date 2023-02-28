#include "Twitter.h"
#include "Feed.h"

#include "Register.h"
#include "qpalette.h"
#include"../CommonClasses/PostPersonalProfile.h"
#include"../CommonClasses/Repost.h"
#include"../CommonClasses/Post.h"
#include"ClientManagement.h"
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <qdebug.h>
#include <chrono>
#include <cstdint>
#include <sstream>
#include "Utility.h"
#include "WidgetManagement.h"
#include "windows.h"
#include <QTimer>

Twitter::Twitter(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	//this->resize(1000, 1000);
	ui.stackedWidgets->showFullScreen();
	ui.stackedWidgets->setCurrentIndex(0);
	ui.SearchListWidget->hide();

	QPixmap pix("./backgroundTwitter.png");
	QPixmap pixHeader("./header.png");
	ui.label_4->setPixmap(pix);
	ui.label_4->setScaledContents(true);
	ui.label_4->showFullScreen();

	ui.label_5->setPixmap(pixHeader);
	ui.label_5->setScaledContents(true);

//	ui.label_2->setPixmap(QPixmap("./pngwing.com.png"));
//	QGraphicsOpacityEffect* eff = new QGraphicsOpacityEffect(this);
//	ui.label_2->setGraphicsEffect(eff);
	//QPropertyAnimation* a = new QPropertyAnimation(eff, "opacity");
	//a->setDuration(3500);
	//a->setStartValue(1);
	//a->setEndValue(0);
	//a->setEasingCurve(QEasingCurve::OutBack);
	//a->start(QPropertyAnimation::DeleteWhenStopped);
	//connect(a, SIGNAL(finished()), this, SLOT(hideThisWidget()));

	this->SetPageNumber("LoginWindow", 0);
	this->SetPageNumber("RegisterWindow", 1);
	this->SetPageNumber("FeedWindow", 2);
	this->SetPageNumber("MenuWindow", 3);
	this->SetPageNumber("SearchWindow", 4);
	this->SetPageNumber("KeywordWindow", 5);
	this->SetPageNumber("PostWindow", 6);
	this->SetPageNumber("PersonalProfilePage", 7);
	this->SetPageNumber("SearchedProfilePage", 8);

	this->showMaximized();


	/*ui.stackedWidgets->setGeometry(
		 QStyle::alignedRect(
			 Qt::LeftToRight,
			 Qt::AlignCenter,
			 this->size(),
			 qApp->desktop()->availableGeometry()
		));*/

	ui.ErrorMessageLogin->hide();
	ui.ErrorMessageRegister->hide();
	ui.ErrorMessageUsername->hide();
	ui.ErrorMessagePassword->hide();
	ui.ErrorMessagePassDontMatch->hide();
	ui.ErrorMessagePassLogin->hide();
	ui.ErrorMessageUsernameLogin->hide();
	ui.UsernameExists->hide();
	ui.ConfirmPostWindow->hide();
	ui.ErrorPostWindow->hide();
	ui.ConfirmFeedWindow->hide();
	ui.ConfirmSP->hide();
	ui.ErrorSP->hide();
	ui.ErrorFeedWindow->hide();
	ui.currentRetweetLabel->hide();
	ui.OriginalPostCreator->hide();
	ui.line_4->hide();
	ui.line_5->hide();
	ui.currentPostLabelOriginal->hide();
	ui.currentPostLabel->hide();


	QPalette palette;
	palette.setColor(QPalette::PlaceholderText, QColor(255, 255, 255));
	palette.setColor(QPalette::Text, QColor(255, 255, 255));
	ui.PasswordLineEditLogin->setPalette(palette);
	ui.UsernameLineEditLogin->setPalette(palette);
	ui.UsernameLineEdit->setPalette(palette);
	ui.UsernameLineEdit->setPalette(palette);
	ui.PasswordLineEdit->setPalette(palette);
	ui.PasswordCheckLineEdit->setPalette(palette);
	ui.TweetLineEdit->setPalette(palette);
	ui.SearchBarLineEdit->setPalette(palette);
	ui.KeyEdit->setPalette(palette);
	ui.WirteCommentFeed->setPalette(palette);
	ui.WirteCommentSP->setPalette(palette);

	ui.ErrorMessagePassLogin->setStyleSheet("color: #FF0000");
	ui.ErrorMessageUsernameLogin->setStyleSheet("color: #FF0000");
	ui.ErrorMessageUsername->setStyleSheet("color: #FF0000");
	ui.ErrorMessagePassword->setStyleSheet("color: #FF0000");
	ui.ErrorMessagePassDontMatch->setStyleSheet("color: #FF0000");

	QPalette palette2;
	//palette.setColor(QPalette::setColor(), QColor(158, 158, 158));

	connect(ui.LoginButton, &QPushButton::clicked, this, &Twitter::on_Login_cliked);
	connect(ui.RegisterButtonLogin, &QPushButton::clicked, this, &Twitter::on_RegisterButtonLogin_cliked);
	connect(ui.RegisterButtonRegisterWindow, &QPushButton::clicked, this, &Twitter::on_RegisterButtonRegisterWindow_cliked);
	connect(ui.Back, &QPushButton::clicked, this, &Twitter::on_Back_cliked);
	connect(ui.Post, &QPushButton::clicked, this, &Twitter::on_Post_clicked);
	connect(ui.PersonalProfile, &QPushButton::clicked, this, &Twitter::on_personalProfile_clicked);
	connect(ui.Follow, &QPushButton::clicked, this, &Twitter::on_follow_clicked);
	connect(ui.Feed, &QPushButton::clicked, this, &Twitter::on_Feed_clicked);
	connect(ui.UserSearch, &QPushButton::clicked, this, &Twitter::on_userSearch_clicked);
	connect(ui.Logout, &QPushButton::clicked, this, &Twitter::on_Logout_clicked);
	connect(ui.LogoutPersonalProfile, &QPushButton::clicked, this, &Twitter::on_Logout_clicked);
	connect(ui.BackButtonPost, &QPushButton::clicked, this, &Twitter::on_Back_clicked);
	connect(ui.BackButtonSearchWindow, &QPushButton::clicked, this, &Twitter::on_Back_clicked);
	connect(ui.BackButtonPersonalProfile, &QPushButton::clicked, this, &Twitter::on_Back_clicked);
	connect(ui.BackButtonFeedWindow, &QPushButton::clicked, this, &Twitter::on_Back_clicked);
	connect(ui.BackButtonKeyword, &QPushButton::clicked, this, &Twitter::on_Back_clicked);
	connect(ui.UserSearch, &QPushButton::clicked, this, &Twitter::on_UserSearch_clicked);
	connect(ui.KeywordSearch, &QPushButton::clicked, this, &Twitter::on_KeywordSearch_clicked);
	connect(ui.SearchButton, &QPushButton::clicked, this, &Twitter::on_Search_clicked);
	connect(ui.SearchListWidget, &QListWidget::clicked, this, &Twitter::on_SearchListWidget_clicked);
	connect(ui.BackButtonSearchedProfile, &QPushButton::clicked, this, &Twitter::on_SearchedProfileBack_clicked);
	connect(ui.NextPostPP, &QPushButton::clicked, this, &Twitter::on_NextPost_clicked);
	connect(ui.PrevPostPP, &QPushButton::clicked, this, &Twitter::on_PrevPost_clicked);
	connect(ui.BackPostKeyword, &QPushButton::clicked, this, &Twitter::on_BackButtonKeyword);
	connect(ui.NextPostKeyword, &QPushButton::clicked, this, &Twitter::on_NextButtonKeyword);
	connect(ui.PostTweetButton, &QPushButton::clicked, this, &Twitter::on_PostTweetButton);
	connect(ui.KeySearch, &QPushButton::clicked, this, &Twitter::on_KeywordSearch);
	connect(ui.FollowSearchedProfile, &QPushButton::clicked, this, &Twitter::On_FollowButton);

	connect(ui.LikeButton_2, &QPushButton::clicked, this, &Twitter::On_LikeButtonSearch);
	connect(ui.DislikeButton_2, &QPushButton::clicked, this, &Twitter::On_DislikeButtonSearch);

	connect(ui.LikeButton, &QPushButton::clicked, this, &Twitter::on_LikeFeed);
	connect(ui.DislikeButton, &QPushButton::clicked, this, &Twitter::on_DislikePostFeed);
	//connect(ui.LikeButton, &QPushButton::clicked, this, &Twitter::On_LikeButtonSearch);
   // connect(ui.DislikeButton, &QPushButton::clicked, this, &Twitter::On_DislikeButtonSearch);

	connect(ui.RetweetButton, &QPushButton::clicked, this, &Twitter::on_Retweet_clicked);
	connect(ui.CommentButtonFeed, &QPushButton::clicked, this, &Twitter::on_Comment_clicked);
	connect(ui.CommentButtonSP, &QPushButton::clicked, this, &Twitter::on_CommentSP_clicked);
	connect(ui.NextPostPP_2, &QPushButton::clicked, this, &Twitter::on_NextPostFeed);
	connect(ui.PrevPostPP_2, &QPushButton::clicked, this, &Twitter::on_PrevPostFeed);

	connect(ui.NextPostSP, &QPushButton::clicked, this, &Twitter::on_NextSP);
	connect(ui.PrevPostSP, &QPushButton::clicked, this, &Twitter::on_PrevSP);

	QFont littleFont("Circular Std", 12);

	ui.SearchBarLineEdit->setFont(littleFont);
	ui.TweetLineEdit->setFont(littleFont);
	ui.currentPostLabel->setFont(littleFont);
	ui.CommentList->setFont(littleFont);

	ui.currentPostLabel->setWordWrap(true);

	ui.CommentList->clear();

	QFont font;
	font.setPointSize(10);

}

void Twitter::on_Login_cliked() {
	feedPosts.clear();
	std::string username = ui.UsernameLineEditLogin->text().toStdString();
	std::string password = ui.PasswordLineEditLogin->text().toStdString();

	uint64_t time;
	time = TimeSinceEpochMillisec();
	if (username.size() > 0 && password.size() > 0)
	{
		ClientManagement::WriteInFileAction
		(ClientManagement::FromActionToaString(ClientManagement::Action::eLogin), username, password, time);
		uint64_t exist = ClientManagement::ReadFromFileLogin(time);
		try {
			if (exist != -1) {
				ui.ErrorMessageLogin->hide();
				ui.stackedWidgets->setCurrentIndex(this->GetPageNumber("MenuWindow"));
				m_userCurrent.SetPassword(password);
				m_userCurrent.SetUsername(username);
				m_userCurrent.SetIdUser(exist);

				m_currUsername = username;
				ui.UsernamePersonalProfile->setText(QString::fromStdString(m_userCurrent.GetUsername()));
				ui.MainMenuTitle_2->setText(QString::fromStdString(m_userCurrent.GetUsername()));
				ui.ErrorMessageLogin->hide();
				ui.UsernameLineEditLogin->clear();
				ui.PasswordLineEditLogin->clear();
			}
			throw 404;
		}

		catch (int e)
		{
			ui.ErrorMessageLogin->show();
		}
	}
	else 
		ui.ErrorMessageLogin->show();
}

void Twitter::MouseMoveEvent(QMouseEvent* e)
{
	
}

void Twitter::SetPageNumber(const std::string& pageName, const int& value)
{
	if (m_windowNumber.find(pageName) != m_windowNumber.end()) {
		m_windowNumber[pageName] = value;
	}

	m_windowNumber.insert(std::pair<std::string, int>(pageName, value));
}

int Twitter::GetPageNumber(const std::string& pageName)
{
	if (m_windowNumber.find(pageName) != m_windowNumber.end()) {
		return m_windowNumber[pageName];
	}
	else return -1;
}

void Twitter::on_RegisterButtonLogin_cliked() {
	ui.stackedWidgets->setCurrentIndex(this->GetPageNumber("RegisterWindow"));
}

void Twitter::on_RegisterButtonRegisterWindow_cliked() {
	
	ui.ErrorMessagePassDontMatch->hide();
	ui.ErrorMessagePassword->hide();
	ui.UsernameExists->hide();
	ui.ErrorMessageRegister->hide();

	std::string username = ui.UsernameLineEdit->text().toStdString();
	std::string password = ui.PasswordLineEdit->text().toStdString();
	std::string passwors2 = ui.PasswordCheckLineEdit->text().toStdString();
	uint64_t timeCurr = TimeSinceEpochMillisec();

	if (password != passwors2)
	{
		ui.ErrorMessagePassDontMatch->show();
	}
	if (Register::HasPasswordCorrectPattern(password) == false && password.size()>0)
	{
		ui.ErrorMessagePassword->show();
	}
	if (Register::VerifyUsername(username) == false && username.size()>0)
		ui.UsernameExists->show();

	if (password == passwors2 && Register::HasPasswordCorrectPattern(password) == true && Register::VerifyUsername(username) == true && password.size()>0&& username.size()>0)
	{
		ClientManagement::WriteInFileAction(ClientManagement::FromActionToaString(ClientManagement::Action::eRegister), username, password, timeCurr);
		bool registerUser = ClientManagement::ReadFromFileRegister(timeCurr);
		if (registerUser == true)
		{
			ui.ErrorMessageRegister->hide();
			ui.stackedWidgets->setCurrentIndex(this->GetPageNumber("LoginWindow"));
		}
		else
		{
			ui.ErrorMessageRegister->show();
		}
	}

}

void Twitter::on_Back_cliked() {
	ui.stackedWidgets->setCurrentIndex(this->GetPageNumber("LoginWindow"));
	ui.ErrorMessagePassDontMatch->hide();
	ui.ErrorMessagePassword->hide();
	ui.UsernameExists->hide();
	ui.ErrorMessageRegister->hide();
}

void Twitter::on_Feed_clicked()
{
	ui.stackedWidgets->setCurrentIndex(this->GetPageNumber("FeedWindow"));
	ClientManagement::WriteInFileAction(ClientManagement::FromActionToaString(ClientManagement::Action::eFeed), m_userCurrent.GetIdUser());
	feedPosts = std::move(ClientManagement::ReadFromFeed());


	
	if (feedPosts.size() > 0) {

		WidgetManagement::DislikeAndLikeButton(ui.LikeButton, ui.DislikeButton, m_userCurrent.GetIdUser(),
			feedPosts[m_indexFeedPosts]->GetIdPost(), WidgetManagement::FromObjectToString(feedPosts[m_indexFeedPosts]));

		if (WidgetManagement::FromObjectToString(feedPosts[m_indexFeedPosts]) == "REPOST") {
			std::shared_ptr<Repost>repostText = std::dynamic_pointer_cast<Repost>(feedPosts[m_indexFeedPosts]);
			ui.currentRetweetLabel->show();
			ui.OriginalPostCreator->show();

			ui.currentPostLabelOriginal->hide();
			ui.currentPostLabel->show();

			ui.line_4->show();
			ui.line_5->show();
			ui.PostsUsername->setText(QString::fromStdString("Retweeted by: " + repostText->GetUsernameRepost()));

			ui.currentRetweetLabel->setText(QString::fromStdString(feedPosts[m_indexFeedPosts]->GetPostText()));

			std::string name = repostText->GetRepostText();

			ui.OriginalPostCreator->setText(QString::fromStdString("Original post by:  " + repostText->GetUsernameUserPost()));
			ui.currentPostLabel->setText(QString::fromStdString(repostText->GetRepostText()));
			
		}

		else {
			ui.currentPostLabelOriginal->show();
			ui.currentPostLabel->hide();
			ui.currentRetweetLabel->hide();
			ui.OriginalPostCreator->hide();
			ui.line_4->hide();
			ui.line_5->hide();

			ui.PostsUsername->setText(QString::fromStdString("Posted by: " + feedPosts[m_indexFeedPosts]->GetUsernameUserPost()));
			ui.currentPostLabelOriginal->setText(QString::fromStdString(feedPosts[m_indexFeedPosts]->GetPostText()));
		}

		ui.LikeCountLabel->setText("Likes " + QString::number(feedPosts[m_indexFeedPosts]->GetLikes()));
		ui.DislikeCountLabel->setText("Dislikes " + QString::number(feedPosts[m_indexFeedPosts]->GetDislikes()));
		ui.CommentCountLabel->setText("Comments " + QString::number(feedPosts[m_indexFeedPosts]->GetCommentsSize()));

	

		WidgetManagement::CommentManagement(ui.CommentList, feedPosts[m_indexFeedPosts]->GetComments());
		
	}
}

void Twitter::on_Post_clicked()
{
	ui.stackedWidgets->setCurrentIndex(this->GetPageNumber("PostWindow"));
}

void Twitter::on_keywordSearch_clicked()
{

}

void Twitter::on_userSearch_clicked()
{

}

void Twitter::on_Logout_clicked()
{
	ui.stackedWidgets->setCurrentIndex(this->GetPageNumber("LoginWindow"));
	HideMessageErrorLogin();

}

void Twitter::on_follow_clicked()
{

}

void Twitter::on_personalProfile_clicked()
{

	ui.stackedWidgets->setCurrentIndex(this->GetPageNumber("PersonalProfilePage"));

	ClientManagement::WriteInFileAction(ClientManagement::FromActionToaString
	(ClientManagement::Action::eFollowAndFollowing), m_userCurrent.GetIdUser());

	std::pair<uint64_t, uint64_t>pairFollow = ClientManagement::ReadFromFileNumberOfFollowingAndFollowers(m_userCurrent.GetIdUser());


	ui.FollowingCount->setText("Following:" + QString::number(pairFollow.first));
	ui.FollowersCount->setText("Followers:" + QString::number(pairFollow.second));


	ClientManagement::WriteInFileAction(ClientManagement::FromActionToaString
	(ClientManagement::Action::eUserPostPersonal), m_userCurrent.GetIdUser());
	m_personalProfilePosts = std::move(ClientManagement::ReadFromFilePostPersonalInitial(m_userCurrent.GetIdUser()));

	m_indexPersonalProfile = 0;
	if (m_personalProfilePosts.size() > 0)
	{		
		WidgetManagement::ProfileManagement(m_personalProfilePosts[m_indexPersonalProfile],ui.currentPostLabel_3,ui.LikeCountPP,ui.DislikeCountPP,ui.CommentCountPP);	    
		WidgetManagement::CommentManagement(ui.listWidget_2, m_personalProfilePosts[m_indexPersonalProfile]->GetComments());
	}
}

void Twitter::on_NextPost_clicked()
{
	m_indexPersonalProfile++;
	std::cout << m_indexPersonalProfile;
	if (m_personalProfilePosts.size() > m_indexPersonalProfile)
	{

		WidgetManagement::ProfileManagement(m_personalProfilePosts[m_indexPersonalProfile], ui.currentPostLabel_3, ui.LikeCountPP, ui.DislikeCountPP, ui.CommentCountPP);
		WidgetManagement::CommentManagement(ui.listWidget_2, m_personalProfilePosts[m_indexPersonalProfile]->GetComments());
	}
	else
		m_indexPersonalProfile--;
}

void Twitter::on_PrevPost_clicked()
{
	m_indexPersonalProfile--;
	if (m_indexPersonalProfile >= 0)
	{
		WidgetManagement::ProfileManagement(m_personalProfilePosts[m_indexPersonalProfile], ui.currentPostLabel_3, ui.LikeCountPP, ui.DislikeCountPP, ui.CommentCountPP);
		WidgetManagement::CommentManagement(ui.listWidget_2, m_personalProfilePosts[m_indexPersonalProfile]->GetComments());
	}
	else m_indexPersonalProfile++;
}

void Twitter::on_Back_clicked()
{
	ui.listWidget_2->clear();
	ui.stackedWidgets->setCurrentIndex(this->GetPageNumber("MenuWindow"));
	m_personalProfilePosts.clear();
	ui.SearchBarLineEdit->clear();
	ui.KeyEdit->clear();
	ui.TweetLineEdit->setPlaceholderText("What's happening?");
	ui.PostTweetButton->setText("Tweet");
	isRepost = false;
	m_personalProfilePosts.clear();
	feedPosts.clear();
}

void Twitter::on_UserSearch_clicked()
{
	ui.stackedWidgets->setCurrentIndex(this->GetPageNumber("SearchWindow"));



	//we are going to fill the list widget only with user names
}

void Twitter::on_KeywordSearch_clicked()
{
	ui.stackedWidgets->setCurrentIndex(this->GetPageNumber("KeywordWindow"));
}

void Twitter::on_Search_clicked()
{
	ui.SearchListWidget->clear();
	ui.SearchListWidget->show();

	std::string searchedUsername = ui.SearchBarLineEdit->text().toStdString();

	ClientManagement::WriteInFileAction(ClientManagement::FromActionToaString
	(ClientManagement::Action::eUserSearch), searchedUsername);

	std::vector<std::pair<std::string, std::string>> usernames = ClientManagement::ReadFromFileUserSearch();

	int index = 0;

	std::unordered_map<std::string, std::string> umap;

	for (auto& username : usernames) {

		QFont font;
		font.setWeight(QFont::Bold);
		font.setPointSize(20);

		ui.SearchListWidget->addItem(QString::fromStdString(username.first));
		ui.SearchListWidget->item(index)->setFont(font);
		ui.SearchListWidget->item(index)->setForeground(Qt::white);
		umap.insert(username);
		index++;

	}
	Utility::SetSearchedUsernames(umap);
}

//still have to work on it
void Twitter::on_SearchListWidget_clicked()
{
	selectedSearchResult = ui.SearchListWidget->currentItem()->text();
	id_user_search = std::stoi(Utility::GetId(selectedSearchResult.toStdString()));

	std::string id = Utility::GetId(selectedSearchResult.toStdString());
	std::cout << "Id of selected user is: " << id;



	ClientManagement::WriteInFileAction(ClientManagement::FromActionToaString
	(ClientManagement::Action::eFollowAndFollowing), std::stoi(Utility::GetId(selectedSearchResult.toStdString())));

	std::pair<uint64_t, uint64_t>pairFollow = ClientManagement::ReadFromFileNumberOfFollowingAndFollowers
	(std::stoi(Utility::GetId(selectedSearchResult.toStdString())));

	ui.FollowingCountSearchedProfile->setText("Following:" + QString::number(pairFollow.first));
	ui.FollowersCountSearchedProfile->setText("Followers:" + QString::number(pairFollow.second));

	// ClientManagement::writeInFileFollowStats(m_userCurrent.GetIdUser(),std::stoi(Utility::GetId(selectedSearchResult.toStdString())));

	ClientManagement::WriteInFileAction(ClientManagement::FromActionToaString
	(ClientManagement::Action::eFollowStats), m_userCurrent.GetIdUser(), std::stoi(Utility::GetId(selectedSearchResult.toStdString())));

	if (ClientManagement::ReadFromFileFollowStats(m_userCurrent.GetIdUser()) == true)
	{
		ui.FollowSearchedProfile->setText("Unfollow");
		ui.FollowSearchedProfile->setStyleSheet("color:rgb(255, 255, 255);"
			"background-color: rgb(20 ,31, 42);"
			"border-top: 2px solid rgb(20, 60, 88);"
			"border-left: 2px solid rgb(20, 60, 88);"
			"border-right: 2px solid rgb(20, 60, 88);"
			"border-bottom: 2px solid rgb(20, 60, 88);"
			"border-radius: 20px;");
	}
	else {
		ui.FollowSearchedProfile->setText("Follow");
		ui.FollowSearchedProfile->setStyleSheet("color:rgb(255, 255, 255);"
			"background-color:rgb(28, 162, 243);"
			"border-radius: 20px;");
	}

	

	ClientManagement::WriteInFileAction(ClientManagement::FromActionToaString
	(ClientManagement::Action::eUserPostPersonal), id_user_search);
	m_personalProfilePosts = std::move(ClientManagement::ReadFromFilePostPersonalInitial(std::stoi(id)));

	

	m_indexPersonalProfile = 0;
	if (m_personalProfilePosts.size() > 0)
	{
		WidgetManagement::ProfileManagement(m_personalProfilePosts[m_indexPersonalProfile], ui.currentPostLabelSP, ui.LikeCountSP, ui.DislikeCountSP, ui.CommentCountSP);
		WidgetManagement::CommentManagement(ui.CommentCurrentPostSP, m_personalProfilePosts[m_indexPersonalProfile]->GetComments());		
	}
	
	ui.stackedWidgets->setCurrentIndex(this->GetPageNumber("SearchedProfilePage"));
	ui.SearchListWidget->hide();
	ui.UsernameSearchedProfile->setText(selectedSearchResult);

}

void Twitter::on_SearchedProfileBack_clicked()
{
	int currIndex = ui.stackedWidgets->currentIndex();
	ui.SearchListWidget->hide();
	ui.stackedWidgets->setCurrentIndex(this->GetPageNumber("SearchWindow"));

	m_personalProfilePosts.clear();
}

void Twitter::on_KeywordSearch()
{
	int currIndex = ui.stackedWidgets->currentIndex();
	std::string searchedQuery = ui.KeyEdit->text().toStdString();

	m_indexKeywordPosts = 0;

	ClientManagement::WriteInFileAction(ClientManagement::FromActionToaString(ClientManagement::Action::eKeywordSearch), searchedQuery);
	m_keywordPosts = std::move(ClientManagement::ReadFromFileKeyword());


	if (m_keywordPosts.size() > 0) {

		WidgetManagement::DislikeAndLikeButton(ui.LikeButton_2, ui.DislikeButton_2, m_userCurrent.GetIdUser(),
			m_keywordPosts[m_indexKeywordPosts]->GetIdPost(), WidgetManagement::FromObjectToString(m_keywordPosts[m_indexKeywordPosts]));

		ui.label->setText(QString::fromStdString(m_keywordPosts[m_indexKeywordPosts]->GetUsernameUserPost()));
		ui.currentPostLabel_2->setText(QString::fromStdString(m_keywordPosts[m_indexKeywordPosts]->GetPostText()));
		ui.LikeCountLabel_2->setText("Likes " + QString::number(m_keywordPosts[m_indexKeywordPosts]->GetLikes()));
		ui.DislikeCountLabel_2->setText("Dislikes " + QString::number(m_keywordPosts[m_indexKeywordPosts]->GetDislikes()));
		ui.CommentCountLabel_2->setText("Comments " + QString::number(m_keywordPosts[m_indexKeywordPosts]->GetCommentsSize()));
	
		WidgetManagement::CommentManagement(ui.listWidget, m_keywordPosts[m_indexKeywordPosts]->GetComments());

	}

}

void Twitter::on_BackButtonKeyword()
{
	m_keywordPosts = std::move(m_keywordPosts);
	m_indexKeywordPosts--;

	if (m_indexKeywordPosts >= 0) {
		WidgetManagement::DislikeAndLikeButton(ui.LikeButton_2, ui.DislikeButton_2, m_userCurrent.GetIdUser(),
			m_keywordPosts[m_indexKeywordPosts]->GetIdPost(), WidgetManagement::FromObjectToString(m_keywordPosts[m_indexKeywordPosts]));

		ui.label->setText(QString::fromStdString(m_keywordPosts[m_indexKeywordPosts]->GetUsernameUserPost()));

		ui.currentPostLabel_2->setText(QString::fromStdString(m_keywordPosts[m_indexKeywordPosts]->GetPostText()));
		ui.LikeCountLabel_2->setText("Likes " + QString::number(m_keywordPosts[m_indexKeywordPosts]->GetLikes()));

		ui.DislikeCountLabel_2->setText("Dislikes " + QString::number(m_keywordPosts[m_indexKeywordPosts]->GetDislikes()));
		ui.CommentCountLabel_2->setText("Comments " + QString::number(m_keywordPosts[m_indexKeywordPosts]->GetCommentsSize()));

		ui.listWidget->clear();
		WidgetManagement::CommentManagement(ui.listWidget, m_keywordPosts[m_indexKeywordPosts]->GetComments());
	}
	else
		m_indexKeywordPosts++;

}

void Twitter::on_NextButtonKeyword()
{
	m_keywordPosts = std::move(m_keywordPosts);
	m_indexKeywordPosts++;

	if (m_indexKeywordPosts < m_keywordPosts.size()) {
		WidgetManagement::DislikeAndLikeButton(ui.LikeButton_2, ui.DislikeButton_2, m_userCurrent.GetIdUser(),
			m_keywordPosts[m_indexKeywordPosts]->GetIdPost(), WidgetManagement::FromObjectToString(m_keywordPosts[m_indexKeywordPosts]));

		ui.label->setText(QString::fromStdString(m_keywordPosts[m_indexKeywordPosts]->GetUsernameUserPost()));
		ui.currentPostLabel_2->setText(QString::fromStdString(m_keywordPosts[m_indexKeywordPosts]->GetPostText()));
		ui.LikeCountLabel_2->setText("Likes " + QString::number(m_keywordPosts[m_indexKeywordPosts]->GetLikes()));
		ui.DislikeCountLabel_2->setText("Dislikes " + QString::number(m_keywordPosts[m_indexKeywordPosts]->GetDislikes()));
		ui.CommentCountLabel_2->setText("Comments " + QString::number(m_keywordPosts[m_indexKeywordPosts]->GetCommentsSize()));
		ui.listWidget->clear();
		WidgetManagement::CommentManagement(ui.listWidget, m_keywordPosts[m_indexKeywordPosts]->GetComments());
	}
	else
		m_indexKeywordPosts--;
}

void Twitter::On_FollowButton()
{
	if (ui.FollowSearchedProfile->text() == "Unfollow")
	{
		//ClientManagement::writeFollowOrUnfollow(m_userCurrent.GetIdUser(), id_user_search, false);
		ClientManagement::WriteInFileAction(ClientManagement::FromActionToaString(ClientManagement::Action::eFollowOrUnfollow), "UNFOLLOW", m_userCurrent.GetIdUser(), id_user_search);

		ui.FollowSearchedProfile->setText("Follow");
		ui.FollowSearchedProfile->setStyleSheet("color:rgb(255, 255, 255);"
			"background-color:rgb(28, 162, 243);"
			"border-radius: 20px;");

	}
	else if (ui.FollowSearchedProfile->text() == "Follow")
	{
		//ClientManagement::writeFollowOrUnfollow(m_userCurrent.GetIdUser(), id_user_search, true);
		ClientManagement::WriteInFileAction(ClientManagement::FromActionToaString(ClientManagement::Action::eFollowOrUnfollow), "FOLLOW", m_userCurrent.GetIdUser(), id_user_search);

		ui.FollowSearchedProfile->setText("Unfollow");
		ui.FollowSearchedProfile->setStyleSheet("color:rgb(255, 255, 255);"
			"background-color: rgb(20 ,31, 42);"
			"border-top: 2px solid rgb(20, 60, 88);"
			"border-left: 2px solid rgb(20, 60, 88);"
			"border-right: 2px solid rgb(20, 60, 88);"
			"border-bottom: 2px solid rgb(20, 60, 88);"
			"border-radius: 20px;");
	}
}

void Twitter::On_LikeButtonSearch()
{
	WidgetManagement::LikeAction(ui.LikeButton_2, ui.DislikeButton_2, m_userCurrent.GetIdUser(), m_keywordPosts[m_indexKeywordPosts]->GetIdPost()
		, WidgetManagement::FromObjectToString(m_keywordPosts[m_indexKeywordPosts]), m_keywordPosts[m_indexKeywordPosts]);

	ui.LikeCountLabel_2->setText("Likes " + QString::number(m_keywordPosts[m_indexKeywordPosts]->GetLikes()));
	ui.DislikeCountLabel_2->setText("Dislikes " + QString::number(m_keywordPosts[m_indexKeywordPosts]->GetDislikes()));

}

void Twitter::On_DislikeButtonSearch()
{
	WidgetManagement::DislikeAction(ui.LikeButton_2, ui.DislikeButton_2, m_userCurrent.GetIdUser(), m_keywordPosts[m_indexKeywordPosts]->GetIdPost()
		, WidgetManagement::FromObjectToString(m_keywordPosts[m_indexKeywordPosts]), m_keywordPosts[m_indexKeywordPosts]);

	ui.LikeCountLabel_2->setText("Likes " + QString::number(m_keywordPosts[m_indexKeywordPosts]->GetLikes()));
	ui.DislikeCountLabel_2->setText("Dislikes " + QString::number(m_keywordPosts[m_indexKeywordPosts]->GetDislikes()));
}

void Twitter::on_Retweet_clicked()
{
	////////////////////////////////////////////////////////////////////////////////

	ui.stackedWidgets->setCurrentIndex(this->GetPageNumber("PostWindow"));
	ui.TweetLineEdit->setPlaceholderText("Add a description to your retweet");
	ui.PostTweetButton->setText("Retweet");
	isRepost = true;

}

void Twitter::on_Comment_clicked()
{
	//still to be implemented
	if (ui.WirteCommentFeed->text() != "") {
		if (WidgetManagement::FromObjectToString(feedPosts[m_indexFeedPosts]) == "POST") {
			ClientManagement::WriteInFileAction(ClientManagement::FromActionToaString(ClientManagement::Action::eComment), m_userCurrent.GetIdUser(), feedPosts[m_indexFeedPosts]->GetIdPost(), "POST", ui.WirteCommentFeed->text().toStdString());
		}
		else {
			std::shared_ptr<Repost>t = std::dynamic_pointer_cast<Repost>(feedPosts[m_indexFeedPosts]);
			ClientManagement::WriteInFileAction(ClientManagement::FromActionToaString(ClientManagement::Action::eComment), m_userCurrent.GetIdUser(), t->GetIdRepost(), "REPOST", ui.WirteCommentFeed->text().toStdString());
		}

		ui.WirteCommentFeed->clear();

		ui.ConfirmFeedWindow->show();
		QTimer::singleShot(2000, ui.ConfirmFeedWindow, &QWidget::hide);
	}

	else {
		ui.ErrorFeedWindow->show();
		QTimer::singleShot(1000, ui.ErrorFeedWindow, &QWidget::hide);
	}
	//update();
}

void Twitter::on_CommentSP_clicked()
{
	if (ui.WirteCommentSP->text() != "") {
		ui.ConfirmSP->show();
		QTimer::singleShot(2000, ui.ConfirmSP, &QWidget::hide);
	}
	
	else {
		ui.ErrorSP->show();
		QTimer::singleShot(2000, ui.ErrorSP, &QWidget::hide);
	}
}

void Twitter::on_NextPostFeed()
{
	ui.CommentList->clear();
	m_indexFeedPosts++;

	
	if (m_indexFeedPosts < feedPosts.size()) {

		WidgetManagement::DislikeAndLikeButton(ui.LikeButton, ui.DislikeButton, m_userCurrent.GetIdUser(),
			feedPosts[m_indexFeedPosts]->GetIdPost(), WidgetManagement::FromObjectToString(feedPosts[m_indexFeedPosts]));

		if (WidgetManagement::FromObjectToString(feedPosts[m_indexFeedPosts]) == "REPOST") {
			std::shared_ptr<Repost>repostText = std::dynamic_pointer_cast<Repost>(feedPosts[m_indexFeedPosts]);
			ui.currentRetweetLabel->show();
			ui.OriginalPostCreator->show();
			ui.line_4->show();
			ui.line_5->show();

			ui.currentPostLabelOriginal->hide();
			ui.currentPostLabel->show();

			ui.PostsUsername->setText(QString::fromStdString("Retweeted by: " + repostText->GetUsernameRepost()));
			
			ui.currentRetweetLabel->setText(QString::fromStdString(feedPosts[m_indexFeedPosts]->GetPostText()));

			std::string name = repostText->GetRepostText();

			ui.OriginalPostCreator->setText(QString::fromStdString("Original post by:  " + repostText->GetUsernameUserPost()));
			ui.currentPostLabel->setText(QString::fromStdString(repostText->GetRepostText()));
		}

		else {

			ui.currentRetweetLabel->hide();
			ui.OriginalPostCreator->hide();
			ui.line_4->hide();
			ui.line_5->hide();

			ui.currentPostLabelOriginal->show();
			ui.currentPostLabel->hide();

			ui.PostsUsername->setText(QString::fromStdString("Posted by:  " + feedPosts[m_indexFeedPosts]->GetUsernameUserPost()));
			ui.currentPostLabelOriginal->setText(QString::fromStdString(feedPosts[m_indexFeedPosts]->GetPostText()));
		}


		ui.LikeCountLabel->setText("Likes " + QString::number(feedPosts[m_indexFeedPosts]->GetLikes()));
		ui.DislikeCountLabel->setText("Dislikes " + QString::number(feedPosts[m_indexFeedPosts]->GetDislikes()));
		ui.CommentCountLabel->setText("Comments " + QString::number(feedPosts[m_indexFeedPosts]->GetCommentsSize()));

		WidgetManagement::CommentManagement(ui.CommentList, feedPosts[m_indexFeedPosts]->GetComments());
	}
	else
		m_indexFeedPosts--;

}

void Twitter::on_PrevPostFeed()
{

	m_indexFeedPosts--;
	if (m_indexFeedPosts >= 0) {
		WidgetManagement::DislikeAndLikeButton(ui.LikeButton, ui.DislikeButton, m_userCurrent.GetIdUser(),
			feedPosts[m_indexFeedPosts]->GetIdPost(), WidgetManagement::FromObjectToString(feedPosts[m_indexFeedPosts]));


		if (WidgetManagement::FromObjectToString(feedPosts[m_indexFeedPosts]) == "REPOST") {
			std::shared_ptr<Repost>repostText = std::dynamic_pointer_cast<Repost>(feedPosts[m_indexFeedPosts]);
			ui.currentRetweetLabel->show();
			ui.OriginalPostCreator->show();
			ui.line_4->show();
			ui.line_5->show();

			ui.currentPostLabelOriginal->hide();
			ui.currentPostLabel->show();
			ui.PostsUsername->setText(QString::fromStdString("Retweeted by:  " + repostText->GetUsernameRepost()));
			ui.currentRetweetLabel->setText(QString::fromStdString(feedPosts[m_indexFeedPosts]->GetPostText()));
			std::string name = repostText->GetRepostText();

			ui.OriginalPostCreator->setText(QString::fromStdString("Original post by:  " + repostText->GetUsernameUserPost()));
			ui.currentPostLabel->setText(QString::fromStdString(repostText->GetRepostText()));
			
		}

		else {

			ui.currentRetweetLabel->hide();
			ui.OriginalPostCreator->hide();
			ui.line_4->hide();
			ui.line_5->hide();

			ui.currentPostLabelOriginal->show();
			ui.currentPostLabel->hide();

			ui.PostsUsername->setText(QString::fromStdString("Posted by: " + feedPosts[m_indexFeedPosts]->GetUsernameUserPost()));
			ui.currentPostLabelOriginal->setText(QString::fromStdString(feedPosts[m_indexFeedPosts]->GetPostText()));

		}
		ui.LikeCountLabel->setText("Likes " + QString::number(feedPosts[m_indexFeedPosts]->GetLikes()));
		ui.DislikeCountLabel->setText("Dislikes " + QString::number(feedPosts[m_indexFeedPosts]->GetDislikes()));
		ui.CommentCountLabel->setText("Comments " + QString::number(feedPosts[m_indexFeedPosts]->GetCommentsSize()));		
		WidgetManagement::CommentManagement(ui.CommentList, feedPosts[m_indexFeedPosts]->GetComments());
	}
	else
		m_indexFeedPosts++;
	
}


void Twitter::on_LikeFeed()
{
	WidgetManagement::LikeAction(ui.LikeButton, ui.DislikeButton, m_userCurrent.GetIdUser(), feedPosts[m_indexFeedPosts]->GetIdPost()
		, WidgetManagement::FromObjectToString(feedPosts[m_indexFeedPosts]), feedPosts[m_indexFeedPosts]);

	ui.LikeCountLabel->setText("Likes " + QString::number(feedPosts[m_indexFeedPosts]->GetLikes()));
	ui.DislikeCountLabel->setText("Dislikes " + QString::number(feedPosts[m_indexFeedPosts]->GetDislikes()));
}

void Twitter::on_DislikePostFeed()
{
	WidgetManagement::DislikeAction(ui.LikeButton, ui.DislikeButton, m_userCurrent.GetIdUser(), feedPosts[m_indexFeedPosts]->GetIdPost()
		, WidgetManagement::FromObjectToString(feedPosts[m_indexFeedPosts]), feedPosts[m_indexFeedPosts]);

	ui.LikeCountLabel->setText("Likes " + QString::number(feedPosts[m_indexFeedPosts]->GetLikes()));
	ui.DislikeCountLabel->setText("Dislikes " + QString::number(feedPosts[m_indexFeedPosts]->GetDislikes()));
}

void Twitter::on_NextSP()
{

	m_indexPersonalProfile ++;
	if (m_personalProfilePosts.size() > m_indexPersonalProfile)
	{
		WidgetManagement::ProfileManagement(m_personalProfilePosts[m_indexPersonalProfile], ui.currentPostLabelSP, ui.LikeCountSP, ui.DislikeCountSP, ui.CommentCountSP);
		WidgetManagement::CommentManagement(ui.CommentCurrentPostSP, m_personalProfilePosts[m_indexPersonalProfile]->GetComments());
	}
	else
		m_indexPersonalProfile--;

}

void Twitter::on_PrevSP()
{
	m_indexPersonalProfile--;
	if (m_indexPersonalProfile>=0)
	{
		WidgetManagement::ProfileManagement(m_personalProfilePosts[m_indexPersonalProfile], ui.currentPostLabelSP, ui.LikeCountSP, ui.DislikeCountSP, ui.CommentCountSP);
		WidgetManagement::CommentManagement(ui.CommentCurrentPostSP, m_personalProfilePosts[m_indexPersonalProfile]->GetComments());
	}
	else
		m_indexPersonalProfile++;
}

void Twitter::on_PostTweetButton()
{
	std::string post = ui.TweetLineEdit->text().toStdString();

	if (isRepost == false && post.size() > 0 && post.size()<=140)
	{
		ClientManagement::WriteInFileAction(ClientManagement::FromActionToaString(ClientManagement::Action::eUserPostSend), m_userCurrent.GetIdUser(), post);
		ui.ConfirmPostWindow->show();
		QTimer::singleShot(2000, ui.ConfirmPostWindow, &QWidget::hide);
	}
	else if (isRepost == true && post.size() > 0&&  post.size() <= 140)
	{
		ClientManagement::WriteInFileAction(ClientManagement::FromActionToaString(ClientManagement::Action::eRepost), m_userCurrent.GetIdUser(),
			feedPosts[m_indexFeedPosts]->GetIdPost(), post);
		ui.ConfirmPostWindow->show();
		QTimer::singleShot(2000, ui.ConfirmPostWindow, &QWidget::hide);
	}
	else if (post.size() <= 0)
	{
		ui.ErrorPostWindow->show();
		QTimer::singleShot(2000, ui.ErrorPostWindow, &QWidget::hide);
	}

}

uint64_t Twitter::TimeSinceEpochMillisec()
{
	using namespace std::chrono;
	return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

void Twitter::HideMessageErrorLogin()
{
	ui.UsernameExists->hide();
	ui.ErrorMessageUsernameLogin->hide();
	ui.ErrorMessagePassLogin->hide();
	ui.ErrorMessageLogin->hide();
}