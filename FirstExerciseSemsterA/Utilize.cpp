#include "Utilize.h"
#include <iostream>
#include <unordered_map>
#include <string>
#include "Status.h"
using namespace std;

typedef unordered_map<string, User*> userMap;
typedef unordered_map<string, FanPage*> pagesMap;
void readName(string& name) throw(NameException)
{
	//this function reads a user name,if the name is already exist the funciton throw an excptions
	getline(cin,name);
	if (name.size() == 0)
		throw(NameException("Name can not be empty ,please try again"));
}

void cleanBuffer()
{
	// this function clean the buffer
	int c;
	do
	{
		c = getchar();
	} while (c != EOF && c != '\n');
}

const Date& readDate()
{//this function reads a date from the user
	std::cout << "Enter user birthday(day month year) :";
	int day, month, year;
	std::cin >> day >> month >> year;
	cleanBuffer();
	return Date(day, month, year);
}

void readStatusForUser(userMap& users,const string& userName)throw (UnrecognizeCharException, UserException)
{	//this function reads a status for a user from the user
	const auto& userIter = users.find(userName);
	if (userIter != users.end())
	{
		string path, text;
		char type;
		cout << "What are you thinking off: ";
		getline(cin, text);
		cout << "Would you like to add to the status image or video? (y/n): ";
		cin >> type;
		cleanBuffer();
		if (type != 'y' && type != 'Y' && type != 'n' && type != 'N')
			throw UnrecognizeCharException("You entered invailed char,please try again");
		else if (type == 'y' || type == 'Y')
		{
			cout << "Would you like to add image or video? (i/v): ";
			cin >> type;
			cleanBuffer();
			if (type == 'i' || type == 'I')
			{
				cout << "Please enter the path of the image: ";
				cin >> path;
				userIter->second->addStatus(text,path);
				cout << "The status and the image have been added" << endl;

			}
			else if (type == 'v' || type == 'V')
			{
				cout << "Please enter the path of the video: ";
				cin >> path;
				userIter->second->addStatus(text, path);
				cout << "The status and the video have been added" << endl;

			}
			else
				throw UnrecognizeCharException("You entered invailed char,please try again");
		}
		else
		{
			userIter->second->addStatus(text);
			cout << "The status has been added" << endl;
		}
	}
	else
		throw(UserException("There is no user named" + userName));
}

void readStatusForFanPage(pagesMap& pages,const string& pageName)throw(UnrecognizeCharException,FanPageException)
{//this function reads a status for a fan page from the user
	const auto& pageIter = pages.find(pageName);
	if (pageIter != pages.end())
	{
		string path, text;
		char type;
		cout << "What are you thinking off: ";
		getline(cin, text);
		cout << "Would you like to add to the status image or video? (y/n): ";
		cin >> type;
		cleanBuffer();
		if (type != 'y' && type != 'Y' && type != 'n' && type != 'N')
			throw UnrecognizeCharException("You entered invailed char,please try again");
		else if (type == 'y' || type == 'Y')
		{
			cout << "Would you like to add image or video? (i/v): ";
			cin >> type;
			cleanBuffer();
			if (type == 'i' || type == 'I')
			{
				cout << "Please enter the path of the image: ";
				cin >> path;
				pageIter->second->addStatus(text, path);
				cout << "The status and the image have been added" << endl;

			}
			if (type == 'v' || type == 'V')
			{
				cout << "Please enter the path of the video: ";
				cin >> path;
				pageIter->second->addStatus(text, path);
				cout << "The status and the video have been added" << endl;

			}
			else
				throw UnrecognizeCharException("You entered invailed char,please try again");
		}
		else
		{
			pageIter->second->addStatus(text);
			cout << "The status has been added" << endl;
		}
	}
	else
		throw(FanPageException("There is no fan page named" + pageName));
}

