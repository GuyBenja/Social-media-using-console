#ifndef STATUS_H
#define STATUS_H
#include <iostream>
#include <fstream>
#include <ctime>
#include "Exceptions.h"

class Status
{
protected:
	std::string		m_text;
	time_t          m_time;

	virtual void displayAdditionalStatus() const {}
	virtual void saveAddionalData(std::ofstream& file)const { file << "0" << std::endl; }

public:

	void setStatus(const std::string text);
	void displayStatus() const;
	void printPublishTime()const;

	Status(const std::string& text, long int time) :m_time(time) {setStatus(text);}
	Status(const std::string& text): m_time(time(NULL)) {setStatus(text);}
	virtual ~Status() {}
	inline bool operator==(const Status& other)const		{ return m_text == other.m_text; }
	inline bool operator!=(const Status& other)const		{ return  m_text != other.m_text; }
	void saveToFile(std::ofstream& file)const;
};
#endif // !STATUS_H

