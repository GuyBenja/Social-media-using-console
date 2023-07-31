#include <iostream>
#include "Date.h"
#include "Status.h"
#include "User.h"
#include "FanPage.h"
#include "FaceBook.h"
#include "Utilize.h"

using namespace std;
enum eMenuOpt {
	ADD_FRIEND = 1, ADD_NEW_FANPAGE, ADD_NEW_STATUS, DISPLAY_TOP_TEN_FIRENDS_STATUS,DISPLAY_RECENT_STATUS, DISPLAY_ALL_LIKE_FANPAGE, CONNECT_USERS, DISCONNECT_USERS,
	CONNECT_USER_TO_FAN, DISCONNECT_USER_FROM_FAN, DISPLAY_ALL_ENTITIES, DISPLAY_ALL_CONNECTED_USERS, EXIT
};

void Facebook::addNewUser()throw(UserException)
{
	// this funcion add a new user to the system
	cout << "Please enter the name of the new user:";
	string userName;
	readName(userName);
	if(isUserExist(userName)==false)
	{
		Date birthday = readDate();
		User* newUser = new User(userName, birthday);
		users.insert({ userName, newUser });
		cout << userName << " has been added to the system" << endl;
	}
	else
		throw(UserException("There is already user named " + userName));
}

void Facebook::addNewFanPage()throw(FanPageException)
{
	// this function adds new fan page to the system
	cout << "Please enter the name of the new fan page:";
	string fanPageName;
	readName(fanPageName);
	if (isFanPageExist(fanPageName) == false)
	{
		FanPage* newFanPage=new FanPage(fanPageName);
		pages.insert({ fanPageName, newFanPage });
		cout << fanPageName << " has been added to the system" << endl;
	}
	else
		throw(FanPageException("There is already fan page named " + fanPageName));
}

void Facebook::addNewStatus()throw(UserException,FanPageException,UnrecognizeCharException)
{
	// this function adds new status to a user or a fan page
	//it first ask for a type of intity user or fan page to add the status.
	//than it adds the status to the intity

	char type;
	cout << "Would you like to add status to user or fan page ?(u/f): ";
	cin >> type;
	cleanBuffer();
	if (type == 'u' || type == 'U')
	{
		cout << "Please enter the name of the user you wish to add status:";
		string userName;
		readName(userName);
		if(isUserExist(userName))
			readStatusForUser(users, userName);
		else
			throw(UserException("There is no user named " + userName));
	}
	else if (type == 'f' || type == 'F')
	{
		cout << "Please enter the name of the fan page you wish to add stats:";
		string fanPageName;
		readName(fanPageName);
		if(isFanPageExist(fanPageName))
			readStatusForFanPage(pages, fanPageName);
		else
			throw(FanPageException("There is no fan page named " + fanPageName));
	}
	else
		throw(UnrecognizeCharException("You entered unvailed char ,please try again"));
}

void Facebook::displayAllStatus()const throw(UnrecognizeCharException)
{
	// this function display a wall of a user or fan pag
	string text;
	char type;
	cout << "Would you like to show all status of a user or fanpage?(u/f):  ";
	cin >> type;
	cleanBuffer();
	if (type == 'u' || type == 'U')
	{
		cout << "Please enter the name of the user you wish to see all his status:";
		string userName;
		readName(userName);
		if (isUserExist(userName))
		{
			auto userIter = users.find(userName);
			userIter->second->displayWall();
		}
		else
			throw (UserException("There is no user named " + userName));
	}
	else if (type == 'f' || type == 'F')
	{
		cout << "Please enter the name of the fan page you wish to see all his status:";
		string fanPageName;
		readName(fanPageName);
		if (isFanPageExist(fanPageName))
		{
			auto fanPageIter = pages.find(fanPageName);
			fanPageIter->second->displayWall();
		}
		else
			throw (UserException("There is no fan paged named " + fanPageName));
	}
	else
		throw(UnrecognizeCharException("You entered unvailed type ,please try again"));
}

