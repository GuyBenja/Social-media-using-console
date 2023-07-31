#include "Exceptions.h"
#include "Entity.h"
#include "ImageStatus.h"
#include "VideoStatus.h"
#include <iostream>
#include <fstream>

using namespace std;


Entity::Entity(const string& name)throw(NameException)
{
	//this is a c'tor for entity
	if (name.size() == 0)
		throw NameException("Name can not be empty");
	setName(name);
}

bool Entity::operator>(const Entity& other)
{//this function compare between the amount of friends of 2 entities
		if (m_connectedEntity.size() > other.getAmountOfFollowers())
			return true;
		return false;
}

void Entity::addStatus(const string& text)
{
	// this function get a str and add it to a fanpage
	Status* newStatus = new Status(text);
	m_wallOfStatus.push_back(newStatus);
}

void Entity::addStatus(const string& text, const string& path)
{
	// this function get a str and add it to a fanpage
	if (path.size() != 0)
	{
		if (path.find(".jpg") != std::string::npos)
		{
			ImageStatus* newImageStatus = new ImageStatus(text, path);
			m_wallOfStatus.push_back(newImageStatus);
		}
		else if (path.find(".jpg") != std::string::npos)
		{
			VideoStatus* newVideoStatus = new VideoStatus(text, path);
			m_wallOfStatus.push_back(newVideoStatus);
		}
		else 
			throw(PathException("The file extention is not correct, please try again"));
	}
	else
		throw(PathException("The file extention is not correct, please try again"));

}

void Entity::displayWall(int i)const
{
	// this function get and int and display the last i status of a fanpage
	// if i == 0 it present all the wall
	if (m_wallOfStatus.size() == 0)
	{
		cout << m_name << "'s wall is empty" << endl;
		return;
	}
	if (i > m_wallOfStatus.size())
	{
		cout << m_name << " has only " << m_wallOfStatus.size() << "posts.." << endl;
		i = m_wallOfStatus.size();
	}
	if (i != 0)
	{
		for (int j = m_wallOfStatus.size() - i; j < m_wallOfStatus.size(); ++j)
		{
			if (j < 0)
				break;
			m_wallOfStatus[j]->displayStatus();
		}
	}
	else
	{
		for (int j = i; j < m_wallOfStatus.size(); ++j)
		{
			m_wallOfStatus[j]->displayStatus();
		}
	}
}

void Entity::removeFollower(const string& FriendNameToRemove)
{
	// this function get friend to remove and remove him from the list
	auto iter = m_connectedEntity.find(FriendNameToRemove);
	if (iter != m_connectedEntity.end())
	{
		m_connectedEntity.erase(FriendNameToRemove);
	}
}

void Entity::displayMyFollowers()const
{
	// this function display the followers name
	int i = 1;
	for (auto iter = m_connectedEntity.begin(); iter != m_connectedEntity.end(); ++iter, ++i)
	{
		cout << "#" << i << ": " << iter->first << endl;
	}
	cout << endl;

}

bool Entity::isFollowerExist(const string& nameToCheck)const
{//this functio checks if a user is a follower of a fun page
	return m_connectedEntity.find(nameToCheck) != m_connectedEntity.end();

}

void Entity::saveToFile(std::ofstream& file) const
{
	//This is a function which save the data of entity to file
	// Write the name
	size_t nameSize = m_name.size();
	file.write(m_name.data(), nameSize);
	file << endl;

	// Write the connected entities
	size_t connectedEntitySize = m_connectedEntity.size();
	file << connectedEntitySize << endl;
	for (auto& iter : m_connectedEntity) {
		size_t keySize = iter.first.size();
		file.write(iter.first.data(), keySize);
		file << endl;
	}

	// Write the wall of status
	std::size_t wallOfStatusSize = m_wallOfStatus.size();
	file << wallOfStatusSize << endl;;
	for (const auto& status : m_wallOfStatus) {
		status->saveToFile(file);
	}

	saveAdditionalData(file);
}
