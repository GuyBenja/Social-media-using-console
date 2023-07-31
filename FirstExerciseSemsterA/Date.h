#ifndef DATE_H
#define DATE_H
#include <iostream>
#include "Exceptions.h"

class Date
{

private:

	int m_day;
	int m_month;
	int m_year;

public:

	bool setDay(int day);
	bool setMonth(int month);
	bool setYear(int year);

	int getDay()const;
	int getMonth()const;
	int getYear()const;

	inline void displayDate()const;
	Date(int day, int month, int year)throw(DateException);
	Date() = default;

};

#endif // !DATE_H