void Facebook::displayFriendsStatus()const throw(UserException)
{
	// this function display all of a user friends wall
	cout << "Please enter the name of the user you wish to see all his friends status:";
	string userName;
	readName(userName);
	if (isUserExist(userName))
	{
		auto userIter = users.find(userName);
		userIter->second->DisplayFriendsTop10Status();
	}
	else
		throw(UserException("There is no user named " + userName));

}

void Facebook::displayAllLikeFanPage()const throw(UserException)
{
	// this function display all of a user friends wall
	cout << "Please enter the name of the user you wish to see all his like fan page:";
	string userName;
	readName(userName);
	if (isUserExist(userName))
	{
		auto userIter = users.find(userName);
		userIter->second->displayAllFanPages();
	}
	else
		throw(UserException("There is no user named " + userName));
}

void Facebook::connectUsers() throw(UserException,FriendshipExceptions)
{
	// this function connect between two friends
	string firstName, secondName;
	cout << "Please enter the names of the users that you wish to connect:" << endl;

	cout<< "First user:";
	readName(firstName);
	if (isUserExist(firstName) == false)
		throw(UserException("There is no user named " + firstName));

	cout << "Second user:";
	readName(secondName);
	if (isUserExist(secondName) == false)
		throw(UserException("There is no user named " + secondName));

	auto FirstUserIter = users.find(firstName);
	auto SecondUserIter = users.find(secondName);

	if (FirstUserIter->second->isFollowerExist(secondName)==false)
	{
		*(FirstUserIter->second) += *(SecondUserIter->second);
		*(SecondUserIter->second) += *(FirstUserIter->second);
		cout << firstName << " and " << secondName << " are now friends" << endl;
	}
	else
		throw(FriendshipExceptions(firstName+" and " + secondName + " are already friends"));
}

void Facebook::disconnectUsers() throw(UserException, FriendshipExceptions)
{
	// this function disconnect two friends
	string firstName, secondName;
	cout << "Please enter the names of the users that you wish to disconnect:" << endl;

	cout << "First user:";
	readName(firstName);
	if (isUserExist(firstName) == false)
		throw(UserException("There is no user named " + firstName));

	cout << "Second user:";
	readName(secondName);
	if (isUserExist(secondName) == false)
		throw(UserException("There is no user named " + secondName));

	auto FirstUserIter = users.find(firstName);
	auto SecondUserIter = users.find(secondName);

	if (FirstUserIter->second->isFollowerExist(secondName) == true)
	{
		FirstUserIter->second->removeFollower(secondName);
		SecondUserIter->second->removeFollower(firstName);
		cout << firstName << " and " << secondName << " are no longer friends" << endl;
	}
	else
		throw(FriendshipExceptions(firstName + " and " + secondName + " were not friends in firstplace"));
	}

void Facebook::addFollowerToPage() throw(UserException,FanPageException, FriendshipExceptions)
{
	// this function add a follower to a page
	cout << "Please enter the names of the fan page and user that you wish to connect:" << endl;;

	cout << "Fan page name:";
	string fanPageName;
	readName(fanPageName);
	if (isFanPageExist(fanPageName) == false)
		throw (FanPageException("There is no fan page named " + fanPageName));

	cout << "User name:";
	string userName;
	readName(userName);
	if (isUserExist(userName) == false)
		throw (UserException("There is no user named " + userName));

	auto UserIter = users.find(userName);
	auto FanPageIter = pages.find(fanPageName);

	if (FanPageIter->second->isFollowerExist(userName) == false)
	{
		*(UserIter->second) += *(FanPageIter->second);
		*(FanPageIter->second) += *(UserIter->second);
		cout << userName << " is following " << fanPageName << endl;
	}
	else
		throw(FriendshipExceptions(userName + " is already following " + fanPageName));
}

