#ifndef FACEBOOK_H
#define FACEBOOK_H
#include <unordered_map>
#include "Exceptions.h"
#include "StateSaverReader.h"

class User;
class FanPage;
class Facebook
{	
	StateSaverReader						 SaverReader;
	std::unordered_map<std::string,User*>    users;
	std::unordered_map<std::string,FanPage*> pages;

public:
	void addNewUser()								throw(UserException);
	void addNewFanPage()							throw(FanPageException);
	void addNewStatus()								throw(UserException, FanPageException, UnrecognizeCharException);
	void displayAllStatus()const					throw(UnrecognizeCharException);
	void displayFriendsStatus()const                throw(UserException);
	void displayAllLikeFanPage()const				throw(UserException);
	void connectUsers()								throw(UserException, FriendshipExceptions);
	void disconnectUsers()							throw(UserException, FriendshipExceptions);
	void addFollowerToPage()						throw(UserException, FanPageException, FriendshipExceptions);
	void removeFollowerFromPage()					throw(UserException, FanPageException, FriendshipExceptions);
	void displayAllUsersAndPages()const				throw(UserException, FanPageException);
	void displayAllFriends()const					throw(UserException, FanPageException, UnrecognizeCharException);
	bool isUserExist(const std::string& name)const;
	bool isFanPageExist(const std::string& name)const;
	void saveAll()const;

	void menu();
	Facebook();
	~Facebook();
};

#endif // !FACEBOOK_H
