#include "Date.h"
#include "Exceptions.h"
#include <fstream>

using namespace std;

bool Date::setDay(int day)
{//this function set the day
	if (day < 0 || day>31)
		return false;

	m_day = day;
	return true;
}

bool Date::setMonth(int month)
{//this function set the month
	if (month < 0 || month>12)
		return false;
	m_month = month;
	return true;
}

bool Date::setYear(int year)
{//this function set the year
	if (year < 1900 || year>2022)
		return false;
	m_year = year;
	return true;
}

int Date::getDay()const
{//this function return the day
	return m_day;
}

int Date::getMonth()const
{//this function return the month
	return m_month;
}

int Date::getYear()const
{//this function return the year
	return m_year;
}

inline void Date::displayDate()const 
{ //this function display the date
	std::cout << m_day << "/" << m_month << "/" << m_year << std::endl;
}

Date::Date(int day, int month, int year)
{//this function is a ctor for the date
	if (!setDay(day))
		throw DateException("Day of birthday is not valid..(1-31))");
	if (!setMonth(month))
		throw DateException("Month of birthday is not valid..(1-12)");
	if (!setYear(year))
		throw DateException("Year of birthday is not valid..(1900-2022)");
}



