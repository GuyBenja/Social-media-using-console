#ifndef FAN_PAGE_H
#define FAN_PAGE_H
#include "Entity.h"
#include "Status.h"
#include <fstream>

class User;
class FanPage: public Entity
{
private:

public:
	FanPage(const std::string& name) : Entity(name) {}
	FanPage(std::ifstream& infstream);
	~FanPage()override {}
	FanPage(const FanPage& other) = delete;					
	FanPage(FanPage && other) = delete;		

	void operator+=(Entity& other)override;

	const FanPage & operator=(const FanPage & other) = delete;
	const FanPage& operator=(FanPage&& other)=delete;
	const FanPage& operator+=(FanPage&& other) = delete;
	const FanPage& operator+=(User&& other) = delete;
	bool operator>(FanPage&& other) = delete;
	bool operator>(User&& other) = delete;
};
#endif // !FAN_PAGE_H