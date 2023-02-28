#pragma once
#include <iostream>
#include<unordered_map>
#include <QtWidgets/QMainWindow>
#include <qdesktopwidget.h>
#include <qlayout.h>
#include <qstyle.h>
#include "ui_Twitter.h"
#include "Register.h"
#include "Login.h"
#include "Feed.h"
#include "UserTwitter.h"
#include"../CommonClasses/PostPersonalProfile.h"
#include"../CommonClasses/Post.h"

class Twitter : public QMainWindow
{
    Q_OBJECT
    //mainWindow->setCentralWidget(stackedWidget);

public:
    Twitter(QWidget *parent = Q_NULLPTR);
    virtual void MouseMoveEvent(QMouseEvent* e);
    //placeholder attempt function
    //void MainWindow(QWidget* parent = nullptr);

    void SetPageNumber(const std::string& pageName, const int& value);
    int GetPageNumber(const std::string& pageName);

private slots:
    /*void setMainWindow();*/
    void on_Login_cliked();
    void on_RegisterButtonLogin_cliked();
    void on_RegisterButtonRegisterWindow_cliked();
    void on_Back_cliked();
    void on_Feed_clicked();
    void on_Post_clicked();
    void on_keywordSearch_clicked();
    void on_userSearch_clicked();
    void on_Logout_clicked();
    void on_follow_clicked();
    void on_personalProfile_clicked();
    void on_NextPost_clicked();
    void on_PrevPost_clicked();
    void on_Back_clicked();
    void on_Search_clicked();
    void on_UserSearch_clicked();
    void on_KeywordSearch_clicked();
    void on_SearchListWidget_clicked();
    void on_SearchedProfileBack_clicked();
    void on_PostTweetButton();
    void on_KeywordSearch();
    void on_BackButtonKeyword();
    void on_NextButtonKeyword();
    void On_FollowButton();
    void On_LikeButtonSearch();
    void On_DislikeButtonSearch();
    void on_Retweet_clicked();
    void on_Comment_clicked();
    void on_CommentSP_clicked();
    void on_NextPostFeed();
    void on_PrevPostFeed();
    void on_LikeFeed();
    void on_DislikePostFeed();
    void on_NextSP();
    void on_PrevSP();
    uint64_t TimeSinceEpochMillisec();

private:
    void HideMessageErrorLogin();
private:
    Ui::TwitterClass ui;
    Register m_registration;
    std::unordered_map<std::string, int> m_windowNumber;
    std::string m_searchOption;

    QString selectedSearchResult;

    std::string m_currUsername;

    UserTwitter m_userCurrent;
    uint64_t id_user_search;
    std::vector<std::shared_ptr<PostPersonalProfile>>m_personalProfilePosts;

    std::vector < std::shared_ptr<Post>>m_keywordPosts;
    std::vector < std::shared_ptr<Post>>feedPosts;
    int m_indexPersonalProfile;
    int m_indexKeywordPosts = 0;
    int m_indexFeedPosts = 0;

    bool isRepost = false;
    uint64_t idPostare;
};