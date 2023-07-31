#include "User.h";
#include "FanPage.h"
#include "Exceptions.h"
#include "ImageStatus.h"
#include "VideoStatus.h"
#include <iostream>
#include <string>

using namespace std;
enum eStatusType {
	REGULAR_STATUS ,IMAGE_STATUS,VIDEO_STATUS
};
User::User(const string& name, const Date& birthday):Entity(name),m_birthday(birthday)
{
	//this function is a ctor for user
}

User::User(std::ifstream& in)
{
	//this is a ctor for user which loads from file

	//Read name
	std::string line;
	getline(in, line);
	m_name = line;

	// Read the connected entities
	getline(in, line);
	size_t connectedEntitySize = std::stoul(line);
	m_connectedEntity.reserve(connectedEntitySize);
	for (int i = 0; i < connectedEntitySize; ++i)
	{
		getline(in, line);
		m_connectedEntity.insert({ line, nullptr });
	}

	// Read the wall of status
	getline(in, line);
	size_t wallOfStatusSize = std::stoul(line);
	m_wallOfStatus.resize(wallOfStatusSize);
	for (int i = 0; i < wallOfStatusSize; ++i)
	{
		getline(in, line);
		string time;
		getline(in, time);
		string statusType;
		getline(in, statusType);
		if (stoul(statusType) == REGULAR_STATUS)
		{
			Status* newStatus = new Status(line, stoul(time));
			m_wallOfStatus[i] = newStatus;
		}
		else if (stoul(statusType) == IMAGE_STATUS)
		{
			string path;
			getline(in, path);
			ImageStatus* newStatus = new ImageStatus(line, path, stoul(time));
			m_wallOfStatus[i] = newStatus;
		}
		else if(stoul(statusType)== VIDEO_STATUS)
		{
			string path;
			getline(in, path);
				VideoStatus* newStatus = new VideoStatus(line, path, stoul(time));
				m_wallOfStatus[i] = newStatus;
		}
	}

	//Read birthday
	getline(in, line);
	m_birthday.setDay(stoul(line));
	getline(in, line);
	m_birthday.setMonth(stoul(line));
	getline(in, line);
	m_birthday.setMonth(stoul(line));

	//Write liked fan page
	getline(in, line);
	size_t likedFanPageSize = stoul(line);
	m_likedFanPages.reserve(likedFanPageSize);
	for (int i = 0; i < likedFanPageSize; ++i)
	{
		getline(in, line);
		m_likedFanPages.insert({ line, nullptr });
	}
}

void User::operator+=(Entity& other)
{//this function is operator which add a Entity to user
	if (this != &other)
	{
		if (typeid(other) == typeid(User))
		{
			if(isFollowerExist(other.getName())==false)
				m_connectedEntity.insert({ other.getName(),&other });
		}
		else
		{
			if (isFanPageExist(other.getName()) == false)
			{
				FanPage* pPage = dynamic_cast<FanPage*>(&other);
				if(pPage)
				m_likedFanPages.insert({ other.getName(), pPage});
			}
		}
	}
}

void User::displayTopTenUpdateStatus()const
{
	// this function diplay the 10 most recent status of the user
	m_wallOfStatus.size() <= 10 ? displayWall() : displayWall(10);
}

void User::DisplayFriendsTop10Status()const
{
	// this function display ten most recent status of the friends of the user
	if (m_connectedEntity.size() == 0)
	{
		cout << m_name << " has no friends" << endl;
		return;
	}
	for (auto iter = m_connectedEntity.begin(); iter != m_connectedEntity.end(); ++iter)
	{
		User* connectedUser = dynamic_cast<User*>(iter->second);
		if (connectedUser)
		{
			cout << iter->first << " Status: " << endl;
			connectedUser->m_wallOfStatus.size() <= 10 ? connectedUser->displayWall() : connectedUser->displayWall(10);
			cout << endl;
		}
	}
}

void User::removeFanPage(const string& FanPageNameToRemove)
{
	// this function get a FanPage pointer and remove it to the array of the user fanpapges
	if (isFanPageExist(FanPageNameToRemove))
	{
		m_likedFanPages.erase(FanPageNameToRemove);
	}
}

bool User::isFanPageExist(const string& nameToSearch)const
{ // this function check if a fan page is one of the liked fan page of a user

	return m_likedFanPages.find(nameToSearch) != m_likedFanPages.end();
}

void User::saveAdditionalData(std::ofstream& file)const
{
	//this is a function which save the data of user into the file
	//Write birthday
	file << m_birthday.getDay() << endl;
	file << m_birthday.getMonth() << endl;
	file << m_birthday.getYear() << endl;

	//Write liked fan page
	size_t likedFanPage = m_likedFanPages.size();
	file << likedFanPage << endl;;
	for (auto& iter : m_likedFanPages) {
		size_t keySize = iter.first.size();
		file.write(iter.first.data(), keySize);
		file << endl;
		//iter.second->saveToFile(file);
	}
}

void User::displayAllFanPages()const
{
	//this is a function to display all fan page of a user
	cout << "This are the fan pages " + m_name + " likes:" << endl;
	int count = 1;
	for (auto& page : m_likedFanPages)
	{
		cout << count + "# " + page.first << endl;;
	}
}