void Facebook::removeFollowerFromPage() throw(UserException,FanPageException, FriendshipExceptions)
{
	// this function remove a follower from a page

	cout << "Please enter the names of the fan page and user that you wish to disconnect:";
	cout << "Fan page name:";

	string fanPageName;
	readName(fanPageName);
	if (isFanPageExist(fanPageName) == false)
		throw (FanPageException("There is no fan page named " + fanPageName));

	string userName;
	readName(userName);
	if (isUserExist(userName) == false)
		throw (UserException("There is no user named " + userName));


	auto UserIter = users.find(userName);
	auto FanPageIter = pages.find(fanPageName);

	if (FanPageIter->second->isFollowerExist(userName) == true)
	{
		UserIter->second->removeFanPage(fanPageName);
		FanPageIter->second->removeFollower(userName);
		cout << userName << " is no longer following " << fanPageName << endl;
	}
	else
		throw(FriendshipExceptions(fanPageName + " has no follower named " + userName));
}

void Facebook::displayAllUsersAndPages()const throw(UserException,FanPageException)
{
	// this function display all the user and fan pages name
	if (users.size() == 0)
		throw(UserException("There are not users sign to the system"));
	else
	{
		int i = 1;
		cout << "System users:" << endl << "----------------------" << endl;;
		for (auto iter = users.begin(); iter != users.end(); ++iter, ++i)
		{
			cout << "#" << i << ": " << iter->first << endl;
		}
		cout << endl;
	}
	if (pages.size() == 0)
		throw(FanPageException("The are no pages sign to the system"));
	else
	{
		cout << "System pages:" << endl << "----------------------" << endl;;
		int i = 1;
		for (auto iter = pages.begin(); iter != pages.end(); ++iter, ++i)
		{
			cout << "#" << i << ": " << iter->first << endl;
		}
	}
	cout << endl;
}

void Facebook::displayAllFriends()const throw(UserException, FanPageException,UnrecognizeCharException)
{
	// this function display all the friends of a user or fan
	char type;
	cout << "Would you like to show all status of a user or fanpage?(u/f):" ;
	cin >> type;
	cleanBuffer();
	if (type == 'u' || type == 'U')
	{
		cout << "Please enter the name of the user you wish to see all his friends:";
		string userName;
		readName(userName);
		auto userIter = users.find(userName);
		if (userIter != users.end())
			userIter->second->displayMyFollowers();
		else
			throw UserException("There is no user named " + userName);
	}
	else if (type == 'f' || type == 'F')
	{
		cout << "Please enter the name of the fan page you wish to see all his followers:";
		string fanPageName;
		readName(fanPageName);
		auto fanPageIter = pages.find(fanPageName);
		if (fanPageIter != pages.end())
			fanPageIter->second->displayMyFollowers();
		else
			throw FanPageException("There is no fan page named " + fanPageName);
	}
	else
		throw(UnrecognizeCharException("You enter unvailed type ,please try again"));
}

bool Facebook::isUserExist(const string& name)const
{//this function checks if a user is exsit in the unordered map
	return users.find(name) != users.end();
}

bool Facebook::isFanPageExist(const std::string& name)const
{//this function checks if a fan page is exsit in the unordered map
	return pages.find(name) != pages.end();
}

void Facebook::saveAll()const
{
	//this function suppoesed to save all data

	for (auto iter = users.begin(); iter != users.end(); ++iter)
	{
		SaverReader.Save(*iter->second);
	}

	for (auto iter = pages.begin(); iter != pages.end(); ++iter)
	{
		SaverReader.Save(*iter->second);
	}
	cout << "Data has been saved succesfully" << endl;

}


