#include <iostream>
#include <string>
#include "FanPage.h"
#include "ImageStatus.h"
#include "VideoStatus.h"
using namespace std;

enum eStatusType {
	REGULAR_STATUS, IMAGE_STATUS, VIDEO_STATUS
};
FanPage::FanPage(ifstream& in)
{
	//this is a ctor for fan page which loads from file
	// Read the name
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
	for (int i = 0; i < wallOfStatusSize;++i) 
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
		else if (stoul(statusType) == VIDEO_STATUS)
		{
			string path;
			getline(in, path);
			VideoStatus* newStatus = new VideoStatus(line, path, stoul(time));
			m_wallOfStatus[i] = newStatus;
		}
	}
}

void FanPage::operator+=(Entity& new_follower)
{//this function is an operator for adding a folloer to fan page
	if (isFollowerExist(new_follower.getName()) == false)
	{
		m_connectedEntity.insert({ new_follower.getName(), &new_follower });
	}
}


