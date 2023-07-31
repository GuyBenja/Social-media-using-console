#ifndef USER_H
#define USER_H
#include "Date.h"
#include "Status.h"
#include "Entity.h"
#include <unordered_map>

class FanPage;
class User :public Entity
{
private:

	Date											m_birthday;
	std::unordered_map<std::string,FanPage*>		m_likedFanPages;

public:
	User() = default;
	User(const std::string& name, const Date& birthday);
	User(std::ifstream& infstream);
	~User() {}
	User(const User& other) = delete;					
	User(User&& other) = delete;						

	const User& operator=(const User& other) = delete;
	const User& operator=(User && other) = delete;

	void operator+=(Entity& other)override;

	const User& operator+=(User&& other) = delete;
	const User& operator+=(FanPage&& other) = delete;

	
	bool operator>(User&& other) = delete;
	bool operator>(FanPage&& other) = delete;

	void						displayTopTenUpdateStatus()const;	//show the top 10 update status of user or less if he doesnt have 10
	inline const Date&			getBirthday()const				 { return m_birthday; }
	void						DisplayFriendsTop10Status()const;
	void						removeFanPage(const std::string& FanPageToRemove);
	bool						isFanPageExist(const std::string& nameToSearch)const;
	inline std::unordered_map<std::string, FanPage*>& getPages() { return m_likedFanPages; }
	void displayAllFanPages()const;

protected:
	virtual void saveAdditionalData(std::ofstream& file)const override;
};


#endif // USER_H