void Facebook::menu()
{
	// this function display and allow the user to use the menu
	bool fContinue = true;
	while (fContinue)
	{
		try
		{
			cout << "---------MENU---------" << endl;
			cout << "1.  Add new user" << endl;
			cout << "2.  Add new fan page" << endl;
			cout << "3.  Add new status to a user/fan page" << endl;
			cout << "4.  Display all status of a user/fan page" << endl;
			cout << "5.  Display ten most recent status of a user's friends" << endl;
			cout << "6   Display all fan pages a user likes " << endl;
			cout << "7.  Create friendship bewtween two users" << endl;
			cout << "8.  Remove friendship between two users" << endl;
			cout << "9.  Add a follower to a fan page" << endl;
			cout << "10.  Remove a follower from a fan page" << endl;
			cout << "11. Display all users and fan pages signed to the system" << endl;
			cout << "12. Display all friends of a user/followers of a fan page" << endl;
			cout << "13. EXIT" << endl;
			cout << "Please enter you choise (1-13): ";
			int choice;
			cin >> choice;
			cleanBuffer();
			cout << endl;
			switch (choice)
			{
			case ADD_FRIEND:
			{
				addNewUser();
				cout << endl;
				break;
			}
			case ADD_NEW_FANPAGE:
			{
				addNewFanPage();
				cout << endl;
				break;
			}
			case ADD_NEW_STATUS:
			{
				addNewStatus();
				cout << endl;
				break;
			}
			case DISPLAY_TOP_TEN_FIRENDS_STATUS:
			{
				displayAllStatus();
				cout << endl;
				break;
			}
			case DISPLAY_RECENT_STATUS:
			{
				displayFriendsStatus();
				cout << endl;
				break;
			}
			case DISPLAY_ALL_LIKE_FANPAGE:
			{
				displayAllLikeFanPage();
				cout << endl;
				break;
			}
			case CONNECT_USERS:
			{
				connectUsers();
				cout << endl;
				break;
			}
			case DISCONNECT_USERS:
			{
				disconnectUsers();
				cout << endl;
				break;
			}
			case CONNECT_USER_TO_FAN:
			{
				addFollowerToPage();
				cout << endl;
				break;
			}
			case DISCONNECT_USER_FROM_FAN:
			{
				removeFollowerFromPage();
				cout << endl;
				break;
			}
			case DISPLAY_ALL_ENTITIES:
			{
				displayAllUsersAndPages();
				cout << endl;
				break;
			}
			case DISPLAY_ALL_CONNECTED_USERS:
			{
				displayAllFriends();
				cout << endl;
				break;
			}
			case EXIT:
			{
				fContinue = false;
				saveAll();
				cout <<"Thank you for using Facebook"<<endl;
				break;
			}
			default:
				cout << "You entered invalid number,please try again" << endl;
				break;
			}
		}
		catch (exception& e)
		{
			cout << endl<< e.what() << endl <<endl;
		}
		catch (...)
		{
			cout << endl<< "An error occured,please try again" << endl << endl;
		}
	}
}

Facebook::Facebook()
{
	// this function is a c'tor for facebook
	std::vector<User*> outUsers;
	SaverReader.Read(outUsers);

	std::vector<FanPage*> outFanPages;
	SaverReader.Read(outFanPages);

	for (auto& page : outFanPages)
	{
		for (auto& user : outUsers)
		{
			auto itr = user->getPages().find(page->getName());
			if (itr != user->getPages().end())
			{
				itr->second = page;
			}
		}

		pages.insert({ page->getName(), page });
	}
	for (auto& user : outUsers)
	{
		for (auto& page : outFanPages)
		{
			auto itr = page->getConnectedEntity().find(user->getName());
			if (itr != page->getConnectedEntity().end())
			{
				itr->second = user;
			}
		}	
		for (auto& innerUser : outUsers)
		{
			auto itr = innerUser->getConnectedEntity().find(user->getName());
			if (itr != innerUser->getConnectedEntity().end())
			{
				itr->second = user;
			}
		}
		users.insert({ user->getName(), user });
	}	
}

Facebook::~Facebook()
{ //this function is a dtor for the facebook

	for (auto iter = users.begin(); iter != users.end(); ++iter)
	{
		delete iter->second;
	}
	for (auto iter = pages.begin(); iter != pages.end(); ++iter)
	{
		delete iter->second;
	}
}


